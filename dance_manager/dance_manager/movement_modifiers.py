"""
Layer 2 — Movement Modifiers

Sequence-level spec helpers that describe how a Motif should be expanded
by run_sequence() in choreographer.py. Each helper returns a plain dict
consumed by the _expand() function; none of them touch twist_pub directly.

Modifier types
--------------
Repetition & Pattern
  seq_repeat              : exact repetition N times
  seq_repeat_variation    : repeat with slight energy/scale variation each time
  seq_alternate           : interleave this move with another (A-B-A-B...)
  seq_asymmetric_pause    : repeat with alternating short/long pauses

Transformation
  seq_mirror              : run twice — original then spatially mirrored
  seq_direction_flip      : run twice — original then direction/side/clockwise flipped
  seq_invert              : invert energy (1-energy) and optionally spatial scale
  seq_reverse             : placeholder for phrase-level reversal (single motif = no-op)

Parametric & Dynamic Modulation
  seq_scale               : multiply spatial params (radius, distance) by factor
  seq_speed_modulate      : multiply energy by factor
  seq_decay               : repeat with increasing gap (energy fades)
  seq_crescendo           : repeat with decreasing gap (urgency builds)
  seq_tension             : hold still (anticipation) before the move
  seq_rhythm_shift        : scale gap_before by a factor

Organic Variation
  seq_drift               : shift angle/direction param by a delta
  seq_env_modulation      : apply simulated environmental forces (bias + resistance)

Vocabulary re-exports
  energy_to_speed, weight_to_accel, flow_to_gap, add_noise
"""

from dance_manager.dance_moves import (
    energy_to_speed,
    weight_to_accel,
    flow_to_gap,
    add_noise,
)

__all__ = [
    # vocabulary re-exports
    "energy_to_speed",
    "weight_to_accel",
    "flow_to_gap",
    "add_noise",
    # sequence-level spec helpers
    "seq_repeat",
    "seq_repeat_variation",
    "seq_alternate",
    "seq_asymmetric_pause",
    "seq_mirror",
    "seq_direction_flip",
    "seq_invert",
    "seq_reverse",
    "seq_scale",
    "seq_speed_modulate",
    "seq_decay",
    "seq_crescendo",
    "seq_tension",
    "seq_rhythm_shift",
    "seq_drift",
    "seq_env_modulation",
]


# ── Repetition & Pattern ──────────────────────────────────────────────────────

def seq_repeat(n: int, gap: float = 0.0) -> dict:
    """Repeat a move n times with optional gap between [s]."""
    return {"type": "repeat", "n": n, "gap": gap}


def seq_repeat_variation(n: int = 3, energy_delta: float = 0.1,
                         scale_delta: float = 0.0, gap: float = 0.0) -> dict:
    """Repeat n times with slight variation each iteration.

    energy_delta > 0 → each rep slightly more energetic (A → A' → A'').
    energy_delta < 0 → each rep slightly less energetic.
    scale_delta  > 0 → radius grows each rep (same sign logic).

    Args:
        n: Number of repetitions.
        energy_delta: Energy change per rep (additive, clamped to [0, 1]).
        scale_delta: Fractional radius change per rep (0 = unchanged).
        gap: Pause between reps [s].
    """
    return {"type": "repeat_variation", "n": n,
            "energy_delta": energy_delta, "scale_delta": scale_delta, "gap": gap}


def seq_alternate(other_move: str, n: int, gap: float = 0.0,
                  other_params: dict = None) -> dict:
    """Interleave this move with other_move, n pairs total (A-B × n)."""
    result = {"type": "alternate", "other_move": other_move, "n": n, "gap": gap}
    if other_params:
        result["other_params"] = other_params
    return result


def seq_asymmetric_pause(short: float = 0.2, long: float = 0.8, n: int = 4) -> dict:
    """Repeat with alternating short/long pauses.

    The uneven rhythm lets the audience see the robot "deciding",
    creating tension and anticipation between identical moves.
    """
    return {"type": "asymmetric_pause", "short": short, "long": long, "n": n}


# ── Transformation ────────────────────────────────────────────────────────────

