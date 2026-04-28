"""
Layer 3 — Choreographic Structure (Platform-Agnostic)

Provides high-level data structures (Motif, Phrase, Sequence) and an
AI-powered choreographer that generates full sequences from natural language
descriptions using the Google Gemini API.

This layer is entirely platform-agnostic. It expresses choreographic INTENT
(move names, energy, texture, timing) without knowing how any robot executes
the moves. The platform abstraction layer translates intent into motor commands.

Dancer Design Thinking — Choreography Layer Concepts
------------------------------------------------------
§1 Texture:          abstract movement quality (honey, staccato, ice, cloud, magnet)
§2 Marking:          energy=0.1 for low-power rehearsal / preview
§4 Motif Memory:     track signature moves, recall them to build personality
§4 Repetition+Dev:   A-A-A-B patterns via decay/growth modifiers
§4 Asymmetric Pause: the most intense part is often the stillness
§4 Reason/Intent:    annotation + phrase intent describe WHY, not just WHAT

Architecture
------------
Motif    : atomic unit — one named move + energy + texture + modifier
Phrase   : ordered list of Motifs with a name, intent, and trailing pause
Sequence : ordered list of Phrases with metadata (tempo, mood, title)

Workflow
--------
1. Programmatic: build Motif / Phrase / Sequence manually, call run_sequence().
2. AI-driven: instantiate AIChoreographer with a RobotPlatform,
   call .generate(description), receive a Sequence, then call run_sequence().

Usage — programmatic
---------------------
    from dance_manager.choreographer import Motif, Phrase, Sequence, run_sequence
    from dance_manager.movement_modifiers import seq_repeat, seq_crescendo

    sequence = Sequence(
        title="Simple Groove",
        tempo_bpm=120.0,
        mood="playful",
        phrases=[
            Phrase(name="intro", intent="greet the audience", motifs=[
                Motif("Glance", energy=0.6, texture="neutral"),
                Motif("WagWalk", energy=0.5, gap_before=0.3),
            ]),
            Phrase(name="climax", gap_after=1.0, motifs=[
                Motif("Tap", params={"side": "right"}, modifier=seq_crescendo(n=4), annotation="build up"),
                Motif("Spin", params={"angle": 360}, energy=0.9, texture="staccato"),
            ]),
            Phrase(name="outro", motifs=[
                Motif("Bow", energy=0.4, texture="honey"),
            ]),
        ],
    )
    run_sequence(action_client, sequence)

Usage — AI choreography (platform-aware)
-----------------------------------------
    import rclpy
    from dance_manager.dance_client import DanceActionClient
    from dance_manager.choreographer import AIChoreographer, run_sequence
    from dance_manager.platforms.differential_drive import DiffDrivePlatform

    rclpy.init()
    client = DanceActionClient()
    platform = DiffDrivePlatform(twist_pub)

    ai = AIChoreographer(api_key="YOUR_GEMINI_API_KEY", platform=platform)
    sequence = ai.generate(
        "A curious, exploratory dance: start cautious, then grow more playful "
        "and energetic, end with a graceful bow."
    )
    run_sequence(client, sequence)
"""

from __future__ import annotations

import json
import math
import random
import time
from dataclasses import dataclass, field
from typing import Optional


# ── Data Structures ───────────────────────────────────────────────────────────

@dataclass
class Motif:
    """The atomic unit of choreography: one named move with expressive intent.

    Attributes:
        move: A primitive move name recognised by the RobotPlatform (e.g. "Spin").
        params: Move-specific parameters (e.g. {"angle": 90}, {"direction": "forward"},
                {"side": "left"}). Passed to the platform for interpretation.
        energy: Expressive intensity [0.0-1.0]. Used to scale motion and gaps.
        texture: Movement quality preset name ("neutral", "honey", "staccato",
                 "ice", "cloud", "magnet"). Passed to the platform for
                 interpretation into motor parameters.
        gap_before: Explicit pause [s] inserted before sending this goal.
        modifier: Optional dict produced by a seq_* helper in movement_modifiers
                  (e.g. seq_repeat(4, gap=0.2)). Expanded by run_sequence.
        annotation: Human-readable note shown in logs. Has no effect on motion.
    """
    move: str
    params: dict = field(default_factory=dict)
    energy: float = 0.5
    texture: str = "neutral"
    gap_before: float = 0.0
    modifier: Optional[dict] = None
    annotation: str = ""


@dataclass
class Phrase:
    """An ordered list of Motifs (or nested Phrases) forming a choreographic phrase.

    A phrase is a breath of movement — it has a shape (build/sustain/release),
    a spatial intention, and may have a group modifier applied to all its motifs.

    motifs may contain Motif objects OR nested Phrase objects (for group operations
    that span multiple moves, like mirroring A+B+C together).

    Attributes:
        motifs:    List of Motif | Phrase objects.
        name:      Human-readable label.
        intent:    WHY this phrase exists — the choreographic reason.
        arc:       The phrase's dramatic shape:
                   "build" (growing tension), "sustain" (holding the peak),
                   "release" (letting go), "punctuate" (sharp accent),
                   "question" (unresolved, reaching), "answer" (resolving).
        spatial:   Intended spatial direction: "advance", "retreat", "circle",
                   "diagonal", "stay".
        gap_after: Seconds of stillness after the final motif.
        modifier:  Optional group-level modifier applied to ALL motifs in this
                   phrase as a unit.
    """
    motifs: list = field(default_factory=list)
    name: str = ""
    intent: str = ""
    arc: str = ""
    spatial: str = ""
    gap_after: float = 0.0
    modifier: Optional[dict] = None


@dataclass
class Section:
    """A macro-structural unit — a group of phrases sharing a dramatic role.

    A dance is organised into 3–5 sections (introduction, development,
    climax, resolution, bridge, coda), each with a clear choreographic purpose.
    Sections give the LLM a framework to think at the level of dramatic arc
    rather than individual moves.

    Attributes:
        name:         Human-readable section title.
        role:         Dramatic role: "introduction" | "development" | "climax" |
                      "resolution" | "bridge" | "coda".
        intention:    The choreographic purpose of this section (one sentence).
        effort:       Laban effort qualities dict:
                      {"weight": "strong"|"light", "time": "sudden"|"sustained",
                       "flow": "free"|"bound"}
        spatial_path: The robot's spatial journey: "circular", "advance",
                      "retreat", "diagonal", "stay", "return".
        phrases:      List of Phrase objects in this section.
        gap_after:    Seconds of stillness after the last phrase of the section.
    """
    name: str = ""
    role: str = ""
    intention: str = ""
    effort: dict = field(default_factory=dict)
    spatial_path: str = ""
    phrases: list = field(default_factory=list)
    gap_after: float = 0.0


