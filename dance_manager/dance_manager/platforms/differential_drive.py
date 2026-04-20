"""
Differential Drive Platform — Robot Choreography System

Concrete RobotPlatform implementation for two-wheeled differential drive robots.
Publishes geometry_msgs/Twist commands via a ROS 2 publisher.

This module wraps all the motion primitives from dance_moves.py and exposes
them through the platform abstraction. The choreography layer never touches
Twist directly — it sends move names + MoveContext through the platform interface.

Dancer Design Thinking — Platform-Specific Implementations
-----------------------------------------------------------
§1 Pre-roll:        100ms micro-vibration or subtle counter-steer
§1 Texture presets: honey=high damping/slow ramp, staccato=instant torque,
                    ice=minimal damping, cloud=exponential ramps
§3 Active brake:    brief counter-torque pulse then zero
§3 Spotting:        virtual heading anchor via odometry (placeholder)
§3 Lean into error: residual velocity → suggested flow move
"""

from __future__ import annotations

import math
import time
from typing import Optional

from dance_manager.platform import RobotPlatform, MoveContext, Texture
from dance_manager.dance_moves import (
    step, glide, drive_arc, glance, shimmy, pulse, vibrate,
    tap_on_side, zigzag, pirouette, slalom, spin_on_axis,
    teacup_spin, spiral, teacup, figure_eight, flower,
    wag_walking, bow_sequence,
    pacing, sudden_stop, chaine_turns,
    _brake, _brake_angular, _stop,
)
from dance_manager.dance_vocabulary import translate_params


# ── Environment modulation proxy ─────────────────────────────────────────────

class _EnvPublisher:
    """Twist publisher proxy that applies environmental modulation.

    Wraps the real publisher and modifies each Twist before forwarding:
      env_bias       adds a constant angular.z offset (directional force / slope)
      env_resistance multiplies linear.x by (1 - resistance) (viscosity / friction)
    """

    def __init__(self, real_pub, env_bias: float = 0.0, env_resistance: float = 0.0):
        self._pub = real_pub
        self._bias = float(env_bias)
        self._resistance = max(0.0, min(1.0, float(env_resistance)))

    def publish(self, twist):
        from geometry_msgs.msg import Twist as _Twist
        t = _Twist()
        t.linear.x = twist.linear.x * (1.0 - self._resistance)
        t.linear.y = twist.linear.y
        t.linear.z = twist.linear.z
        t.angular.x = twist.angular.x
        t.angular.y = twist.angular.y
        t.angular.z = twist.angular.z + self._bias
        self._pub.publish(t)


# ── Texture → motor parameter translation ────────────────────────────────────

TEXTURE_PROFILES = {
    Texture.NEUTRAL: {
        "ramp_up_scale": 1.0,
        "ramp_down_scale": 1.0,
        "profile": "linear",
        "damping": 1.0,
    },
    Texture.HONEY: {
        "ramp_up_scale": 2.0,      # slow onset
        "ramp_down_scale": 2.0,    # slow settle
        "profile": "linear",
        "damping": 2.0,            # high damping
    },
    Texture.STACCATO: {
        "ramp_up_scale": 0.3,      # instant torque
        "ramp_down_scale": 0.2,    # abrupt stop
        "profile": "linear",
        "damping": 0.5,
    },
    Texture.ICE: {
        "ramp_up_scale": 0.5,      # quick start
        "ramp_down_scale": 3.0,    # long coast
        "profile": "linear",
        "damping": 0.2,            # minimal damping — gliding
    },
    Texture.CLOUD: {
        "ramp_up_scale": 1.5,
        "ramp_down_scale": 1.5,
        "profile": "exponential",  # floaty ease-in/out
        "damping": 0.8,
    },
    Texture.MAGNET: {
        "ramp_up_scale": 0.4,      # snappy attraction
        "ramp_down_scale": 0.4,    # snappy repulsion
        "profile": "exponential",
        "damping": 1.5,
    },
}