def seq_mirror(gap: float = 0.0) -> dict:
    """Run twice: original params then spatially mirrored params.

    Mirrors all spatial params simultaneously:
      side:      left ↔ right
      direction: forward ↔ backward, left ↔ right
      clockwise: True ↔ False
      angle:     positive ↔ negative
    """
    return {"type": "mirror", "gap": gap}


def seq_direction_flip(gap: float = 0.0) -> dict:
    """Run twice: original then direction/side/clockwise flipped.

    Similar to mirror but does NOT flip side independently —
    all directional params are flipped together.
    """
    return {"type": "direction_flip", "gap": gap}


def seq_invert(factor: float = 1.0) -> dict:
    """Invert dynamic qualities: energy becomes (1 - energy).

    Optionally scale the radius by factor to shrink/expand spatial footprint.
    Useful for contrast: a large, strong move followed by a small, gentle one.

    Args:
        factor: Spatial scale multiplier applied to radius (default 1.0 = unchanged).
    """
    return {"type": "invert", "factor": factor}


def seq_reverse() -> dict:
    """Placeholder for phrase-level temporal reversal.

    On a single Motif this is a no-op. Meaningful when applied to a Phrase
    (ABC → CBA), which requires phrase-level expansion not yet implemented.
    """
    return {"type": "reverse"}


# ── Parametric & Dynamic Modulation ──────────────────────────────────────────

def seq_scale(factor: float = 0.5) -> dict:
    """Scale spatial amplitude params (radius, distance) by factor.

    Use factor < 1 to shrink, factor > 1 to enlarge.
    Affects: radius, distance, max_speed, linear_speed (if present in params).
    """
    return {"type": "scale", "factor": factor}


def seq_speed_modulate(factor: float = 1.5) -> dict:
    """Multiply energy by factor. Values >1 speed up, <1 slow down."""
    return {"type": "speed_modulate", "factor": factor}


def seq_decay(n: int, factor: float = 0.7) -> dict:
    """Repeat n times with increasing gap between reps (energy fading).

    The gap grows each repetition, giving a slowing-down, winding-down quality.
    """
    return {"type": "decay", "n": n, "factor": factor}


def seq_crescendo(n: int, factor: float = 1.3) -> dict:
    """Repeat n times with decreasing gap between reps (urgency building).

    Each rep starts sooner than the last, creating increasing tension.
    """
    return {"type": "crescendo", "n": n, "factor": factor}


def seq_tension(hold_duration: float = 1.0) -> dict:
    """Add hold_duration seconds of stillness before the move (anticipation)."""
    return {"type": "tension", "hold_duration": hold_duration}


def seq_rhythm_shift(gap_scale: float = 0.7) -> dict:
    """Scale gap_before timing by gap_scale.

    gap_scale < 1 → tighten timing (syncopated, rushed feel).
    gap_scale > 1 → loosen timing (suspended, held feel).
    """
    return {"type": "rhythm_shift", "gap_scale": gap_scale}


# ── Organic Variation ─────────────────────────────────────────────────────────

def seq_drift(angle_delta: float = 15.0) -> dict:
    """Shift the angle param by angle_delta degrees.

    Adds a gradual directional deviation to arc/spin moves. On repeated use,
    the robot's path slowly curves — like drifting on a sloped floor.

    Args:
        angle_delta: Degrees to add to the move's angle param.
    """
    return {"type": "drift", "angle_delta": angle_delta}


def seq_env_modulation(bias: float = 0.0, resistance: float = 0.0) -> dict:
    """Apply simulated environmental forces to a move.

    env_bias       [rad/s]: Constant angular velocity offset added to every
                   Twist command — simulates a wind or slope that curves
                   the robot's path.

    env_resistance [0–1]:  Fraction by which linear speed is reduced —
                   simulates viscosity, mud, or friction-like drag.

    Args:
        bias: Angular bias [rad/s]. Positive = CCW lean.
        resistance: Speed reduction fraction [0–1]. 0 = no effect, 1 = stopped.
    """
    return {"type": "env_modulation", "env_bias": bias, "env_resistance": resistance}