@dataclass
class Sequence:
    """A complete choreographic score with macro structure and metadata.

    Attributes:
        sections:     Ordered list of Section objects (preferred — gives macro structure).
        phrases:      Flat list of Phrase objects (backward-compat, used when no sections).
        title:        Human-readable title of the dance.
        tempo_bpm:    Musical tempo used to scale gap timing globally.
        form:         Choreographic form: "ABA", "rondo", "theme-variations",
                      "through-composed", "free".
        energy_arc:   The energy/tension journey: "arch", "wave", "rising",
                      "falling", "flat".
        mood:         Single expressive descriptor (e.g. 'playful', 'dramatic').
        description:  One-sentence choreographic intention.
    """
    sections: list = field(default_factory=list)
    phrases: list = field(default_factory=list)
    title: str = ""
    tempo_bpm: float = 120.0
    form: str = "free"
    energy_arc: str = "arch"
    mood: str = "neutral"
    description: str = ""


# ── Motif Memory ─────────────────────────────────────────────────────────────

class MotifMemory:
    """Track used motifs and recall signature moves to build personality.

    Inspired by dancer "repeat but variate" — repeat a motif from earlier
    in a different context. This creates a "memory" for the audience and
    builds a recognizable personality for the robot.

    Usage:
        memory = MotifMemory()
        # Record moves as they execute
        memory.record("Tap")
        memory.record("Spin")
        # Get a signature move to recall
        sig = memory.get_signature_move()  # → "Tap" (most used)
        # Check if it's time to recall
        if memory.should_recall(current_index=10, total_moves=20):
            # Insert the signature move
            ...
    """

    def __init__(self, recall_interval: int = 5):
        """
        Args:
            recall_interval: Suggest a recall every N moves.
        """
        self._history: list[str] = []
        self._counts: dict[str, int] = {}
        self._recall_interval = recall_interval
        self._last_recall_index = -recall_interval  # allow first recall early

    def record(self, move_name: str) -> None:
        """Record a move that was just executed."""
        self._history.append(move_name)
        self._counts[move_name] = self._counts.get(move_name, 0) + 1

    def get_signature_move(self) -> Optional[str]:
        """Return the most-used move, or None if no history."""
        if not self._counts:
            return None
        return max(self._counts, key=self._counts.get)

    def should_recall(self, current_index: int, total_moves: int) -> bool:
        """Check if it's a good time to insert a signature move recall.

        Returns True if enough moves have passed since the last recall
        and we're not at the very beginning or end of the sequence.
        """
        if current_index < 3:  # too early
            return False
        if current_index >= total_moves - 2:  # too late
            return False
        return (current_index - self._last_recall_index) >= self._recall_interval

    def mark_recalled(self, index: int) -> None:
        """Mark that a recall was inserted at the given index."""
        self._last_recall_index = index

    def get_variation(self, move_name: str, available_moves: list[str]) -> str:
        """Get a variation of a move (same category if possible).

        For the "repeat but variate" concept — same move but the platform
        may execute it with different energy/texture.
        """
        return move_name  # simplest variation: same move, different context


# ── Sequence Runner ───────────────────────────────────────────────────────────