class DiffDrivePlatform(RobotPlatform):
    """Differential drive robot platform (e.g., hoverboard robot).

    Publishes Twist messages to a ROS 2 topic. All motion primitives
    from dance_moves.py are registered as named moves.

    Args:
        twist_pub: A rclpy Publisher[geometry_msgs.msg.Twist].
        track_width: Distance between wheels [m]. Default 0.6.
    """

    def __init__(self, twist_pub, track_width: float = 0.6):
        self._twist_pub = twist_pub
        self._track_width = track_width
        self._move_registry = self._build_move_registry()

    def _build_move_registry(self) -> dict:
        """Build the mapping from primitive move names to callables.

        Each entry is a function that takes (params, **extra_kwargs) where
        params is a dict of move-specific parameters (direction, side, angle, etc.).

        NOTE: Lambdas reference self._twist_pub at call time (not capture time),
        so temporarily replacing self._twist_pub (e.g. for env modulation) is
        reflected immediately without rebuilding the registry.
        """
        track = self._track_width

        return {
            # Social gestures
            "Glance":       lambda p, **kw: glance(self._twist_pub, **kw),
            "Bow":          lambda p, **kw: bow_sequence(self._twist_pub, **kw),
            # Linear translation
            "Step":         lambda p, **kw: step(self._twist_pub,
                                direction=p.get("direction", "forward"), **kw),
            "Glide":        lambda p, **kw: glide(self._twist_pub,
                                direction=p.get("direction", "forward"), **kw),
            # Expressive in-place
            "Shimmy":       lambda p, **kw: shimmy(self._twist_pub, **kw),
            "Pulse":        lambda p, **kw: pulse(self._twist_pub, **kw),
            "Vibrate":      lambda p, **kw: vibrate(self._twist_pub, **kw),
            # Pivot / tap
            "Tap":          lambda p, **kw: tap_on_side(self._twist_pub,
                                side=p.get("side", "right"), track=track, **kw),
            "Pirouette":    lambda p, **kw: pirouette(self._twist_pub,
                                side=p.get("side", "left"), track=track, **kw),
            # Spin — angle in degrees, positive=CCW, negative=CW
            "Spin":         lambda p, **kw: spin_on_axis(
                                self._twist_pub,
                                rotations=abs(p.get("angle", 360)) / 360.0,
                                clockwise=p.get("angle", 360) < 0,
                                **kw),
            # Weaving paths
            "Zigzag":       lambda p, **kw: zigzag(self._twist_pub,
                                direction=p.get("direction", "forward"), track=track, **kw),
            "Slalom":       lambda p, **kw: slalom(self._twist_pub,
                                direction=p.get("direction", "forward"), **kw),
            "WagWalk":      lambda p, **kw: wag_walking(self._twist_pub, **kw),
            # Arc / circle
            "Arc":          lambda p, **kw: drive_arc(self._twist_pub,
                                direction=p.get("direction", "left"),
                                radius=p.get("radius", 0.5),
                                angle=math.radians(p.get("angle", 180)), **kw),
            "TeacupSpin":   lambda p, **kw: teacup_spin(self._twist_pub,
                                side=p.get("side", "left"), **kw),
            "TeacupCircle": lambda p, **kw: teacup(self._twist_pub,
                                direction=p.get("direction", "left"), **kw),
            # Complex paths
            "Spiral":       lambda p, **kw: spiral(self._twist_pub,
                                direction=p.get("direction", "left"), **kw),
            "FigureEight":  lambda p, **kw: figure_eight(self._twist_pub, **kw),
            "Flower":       lambda p, **kw: flower(self._twist_pub, **kw),
            # Layer 1 additions
            "Pacing":       lambda p, **kw: pacing(self._twist_pub,
                                distance=p.get("distance", 0.5),
                                step_duration=p.get("step_duration", 1.0),
                                repetitions=p.get("repetitions", 4),
                                pause_duration=p.get("pause_duration", 0.3),
                                **kw),
            "SuddenStop":   lambda p, **kw: sudden_stop(self._twist_pub,
                                direction=p.get("direction", "forward"),
                                max_speed=p.get("max_speed", 0.6),
                                run_duration=p.get("run_duration", 0.4),
                                brake_times=p.get("brake_times", 8),
                                **kw),
            "ChaineTurns":  lambda p, **kw: chaine_turns(self._twist_pub,
                                turns=p.get("turns", 2.0),
                                half_turn_duration=p.get("half_turn_duration", 0.8),
                                track=track,
                                **kw),
        }

    # ── RobotPlatform interface ──────────────────────────────────────────────

    def get_available_moves(self) -> list[str]:
        return list(self._move_registry.keys())

    def execute_move(self, move_name: str, context: MoveContext) -> bool:
        if move_name not in self._move_registry:
            return False

        # Translate dance vocabulary in params (e.g. "3 o'clock" → direction="right")
        params = translate_params(context.params) if context.params else {}

        # Extract environment modulation params (consumed here, not forwarded to move fn)
        env_bias = float(params.pop("env_bias", 0.0))
        env_resistance = float(params.pop("env_resistance", 0.0))

        # Temporarily apply environmental forces via publisher proxy.
        # Because lambdas in _move_registry reference self._twist_pub at call time,
        # swapping the attribute here is sufficient — no registry rebuild needed.
        real_pub = self._twist_pub
        if env_bias != 0.0 or env_resistance != 0.0:
            self._twist_pub = _EnvPublisher(real_pub, env_bias, env_resistance)

        try:
            kwargs = self._context_to_kwargs(context)

            # §1: Pre-roll — preparatory micro-movement
            if context.enable_pre_roll:
                self.pre_roll(move_name, context)

            # Execute the move with translated params
            self._move_registry[move_name](params, **kwargs)

            # §3: Active brake — freeze as tension
            if context.enable_active_brake:
                self.active_brake(context)
        finally:
            self._twist_pub = real_pub  # always restore original publisher

        return True

    def pre_roll(self, move_name: str, context: MoveContext) -> None:
        """100ms micro-vibration or subtle counter-steer before the move.

        For diff-drive, this is a brief vibration that signals "I'm about
        to move" — like a dancer's preparatory breath.
        """
        if not context.enable_pre_roll:
            return

        from geometry_msgs.msg import Twist
        t = Twist()
        intensity = 0.05 + 0.05 * context.energy  # scale with energy

        # Brief vibration: 2 quick oscillations over ~100ms
        for _ in range(2):
            t.angular.z = intensity
            self._twist_pub.publish(t)
            time.sleep(0.025)
            t.angular.z = -intensity
            self._twist_pub.publish(t)
            time.sleep(0.025)

        t.angular.z = 0.0
        self._twist_pub.publish(t)

    def active_brake(self, context: MoveContext) -> None:
        """Brief counter-torque pulse then zero — freeze as active tension.

        Instead of just publishing zero velocity, we pulse a brief
        counter-movement to create a crisp, intentional stop.
        """
        if not context.enable_active_brake:
            return

        from geometry_msgs.msg import Twist
        t = Twist()

        # Brief counter-pulse (the "tension" of stopping)
        brake_intensity = 0.05 + 0.05 * context.energy
        t.linear.x = -brake_intensity
        self._twist_pub.publish(t)
        time.sleep(0.03)

        # Then firm zero
        t.linear.x = 0.0
        t.angular.z = 0.0
        self._twist_pub.publish(t)

    def stop(self) -> None:
        _stop(self._twist_pub)

    def apply_texture(self, texture: Texture) -> dict:
        return TEXTURE_PROFILES.get(texture, TEXTURE_PROFILES[Texture.NEUTRAL])

    def spotting_anchor(self, target_heading: Optional[float] = None) -> None:
        # Placeholder — requires odometry/IMU integration
        pass

    def lean_into_error(self, residual_velocity: float) -> Optional[str]:
        """Suggest a flow move based on residual drift direction."""
        if abs(residual_velocity) < 0.05:
            return None
        if residual_velocity > 0:
            return "Glide"   # flowing with forward drift
        return "Glide"      # flowing with backward drift

    def get_move_displacements(self) -> dict[str, dict]:
        """Approximate displacement per move at nominal energy with default params.

        Displacement depends on params (direction, angle, side). These are
        estimates for the default param values. The AI prompt also receives
        param descriptions so it can reason about non-default cases.
        """
        pi = 3.14159
        return {
            # In-place / returning
            "Glance":       {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.0, "returns": True},
            "Bow":          {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.3, "returns": True},
            "Shimmy":       {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.0, "returns": True},
            "Pulse":        {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.1, "returns": True},
            "Vibrate":      {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.05, "returns": True},
            "Tap":          {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.1, "returns": True},
            "Pirouette":    {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.6, "returns": True},
            # Translation (default: forward)
            "Step":         {"dx": 0.5, "dy": 0.0, "dtheta": 0.0,  "radius": 0.5, "returns": False,
                             "note": "dx depends on direction: forward +0.5m, backward -0.5m"},
            "Glide":        {"dx": 0.6, "dy": 0.0, "dtheta": 0.0,  "radius": 0.6, "returns": False,
                             "note": "dx depends on direction: forward +0.6m, backward -0.6m"},
            "Zigzag":       {"dx": 0.8, "dy": 0.0, "dtheta": 0.0,  "radius": 1.0, "returns": False,
                             "note": "dx depends on direction: forward +0.8m, backward -0.8m"},
            "Slalom":       {"dx": 2.4, "dy": 0.0, "dtheta": 0.0,  "radius": 2.5, "returns": False,
                             "note": "dx depends on direction: forward +2.4m, backward -2.4m"},
            "WagWalk":      {"dx": 1.5, "dy": 0.0, "dtheta": 0.0,  "radius": 1.5, "returns": False},
            # Spin (default: 360 CCW)
            "Spin":         {"dx": 0.0, "dy": 0.0, "dtheta": 2*pi, "radius": 0.0, "returns": True,
                             "note": "dtheta = angle param in rad. 360=full turn (returns), <360=partial (does not return)"},
            # Arc / curves (default: left, 180 deg)
            "Arc":          {"dx": 0.0, "dy": 1.0, "dtheta": pi,   "radius": 1.0, "returns": False,
                             "note": "displacement depends on direction and angle params"},
            "TeacupSpin":   {"dx": 0.0, "dy": 1.0, "dtheta": 2*pi, "radius": 1.0, "returns": False,
                             "note": "lateral displacement depends on side param"},
            "TeacupCircle": {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 1.0, "returns": True},
            "Spiral":       {"dx": 0.5, "dy": 0.5, "dtheta": 2*pi, "radius": 1.5, "returns": False,
                             "note": "displacement depends on direction param"},
            "FigureEight":  {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 1.0, "returns": True},
            "Flower":       {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 1.6, "returns": True},
            # Layer 1 additions
            "Pacing":       {"dx": 0.0, "dy": 0.0, "dtheta": 0.0,  "radius": 0.5, "returns": True,
                             "note": "one full out-and-back cycle per repetition"},
            "SuddenStop":   {"dx": 0.3, "dy": 0.0, "dtheta": 0.0,  "radius": 0.3, "returns": False,
                             "note": "dx depends on direction: forward +0.3m, backward -0.3m"},
            "ChaineTurns":  {"dx": 0.0, "dy": 0.0, "dtheta": 2*pi, "radius": 0.6, "returns": True,
                             "note": "net displacement small; alternating CCW half-turns"},
        }

    def get_move_categories(self) -> dict[str, list[str]]:
        return {
            "social":     ["Glance", "Bow"],
            "linear":     ["Step", "Glide", "WagWalk", "Pacing"],
            "weaving":    ["Zigzag", "Slalom"],
            "spin":       ["Spin", "Pirouette", "ChaineTurns"],
            "arc":        ["Arc", "TeacupSpin", "TeacupCircle"],
            "complex":    ["Spiral", "FigureEight", "Flower"],
            "percussive": ["Tap", "SuddenStop"],
            "expressive": ["Shimmy", "Pulse", "Vibrate"],
        }

    def get_platform_description(self) -> str:
        return (
            "A differential-drive dance robot with two wheels. "
            "It can move forward/backward, spin in place, pivot around one wheel, "
            "and drive arcs, spirals, figure-eights, and flower curves. "
            f"Track width: {self._track_width}m. "
            "Moves accept params for direction/side/angle — see the parameter "
            "descriptions in the move list."
        )

    # ── Internal helpers ─────────────────────────────────────────────────────

    def _context_to_kwargs(self, context: MoveContext) -> dict:
        """Translate MoveContext into kwargs that dance_moves functions accept.

        Texture mapping to the dancer vocabulary system:
            neutral  → default weight and energy (no modification)
            honey    → heavy weight (slow ramps, grounded feel)
            staccato → light weight + energy boost (instant torque, sharp)
            ice      → light weight + energy reduction (gliding, minimal friction)
            cloud    → light weight (floaty, exponential curves)
            magnet   → neutral weight + noise (push-pull organic variation)
        """
        kwargs = {}

        if context.energy != 0.5:
            kwargs["energy"] = context.energy
        if context.weight != "neutral":
            kwargs["weight"] = context.weight
        if context.noise_level > 0.0:
            kwargs["noise_level"] = context.noise_level

        # Apply texture — translate abstract quality into motor behavior
        if context.texture == Texture.HONEY:
            kwargs.setdefault("weight", "heavy")
        elif context.texture == Texture.STACCATO:
            kwargs.setdefault("weight", "light")
            # Boost energy for percussive snap
            e = kwargs.get("energy", context.energy)
            kwargs["energy"] = min(1.0, e * 1.4)
        elif context.texture == Texture.ICE:
            kwargs.setdefault("weight", "light")
            # Reduce energy for gliding coast
            e = kwargs.get("energy", context.energy)
            kwargs["energy"] = max(0.1, e * 0.6)
        elif context.texture == Texture.CLOUD:
            kwargs.setdefault("weight", "light")
            # Slightly lower energy for floaty feel
            e = kwargs.get("energy", context.energy)
            kwargs["energy"] = max(0.1, e * 0.8)
        elif context.texture == Texture.MAGNET:
            # Add noise for organic push-pull dynamics
            kwargs.setdefault("noise_level", 0.15)

        return kwargs