def run_sequence(action_client, sequence: Sequence, stage_tracker=None) -> None:  # noqa: C901
    """Execute a Sequence by sending goals to the DanceActionServer.

    Iterates through every Phrase and Motif in order. For each Motif:
    - Expands any modifier spec into a list of (move_name, gap_before, energy, texture) tuples.
    - Sleeps gap_before seconds before sending each goal.
    - Calls action_client.send_goal_and_wait() with move name, energy, and texture.

    After each Phrase, sleeps phrase.gap_after seconds.

    Args:
        action_client: An instance of DanceActionClient (or any object with
                       a .send_goal_and_wait(move_name, energy, texture) method).
                       For backward compatibility, also accepts clients with
                       .send_goal_and_wait(move_name) signature.
        sequence: A populated Sequence dataclass.
    """
    from dance_manager.dance_vocabulary import translate_params as _translate_params

    beat = 60.0 / max(1.0, sequence.tempo_bpm)
    memory = MotifMemory()

    total_moves = 0  # updated after flattening sections below
    move_index = 0

    _FLIP_MAP = {
        "left": "right", "right": "left",
        "forward": "backward", "backward": "forward",
    }

    def _flip_params(p: dict) -> dict:
        """Return a copy of p with direction, side, clockwise, and angle flipped."""
        f = dict(p)
        if "side" in f:
            f["side"] = _FLIP_MAP.get(f["side"], f["side"])
        if "direction" in f:
            f["direction"] = _FLIP_MAP.get(f["direction"], f["direction"])
        if "clockwise" in f:
            f["clockwise"] = not bool(f["clockwise"])
        if "angle" in f and isinstance(f["angle"], (int, float)):
            f["angle"] = -f["angle"]
        return f

    def _scale_params(p: dict, factor: float) -> dict:
        s = dict(p)
        for key in ("radius", "distance", "max_speed", "linear_speed"):
            if key in s and isinstance(s[key], (int, float)):
                s[key] = s[key] * factor
        return s

    def _apply_group_mod(items: list, mod: dict) -> list:
        """Apply a modifier to a whole group of (move, params, gap, energy, texture) tuples."""
        mtype = mod.get("type", "")
        gap = mod.get("gap", beat)

        if mtype == "mirror":
            mirrored = [
                (move, _flip_params(params), gap if i == 0 else g, energy, texture)
                for i, (move, params, g, energy, texture) in enumerate(items)
            ]
            return list(items) + mirrored

        elif mtype == "direction_flip":
            flipped = [
                (move, _flip_params(params), gap if i == 0 else g, energy, texture)
                for i, (move, params, g, energy, texture) in enumerate(items)
            ]
            return list(items) + flipped

        elif mtype == "repeat":
            n = mod.get("n", 2)
            result = list(items)
            for _ in range(n - 1):
                result.extend(
                    (move, params, gap if i == 0 else g, energy, texture)
                    for i, (move, params, g, energy, texture) in enumerate(items)
                )
            return result

        elif mtype == "repeat_variation":
            n = mod.get("n", 3)
            e_delta = mod.get("energy_delta", 0.1)
            result = []
            for rep in range(n):
                for i, (move, params, g, energy, texture) in enumerate(items):
                    new_e = max(0.0, min(1.0, energy + rep * e_delta))
                    new_g = gap if (rep > 0 and i == 0) else g
                    result.append((move, params, new_g, new_e, texture))
            return result

        elif mtype == "invert":
            return [
                (move, params, g, max(0.0, min(1.0, 1.0 - energy)), texture)
                for move, params, g, energy, texture in items
            ]

        elif mtype == "scale":
            factor = mod.get("factor", 0.5)
            return [
                (move, _scale_params(params, factor), g, energy, texture)
                for move, params, g, energy, texture in items
            ]

        elif mtype == "speed_modulate":
            factor = mod.get("factor", 1.5)
            return [
                (move, params, g, max(0.0, min(1.0, energy * factor)), texture)
                for move, params, g, energy, texture in items
            ]

        elif mtype == "crescendo":
            n = mod.get("n", 2)
            factor = mod.get("factor", 1.3)
            inter_gap = beat * (n - 1) * (factor - 1.0) * 0.5
            result = []
            for rep in range(n):
                gap_val = max(0.0, inter_gap - rep * beat * (factor - 1.0))
                result.extend(
                    (move, params, gap_val if (rep > 0 and i == 0) else g, energy, texture)
                    for i, (move, params, g, energy, texture) in enumerate(items)
                )
            return result

        elif mtype == "decay":
            n = mod.get("n", 2)
            factor = mod.get("factor", 0.7)
            decay_gap = 0.0
            result = []
            for rep in range(n):
                result.extend(
                    (move, params, max(0.0, decay_gap) if (rep > 0 and i == 0) else g, energy, texture)
                    for i, (move, params, g, energy, texture) in enumerate(items)
                )
                decay_gap += beat * (1.0 - factor)
            return result

        elif mtype == "tension":
            hold = mod.get("hold_duration", beat * 2)
            if not items:
                return items
            move, params, g, energy, texture = items[0]
            return [(move, params, g + hold, energy, texture)] + list(items[1:])

        return list(items)  # unknown modifier → pass through

    def _expand_items(items: list) -> list:
        """Recursively expand Motif | Phrase items into flat (move, params, gap, energy, texture) tuples."""
        flat = []
        for item in items:
            if isinstance(item, Phrase):
                sub = _expand_items(item.motifs)
                if item.modifier:
                    sub = _apply_group_mod(sub, item.modifier)
                flat.extend(sub)
            else:  # Motif
                flat.extend(_expand(item))
        return flat

    def _expand(motif: Motif) -> list:
        """Expand one Motif into a list of (move_name, params, gap_before, energy, texture) tuples."""
        mod = motif.modifier
        base_gap = motif.gap_before
        energy = motif.energy
        texture = motif.texture
        params = motif.params

        if mod is None:
            return [(motif.move, params, base_gap, energy, texture)]

        mtype = mod.get("type", "")

        # ── Repetition & Pattern ─────────────────────────────────────────────
        if mtype == "repeat":
            n = mod.get("n", 1)
            gap = mod.get("gap", 0.0)
            return [(motif.move, params, base_gap if i == 0 else gap, energy, texture)
                    for i in range(n)]

        if mtype == "repeat_variation":
            n = mod.get("n", 3)
            e_delta = mod.get("energy_delta", 0.1)
            s_delta = mod.get("scale_delta", 0.0)
            gap = mod.get("gap", beat)
            pairs = []
            for i in range(n):
                e = max(0.0, min(1.0, energy + i * e_delta))
                p = dict(params)
                if s_delta != 0.0 and "radius" in p and isinstance(p["radius"], (int, float)):
                    p["radius"] = p["radius"] * (1.0 + i * s_delta)
                pairs.append((motif.move, p, base_gap if i == 0 else gap, e, texture))
            return pairs

        if mtype == "alternate":
            other = mod.get("other_move", motif.move)
            other_params = mod.get("other_params", {})
            n = mod.get("n", 2)
            gap = mod.get("gap", 0.0)
            pairs = []
            for i in range(n):
                pairs.append((motif.move, params, base_gap if i == 0 else gap, energy, texture))
                pairs.append((other, other_params, gap, energy, texture))
            return pairs

        if mtype == "asymmetric_pause":
            short = mod.get("short", 0.2)
            long_ = mod.get("long", 0.8)
            n = mod.get("n", 2)
            pairs = []
            for i in range(n):
                pause = short if i % 2 == 0 else long_
                pairs.append((motif.move, params, base_gap if i == 0 else pause, energy, texture))
            return pairs

        # ── Transformation ───────────────────────────────────────────────────
        if mtype == "mirror":
            gap = mod.get("gap", 0.0)
            return [(motif.move, params, base_gap, energy, texture),
                    (motif.move, _flip_params(params), gap, energy, texture)]

        if mtype == "direction_flip":
            gap = mod.get("gap", 0.0)
            return [(motif.move, params, base_gap, energy, texture),
                    (motif.move, _flip_params(params), gap, energy, texture)]

        if mtype == "invert":
            factor = mod.get("factor", 1.0)
            inv_energy = max(0.0, min(1.0, 1.0 - energy))
            inv_params = dict(params)
            if factor != 1.0 and "radius" in inv_params and isinstance(inv_params["radius"], (int, float)):
                inv_params["radius"] = inv_params["radius"] * factor
            return [(motif.move, inv_params, base_gap, inv_energy, texture)]

        if mtype == "reverse":
            # Single motif — no-op (reversal is meaningful only at phrase level)
            return [(motif.move, params, base_gap, energy, texture)]

        # ── Parametric & Dynamic Modulation ─────────────────────────────────
        if mtype == "scale":
            factor = mod.get("factor", 0.5)
            scaled = dict(params)
            for key in ("radius", "distance", "max_speed", "linear_speed"):
                if key in scaled and isinstance(scaled[key], (int, float)):
                    scaled[key] = scaled[key] * factor
            return [(motif.move, scaled, base_gap, energy, texture)]

        if mtype == "speed_modulate":
            factor = mod.get("factor", 1.5)
            new_e = max(0.0, min(1.0, energy * factor))
            return [(motif.move, params, base_gap, new_e, texture)]

        if mtype == "decay":
            n = mod.get("n", 3)
            factor = mod.get("factor", 0.7)
            pairs = []
            gap = base_gap
            for i in range(n):
                pairs.append((motif.move, params, max(0.0, gap), energy, texture))
                gap += beat * (1.0 - factor)
            return pairs

        if mtype == "crescendo":
            n = mod.get("n", 3)
            factor = mod.get("factor", 1.3)
            pairs = []
            gap = base_gap + beat * (n - 1) * (factor - 1.0) * 0.5
            for i in range(n):
                pairs.append((motif.move, params, max(0.0, gap), energy, texture))
                gap -= beat * (factor - 1.0)
            return pairs

        if mtype == "tension":
            hold = mod.get("hold_duration", 1.0)
            return [(motif.move, params, base_gap + hold, energy, texture)]

        if mtype == "rhythm_shift":
            gap_scale = mod.get("gap_scale", 0.7)
            return [(motif.move, params, max(0.0, base_gap * gap_scale), energy, texture)]

        # ── Organic Variation ────────────────────────────────────────────────
        if mtype == "drift":
            angle_delta = mod.get("angle_delta", 15.0)
            drifted = dict(params)
            if "angle" in drifted and isinstance(drifted["angle"], (int, float)):
                drifted["angle"] = drifted["angle"] + angle_delta
            return [(motif.move, drifted, base_gap, energy, texture)]

        if mtype == "env_modulation":
            env_params = {**params,
                          "env_bias": float(mod.get("env_bias", 0.0)),
                          "env_resistance": float(mod.get("env_resistance", 0.0))}
            return [(motif.move, env_params, base_gap, energy, texture)]

        # Unknown modifier type — fall back to bare move
        return [(motif.move, params, base_gap, energy, texture)]

    def _send_goal(move_name, params=None, energy=0.5, texture="neutral"):
        """Send goal with params support."""
        action_client.send_goal_and_wait(move_name, energy, texture,
                                         params=params or {})

    # Flatten sections → phrases (sections take priority over flat phrases list)
    all_phrases = []
    for section in sequence.sections:
        if section.name:
            print(f"[Choreographer] ═══ Section: {section.name} ({section.role}) ═══")
            if section.intention:
                print(f"[Choreographer]   Intention: {section.intention}")
        all_phrases.extend(section.phrases)
        if section.gap_after > 0.0:
            # Insert sentinel phrase for section gap
            all_phrases.append(Phrase(gap_after=section.gap_after))
    if not all_phrases:
        all_phrases = sequence.phrases

    for phrase in all_phrases:
        if phrase.name:
            arc_str = f" [{phrase.arc}]" if phrase.arc else ""
            intent_str = f" — {phrase.intent}" if phrase.intent else ""
            print(f"[Choreographer] Phrase: {phrase.name}{arc_str}{intent_str}")

        # Recursively expand all items (Motif | nested Phrase groups)
        phrase_expanded = _expand_items(phrase.motifs)

        # Apply phrase-level group modifier (e.g. seq_mirror wrapping the whole phrase)
        if phrase.modifier:
            phrase_expanded = _apply_group_mod(phrase_expanded, phrase.modifier)

        for move_name, params, gap, energy, texture in phrase_expanded:
            if gap > 0.0:
                time.sleep(gap)
            params_str = f" {params}" if params else ""
            print(f"[Choreographer]   {move_name}{params_str} (e={energy:.1f} t={texture})")

            translated = _translate_params(params, tempo_bpm=sequence.tempo_bpm)
            _send_goal(move_name, translated, energy, texture)
            memory.record(move_name)
            move_index += 1

            if stage_tracker is not None:
                stage_tracker.log_position(label=move_name)

        if phrase.gap_after > 0.0:
            time.sleep(phrase.gap_after)


# ── AI Choreographer ──────────────────────────────────────────────────────────

class AIChoreographer:
    """Generate Sequence objects from natural language using the Google Gemini API.

    Platform-aware: queries the loaded RobotPlatform for available moves
    and capabilities, so it generates choreography appropriate for any robot.

    Args:
        api_key (str): Google Gemini API key.
        platform: Optional RobotPlatform instance. If provided, the AI uses
                  the platform's available moves and description. If None,
                  falls back to the default differential drive move set.
        model (str): Gemini model ID.
    """

    # Fallback move list when no platform is provided
    DEFAULT_MOVES = [
        "Glance", "Bow",
        "Step", "Glide",
        "Shimmy", "Pulse", "Vibrate",
        "Tap", "Pirouette",
        "Spin",
        "Zigzag", "Slalom", "WagWalk",
        "Arc", "TeacupSpin", "TeacupCircle",
        "Spiral", "FigureEight", "Flower",
        "Pacing", "SuddenStop", "ChaineTurns",
    ]

    MODIFIER_SCHEMA = """\
Motif-level modifier (optional, null for no modifier):
  Repetition — make a move recur:
    {"type":"repeat",           "n":<int>,  "gap":<float s between repeats>}
    {"type":"repeat_variation", "n":<int>,  "energy_delta":<float>, "gap":<float>}
    {"type":"alternate",        "other_move":"<name>", "n":<int>, "gap":<float>}
    {"type":"asymmetric_pause", "short":<float>, "long":<float>, "n":<int>}
  Spatial transformation — flip direction or size:
    {"type":"mirror",           "gap":<float>}
    {"type":"direction_flip",   "gap":<float>}
    {"type":"scale",            "factor":<float, e.g. 0.5=half size>}
  Dynamic shaping — change energy or timing:
    {"type":"speed_modulate",   "factor":<float, >1=faster>}
    {"type":"crescendo",        "n":<int>,  "factor":<float >1>}
    {"type":"decay",            "n":<int>,  "factor":<float 0-1>}
    {"type":"tension",          "hold_duration":<float s, pause before move>}
    {"type":"rhythm_shift",     "gap_scale":<float>}
  Organic — subtle drift:
    {"type":"drift",            "angle_delta":<float degrees>}

Phrase-level modifier (applies to ALL motifs in a phrase as a unit):
  Same format — use when a structural operation (repeat, mirror, crescendo)
  should apply to the whole phrase, not a single move.\
"""

    TEXTURE_OPTIONS = "neutral, honey, staccato, ice, cloud, magnet"

    SYSTEM_PROMPT_TEMPLATE = """\
You are an expert dance choreographer programming a robot dancer. \
Think like a choreographer, not a programmer. \
Generate dance sequences as strict JSON — no prose, no markdown fences.

━━ Robot platform ━━
{platform_description}

━━ Available moves ━━
{move_list}

━━ Expressive parameters ━━
energy      float 0–1   0=restrained/slow, 0.5=moderate, 1=explosive/fast
texture     string      one of: {texture_options}
            neutral  = balanced, clean motion
            honey    = viscous, slow onset, high damping — sustained, weighty movement
            staccato = instant torque, abrupt stops — sharp, percussive, accented
            ice      = frictionless gliding, minimal damping — smooth, continuous flow
            cloud    = floaty, gentle, airy, exponential ramp — light, ethereal movement
            magnet   = push-pull dynamics — elastic, magnetic attraction/repulsion
gap_before  float [s]   silence before this move: 0=bound (tight), 0.5-1.5=suspended (free)

━━ Choreographic form ━━
Every dance needs a macro-structure. Choose the form that fits the intention:
  ABA             Intro (A) → Development/contrast (B) → Return/resolution (A')
                  Most satisfying — gives closure by returning to where you started.
  Rondo           A→B→A→C→A — a theme returns between contrasting episodes.
                  Creates familiarity and surprise alternately.
  Theme+Variations  Establish a signature movement, then systematically transform it.
                  Lets the audience learn one idea and watch it evolve.
  Through-composed  Continuous development, never exactly repeating.
                  For narrative journeys with a clear beginning, middle, end.
  Free              Organized by dramatic arc alone, no fixed return.

━━ Dramatic arc (energy_arc) ━━
The energy/tension journey across the WHOLE dance:
  arch     low → rise → single peak → fall back. Most natural, satisfying.
  wave     multiple peaks and valleys — for playful, oscillating pieces.
  rising   builds continuously from start to end — for celebratory, triumphant pieces.
  falling  starts at peak, winds down — for melancholy, ending pieces.
  flat     consistent energy — for meditative, trance-like pieces (rare).

━━ Section roles ━━
Organise the dance into 3–5 sections. Each section has a clear dramatic role:
  introduction   Establish personality and mood. Moderate energy. Set the world.
  development    Build tension. Explore and transform the opening material.
  climax         The ONE peak moment. Maximum energy, commitment, and surprise.
  resolution     Wind down. Return to calm. Create closure. Echo of introduction.
  bridge         A contrasting episode (in Rondo/ABA). Different quality.
  coda           A brief final statement. Very low energy. Last impression.

━━ Effort qualities (Laban Movement Analysis) ━━
Each section has an overall effort quality that drives move and texture choices:
  weight: "strong" (powerful, large, committed) vs "light" (delicate, small, tentative)
  time:   "sudden" (sharp, accented, staccato texture) vs "sustained" (flowing, honey/cloud)
  flow:   "free" (abandoned, large gaps ok) vs "bound" (controlled, tight gaps)

Effort → texture/energy guide:
  strong + sudden + free   → energy 0.8-1.0, staccato, gaps 0.5-1.0s  (explosive, abandoned)
  strong + sudden + bound  → energy 0.7-0.9, staccato, gaps 0-0.3s    (powerful precision)
  strong + sustained + free → energy 0.6-0.8, honey or ice, gaps 0.3-0.8s (powerful flow)
  light + sudden + bound   → energy 0.3-0.6, staccato, gaps 0-0.2s   (playful, light-footed)
  light + sustained + free → energy 0.1-0.4, cloud, gaps 0.5-1.5s    (floaty, dreamy)
  light + sustained + bound → energy 0.2-0.5, honey, gaps 0-0.3s     (delicate, careful)

━━ Seven choreographic principles ━━

1. CONTRAST is the engine of interest.
   Adjacent sections/phrases must contrast in at least one dimension.
   After explosive staccato → give sustained honey. After advancing → retreat.
   Without contrast, the dance is monotonous regardless of how complex it is.

2. REPETITION creates meaning; VARIATION creates life.
   Repeat a move or motif 2-3 times to make it recognizable and give it weight.
   Then vary it (energy, direction, size, texture) to show development.
   A-A-A-B pattern: repeat 3 times identically, break the pattern on the 4th → surprise.

3. STILLNESS is the most powerful choreographic tool.
   A pause before a big move creates anticipation. Silence after a climax creates resonance.
   Use gap_before 0.8-1.5s before your climax moves.
   Choreograph the stillness — it is not empty space, it is held intention.

4. EVERY PHRASE HAS A SHAPE (arc).
   "build": preparation, growing tension — moves get slightly larger/faster
   "sustain": holding the peak — repeat the climax quality
   "release": letting go, resolution — energy drops, texture softens
   "punctuate": sharp exclamation or accent — brief, high energy, then silence
   "question": unresolved, reaching outward — ends on open move (Glance, Pacing)
   "answer": resolving a previous question — ends with commitment (Bow, Spiral)

5. THE CLIMAX is ONE moment, not a sustained plateau.
   Build steadily toward ONE peak phrase. Don't have multiple equal peaks — it flattens drama.
   The climax phrase: highest energy, most committed moves, tension modifier before it.
   After the climax: immediate contrast (low energy, long gap_after, soft texture).

6. SPATIAL JOURNEY matters choreographically.
   The robot's path through space is part of the expression, not just a byproduct of moves.
   Use spatial_path to show intention:
     circular  = exploration, searching, self-contained
     advance   = confidence, assertion, engagement
     retreat   = withdrawal, introspection, vulnerability
     diagonal  = dynamic, unexpected, breaking the grid
     return    = closure, memory, coming home

7. ENDINGS matter as much as beginnings.
   Mirror the opening to create closure (ABA works because the return gives meaning to the middle).
   End with low energy, a Bow, or a held stillness.
   The last 5 seconds is what the audience remembers.

━━ Modifiers ━━
{modifier_schema}

━━ Nested groups (for group operations on multiple moves) ━━
An item in "motifs" can be a nested group — useful when a structural operation
(mirror, repeat, crescendo) should apply to MULTIPLE moves together, not just one.

  Mirror a group of moves:
  {{"motifs": [A, B, C], "modifier": {{"type":"mirror","gap":0.4}}}}
  → plays A,B,C forward then A,B,C mirrored (directions flipped)

  Repeat a group with growing energy:
  {{"motifs": [A, B], "modifier": {{"type":"repeat_variation","n":3,"energy_delta":0.15}}}}

Use nested groups WHEN the structure genuinely serves the choreographic idea.
Do not nest purely for complexity — simple is often more expressive.

━━ Output JSON schema ━━
{{
  "title": "<string>",
  "tempo_bpm": <number 60–160>,
  "form": "<ABA|rondo|theme-variations|through-composed|free>",
  "energy_arc": "<arch|wave|rising|falling|flat>",
  "mood": "<string>",
  "description": "<one sentence choreographic intention>",
  "sections": [
    {{
      "name": "<string>",
      "role": "<introduction|development|climax|resolution|bridge|coda>",
      "intention": "<string — choreographic purpose of this section>",
      "effort": {{"weight":"<strong|light>","time":"<sudden|sustained>","flow":"<free|bound>"}},
      "spatial_path": "<circular|advance|retreat|diagonal|stay|return>",
      "gap_after": <float>,
      "phrases": [
        {{
          "name": "<string>",
          "arc": "<build|sustain|release|punctuate|question|answer>",
          "intent": "<string — WHY this phrase exists>",
          "spatial": "<advance|retreat|circle|diagonal|stay>",
          "gap_after": <float>,
          "modifier": <group modifier for whole phrase, or null>,
          "motifs": [
            <individual move OR nested group — see below>
          ]
        }}
      ]
    }}
  ]
}}

━━ Motif formats ━━
Individual move:
{{
  "move": "<MOVE_NAME>",
  "params": {{<move-specific params or {{}}>}},
  "energy": <float 0-1>,
  "texture": "<texture_name>",
  "gap_before": <float>,
  "modifier": <motif-level modifier or null>,
  "annotation": "<string, under 50 chars>"
}}

Nested group (for group structural operations):
{{
  "motifs": [<individual moves...>],
  "modifier": <modifier applied to the group as a unit>,
  "intent": "<optional: why this group>"
}}

━━ Move parameters ━━
  Step:         {{"direction":"forward"|"backward"}}
  Glide:        {{"direction":"forward"|"backward"}}
  Spin:         {{"angle":<degrees, +CCW/-CW, e.g. 90, -180, 360>}}
  Arc:          {{"direction":"left"|"right","angle":<degrees, default 180>}}
  Tap:          {{"side":"left"|"right"}}
  Pirouette:    {{"side":"left"|"right"}}
  Zigzag:       {{"direction":"forward"|"backward"}}
  Slalom:       {{"direction":"forward"|"backward"}}
  TeacupSpin:   {{"side":"left"|"right"}}
  TeacupCircle: {{"direction":"left"|"right"}}
  Spiral:       {{"direction":"left"|"right"}}
  Pacing:       {{"distance":<m>,"step_duration":<s>,"repetitions":<int>,"pause_duration":<s>}}
  SuddenStop:   {{"direction":"forward"|"backward","max_speed":<m/s>,"run_duration":<s>}}
  ChaineTurns:  {{"turns":<float>,"half_turn_duration":<s>}}
  Glance, Bow, Shimmy, Pulse, Vibrate, WagWalk, FigureEight, Flower: {{}}

{vocabulary_description}

━━ Quality rules ━━
- Budget ~3–8 seconds per move. Total dance: 30–120s unless specified.
- Never invent move names — only use the list above.
- Keep annotations under 50 chars.
- Return ONLY the JSON object. No markdown fences, no extra text.
- Every section should be distinctly different in effort quality from adjacent sections.
- The climax section must have the highest energy of the whole dance.
- The resolution section must have lower energy than the introduction.
{stage_constraints}\
"""

    def __init__(self, api_key: str, platform=None, model: str = "gpt-4o",
                 stage_width: float = 0.0, stage_depth: float = 0.0):
        try:
            from openai import OpenAI
        except ImportError as exc:
            raise ImportError(
                "The 'openai' package is required for AIChoreographer. "
                "Install it with: pip install openai"
            ) from exc
        self._client = OpenAI(api_key=api_key)
        self._model = model
        self._platform = platform
        self._stage_width = stage_width
        self._stage_depth = stage_depth

    def _get_available_moves(self) -> list[str]:
        if self._platform is not None:
            return self._platform.get_available_moves()
        return self.DEFAULT_MOVES

    def _get_move_list_str(self) -> str:
        if self._platform is not None and hasattr(self._platform, 'get_move_categories'):
            categories = self._platform.get_move_categories()
            lines = []
            for cat, moves in categories.items():
                lines.append(f"{cat.upper():12s}: {', '.join(moves)}")
            return "\n".join(lines)
        # Fallback: flat list
        return ", ".join(self._get_available_moves())

    def _get_platform_description(self) -> str:
        if self._platform is not None:
            return self._platform.get_platform_description()
        return (
            "A differential-drive dance robot with two wheels. "
            "It can move forward/backward, spin in place, pivot around one wheel, "
            "and drive arcs, spirals, figure-eights, and flower curves."
        )

    def _get_displacement_str(self) -> str:
        """Format per-move displacement info for the AI prompt."""
        if self._platform is None or not hasattr(self._platform, 'get_move_displacements'):
            return ""
        displacements = self._platform.get_move_displacements()
        lines = []
        for name, d in displacements.items():
            parts = []
            if d.get("dx", 0) != 0:
                parts.append(f"fwd={d['dx']:+.1f}m")
            if d.get("dy", 0) != 0:
                parts.append(f"lat={d['dy']:+.1f}m")
            if d.get("dtheta", 0) != 0:
                deg = math.degrees(d["dtheta"])
                parts.append(f"turn={deg:+.0f}deg")
            if d.get("radius", 0) > 0:
                parts.append(f"sweep={d['radius']:.1f}m")
            if d.get("returns", False):
                parts.append("returns-to-start")
            if parts:
                lines.append(f"  {name:28s} {', '.join(parts)}")
            else:
                lines.append(f"  {name:28s} in-place, no displacement")
        return "\n".join(lines)

    def _get_stage_constraints_str(self) -> str:
        """Build the stage boundary section for the system prompt."""
        if self._stage_width <= 0 and self._stage_depth <= 0:
            return ""

        displacement_table = self._get_displacement_str()

        parts = ["\n━━ Stage boundary constraints ━━"]
        if self._stage_width > 0 and self._stage_depth > 0:
            parts.append(
                f"Stage size: {self._stage_width:.1f}m wide x {self._stage_depth:.1f}m deep.")
            parts.append(f"The robot starts at stage center (0, 0). Boundaries are:")
            parts.append(f"  Forward/backward: +/- {self._stage_depth / 2:.1f}m")
            parts.append(f"  Left/right:       +/- {self._stage_width / 2:.1f}m")
        elif self._stage_width > 0:
            parts.append(
                f"Stage width: {self._stage_width:.1f}m. "
                f"Left/right: +/- {self._stage_width / 2:.1f}m from center.")
        else:
            parts.append(
                f"Stage depth: {self._stage_depth:.1f}m. "
                f"Forward/backward: +/- {self._stage_depth / 2:.1f}m from center.")

        if displacement_table:
            parts.append("")
            parts.append("Approximate displacement per move (at nominal energy):")
            parts.append(displacement_table)

        parts.append("")
        parts.append("IMPORTANT: Mentally track the robot's cumulative (x, y) position as you "
                      "build the sequence.")
        parts.append("After a heading change (e.g., Spin90CW), forward moves go in the NEW "
                      "heading direction.")
        parts.append("Do not plan moves that would take the robot beyond the stage boundaries.")
        parts.append("Prefer in-place and returning moves when near the edges.")
        parts.append("If unsure, use smaller moves (Step over Glide, Glide over Slalom).")

        return "\n".join(parts)

    def generate(self, description: str, max_retries: int = 2) -> Sequence:
        """Generate a Sequence from a natural language choreography description.

        Args:
            description: Human description of the desired dance.
            max_retries: How many times to ask the model to fix invalid JSON.

        Returns:
            A populated Sequence dataclass.

        Raises:
            ValueError: If the response cannot be parsed after max_retries.
        """
        from dance_manager.dance_vocabulary import get_vocabulary_description

        system = self.SYSTEM_PROMPT_TEMPLATE.format(
            platform_description=self._get_platform_description(),
            move_list=self._get_move_list_str(),
            texture_options=self.TEXTURE_OPTIONS,
            modifier_schema=self.MODIFIER_SCHEMA,
            vocabulary_description=get_vocabulary_description(),
            stage_constraints=self._get_stage_constraints_str(),
        )
        messages = [
            {"role": "system", "content": system},
            {"role": "user",   "content": description},
        ]

        for attempt in range(max_retries + 1):
            response = self._client.chat.completions.create(
                model=self._model,
                messages=messages,
                response_format={"type": "json_object"},
                max_tokens=8192,
            )
            raw = response.choices[0].message.content.strip()

            try:
                data = self._parse_json(raw)
                return self._dict_to_sequence(data)
            except (json.JSONDecodeError, KeyError, ValueError) as exc:
                if attempt < max_retries:
                    messages.append({"role": "assistant", "content": raw})
                    messages.append({
                        "role": "user",
                        "content": (
                            f"That response was invalid: {exc}. "
                            "Please return only the JSON object, no other text."
                        ),
                    })
                else:
                    raise ValueError(
                        f"Could not parse AI response after {max_retries} retries: {exc}\n"
                        f"Raw output:\n{raw}"
                    ) from exc

    def _parse_json(self, text: str) -> dict:
        import re
        text = text.strip()
        # Strip markdown fences
        if text.startswith("```"):
            text = text[text.find("\n") + 1:]
            if "```" in text:
                text = text[: text.rfind("```")]
        text = text.strip()
        # Remove trailing commas before } or ] (common LLM mistake)
        text = re.sub(r",\s*([}\]])", r"\1", text)
        return json.loads(text)

    def _dict_to_sequence(self, data: dict) -> Sequence:
        valid = set(self._get_available_moves())
        valid_textures = {"neutral", "honey", "staccato", "ice", "cloud", "magnet"}

        def _parse_item(item: dict):
            """Parse a dict as either a Motif (has 'move') or a nested Phrase group (has 'motifs')."""
            if "move" in item:
                move = item.get("move", "")
                if move not in valid:
                    raise ValueError(f"Unknown move '{move}'. Valid: {sorted(valid)}")
                texture = str(item.get("texture", "neutral")).lower()
                if texture not in valid_textures:
                    texture = "neutral"
                return Motif(
                    move=move,
                    params=item.get("params", {}),
                    energy=float(item.get("energy", 0.5)),
                    texture=texture,
                    gap_before=float(item.get("gap_before", 0.0)),
                    modifier=item.get("modifier"),
                    annotation=str(item.get("annotation", "")),
                )
            elif "motifs" in item:
                sub_items = [_parse_item(sub) for sub in item.get("motifs", [])]
                return Phrase(
                    motifs=sub_items,
                    name=str(item.get("name", "")),
                    intent=str(item.get("intent", "")),
                    arc=str(item.get("arc", "")),
                    spatial=str(item.get("spatial", "")),
                    gap_after=float(item.get("gap_after", 0.0)),
                    modifier=item.get("modifier"),
                )
            else:
                raise ValueError(f"Item must have 'move' or 'motifs' key: {list(item.keys())}")

        def _parse_phrase(ph: dict) -> Phrase:
            items = [_parse_item(it) for it in ph.get("motifs", [])]
            return Phrase(
                motifs=items,
                name=str(ph.get("name", "")),
                intent=str(ph.get("intent", "")),
                arc=str(ph.get("arc", "")),
                spatial=str(ph.get("spatial", "")),
                gap_after=float(ph.get("gap_after", 0.0)),
                modifier=ph.get("modifier"),
            )

        # Parse sections (new format) or fall back to flat phrases (old format)
        sections = []
        for sec in data.get("sections", []):
            phrases = [_parse_phrase(ph) for ph in sec.get("phrases", [])]
            sections.append(Section(
                name=str(sec.get("name", "")),
                role=str(sec.get("role", "")),
                intention=str(sec.get("intention", "")),
                effort=dict(sec.get("effort", {})),
                spatial_path=str(sec.get("spatial_path", "")),
                phrases=phrases,
                gap_after=float(sec.get("gap_after", 0.0)),
            ))

        flat_phrases = []
        if not sections:
            flat_phrases = [_parse_phrase(ph) for ph in data.get("phrases", [])]

        return Sequence(
            sections=sections,
            phrases=flat_phrases,
            title=str(data.get("title", "")),
            tempo_bpm=float(data.get("tempo_bpm", 120.0)),
            form=str(data.get("form", "free")),
            energy_arc=str(data.get("energy_arc", "arch")),
            mood=str(data.get("mood", "neutral")),
            description=str(data.get("description", "")),
        )

    def describe(self, sequence: Sequence) -> str:
        """Return a human-readable summary of a Sequence for debugging."""
        lines = [
            f"Title:      {sequence.title}",
            f"Form:       {sequence.form}  Energy arc: {sequence.energy_arc}",
            f"Mood:       {sequence.mood}",
            f"Tempo:      {sequence.tempo_bpm} BPM",
            f"Intention:  {sequence.description}",
            "",
        ]

        def _desc_phrase(phrase, indent="  "):
            arc_str = f" [{phrase.arc}]" if phrase.arc else ""
            intent_str = f" — {phrase.intent}" if phrase.intent else ""
            lines.append(f"{indent}[{phrase.name}]{arc_str}{intent_str}")
            for item in phrase.motifs:
                if isinstance(item, Phrase):
                    mod_str = f" mod={item.modifier}" if item.modifier else ""
                    lines.append(f"{indent}  <group{mod_str}>")
                    for sub in item.motifs:
                        if isinstance(sub, Motif):
                            lines.append(f"{indent}    {sub.move:<24} e={sub.energy:.1f} {sub.texture}")
                else:  # Motif
                    mod_str = f"  mod={item.modifier}" if item.modifier else ""
                    note = f"  # {item.annotation}" if item.annotation else ""
                    lines.append(
                        f"{indent}  {item.move:<26} e={item.energy:.1f}"
                        f"  {item.texture:<10}  gap={item.gap_before:.1f}s{mod_str}{note}"
                    )
            if phrase.gap_after:
                lines.append(f"{indent}  ··· pause {phrase.gap_after:.1f}s")

        if sequence.sections:
            for section in sequence.sections:
                effort_str = " | ".join(f"{k}:{v}" for k, v in section.effort.items()) if section.effort else ""
                lines.append(f"═══ {section.name.upper()} ({section.role}) ═══")
                if section.intention:
                    lines.append(f"  Intention: {section.intention}")
                if effort_str:
                    lines.append(f"  Effort: {effort_str}  Path: {section.spatial_path}")
                lines.append("")
                for phrase in section.phrases:
                    _desc_phrase(phrase, indent="  ")
                if section.gap_after:
                    lines.append(f"  ··· section pause {section.gap_after:.1f}s")
                lines.append("")
        else:
            for phrase in sequence.phrases:
                _desc_phrase(phrase, indent="")
                lines.append("")

        return "\n".join(lines)


# ── CLI entry point ───────────────────────────────────────────────────────────

def main():
    """CLI: generate a choreography from a text description.

    Usage (after building the package):
        ros2 run dance_manager choreographer "An excited celebratory dance"

    Set the GOOGLE_API_KEY environment variable before running, or edit
    the api_key argument below.

    Pass --dry-run to print the plan without executing on the robot.
    """
    import os
    import sys
    import argparse

    parser = argparse.ArgumentParser(description="AI Dance Choreographer")
    parser.add_argument("description", nargs="?",
                        default="A playful, curious exploration with a joyful finale.",
                        help="Natural language choreography description")
    parser.add_argument("--dry-run", action="store_true",
                        help="Print the generated sequence without executing")
    parser.add_argument("--model", default="gemini-2.5-flash",
                        help="Gemini model ID")
    parser.add_argument("--stage-width", type=float, default=0.0,
                        help="Stage width [m]. 0 = no boundary constraint.")
    parser.add_argument("--stage-depth", type=float, default=0.0,
                        help="Stage depth [m]. 0 = no boundary constraint.")
    args = parser.parse_args()

    api_key = os.environ.get("GOOGLE_API_KEY", "")
    if not api_key:
        print("Error: set the GOOGLE_API_KEY environment variable.", file=sys.stderr)
        sys.exit(1)

    if args.stage_width > 0 or args.stage_depth > 0:
        print(f"Stage bounds: {args.stage_width}m wide x {args.stage_depth}m deep")

    print(f"Generating choreography for: {args.description!r}")
    ai = AIChoreographer(api_key=api_key, model=args.model,
                         stage_width=args.stage_width, stage_depth=args.stage_depth)
    sequence = ai.generate(args.description)

    print("\n" + ai.describe(sequence))

    if args.dry_run:
        print("[dry-run] Skipping robot execution.")
        return

    import rclpy
    from dance_manager.dance_client import DanceActionClient

    rclpy.init()
    client = DanceActionClient()

    stage_tracker = None
    if args.stage_width > 0 or args.stage_depth > 0:
        from dance_manager.stage_tracker import StageTracker
        stage_tracker = StageTracker(
            client, stage_width=args.stage_width, stage_depth=args.stage_depth)

    try:
        run_sequence(client, sequence, stage_tracker=stage_tracker)
    finally:
        if stage_tracker:
            stage_tracker.destroy()
        client.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
