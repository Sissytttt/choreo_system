"""
Dance Vocabulary — Layer 2 Parameter Mapping

Provides a formal translation from dance-language parameter values to the
technical values expected by motion primitive functions.

The LLM and human users may specify parameters using dance terminology
(e.g. "3 o'clock", "large", "ease-in"). This module translates those terms
into exact numeric/string values.

Supported translations
----------------------
direction       : clock positions / stage directions → "forward"/"backward"/"left"/"right" + optional angle
spatial_scale   : "small"/"large"/etc → radius [m]
speed_quality   : "slow"/"fast"/etc → linear_speed and max_speed [m/s]
beats           : N or "N beats" → duration [s] (uses tempo_bpm)
pause_quality   : "breath"/"short"/etc → pause_duration [s]
accel_profile   : "ease-in"/"sharp"/etc → ramp_up_duration + ramp_down_duration [s]
spin_direction  : "clockwise"/"CCW"/etc → clockwise [bool]
intensity_quality: "light"/"strong"/etc → intensity [0–1]

All other keys are passed through unchanged.

Example
-------
    from dance_manager.dance_vocabulary import translate_params

    params = {"direction": "3 o'clock", "spatial_scale": "large", "beats": 4}
    result = translate_params(params, tempo_bpm=120.0)
    # → {"direction": "right", "side": "right", "radius": 1.2, "duration": 2.0}
"""

from __future__ import annotations


# ── Mapping Tables ────────────────────────────────────────────────────────────

# Clock positions and stage directions → technical direction params.
# Values are dicts merged into the params dict (may set direction, side, angle).
_DIRECTION_MAP: dict[str, dict] = {
    # 12 cardinal positions
    "12 o'clock":    {"direction": "forward"},
    "12 o clock":    {"direction": "forward"},
    "upstage":       {"direction": "forward"},
    "forward":       {"direction": "forward"},

    "6 o'clock":     {"direction": "backward"},
    "6 o clock":     {"direction": "backward"},
    "downstage":     {"direction": "backward"},
    "backward":      {"direction": "backward"},
    "back":          {"direction": "backward"},

    "3 o'clock":     {"direction": "right", "side": "right"},
    "3 o clock":     {"direction": "right", "side": "right"},
    "stage right":   {"direction": "right", "side": "right"},
    "right":         {"direction": "right", "side": "right"},

    "9 o'clock":     {"direction": "left",  "side": "left"},
    "9 o clock":     {"direction": "left",  "side": "left"},
    "stage left":    {"direction": "left",  "side": "left"},
    "left":          {"direction": "left",  "side": "left"},

    # Diagonal clock positions (set direction + angle in degrees for arc-based moves)
    "1 o'clock":        {"direction": "forward",  "angle": 30.0},
    "1 o clock":        {"direction": "forward",  "angle": 30.0},
    "2 o'clock":        {"direction": "forward",  "angle": 60.0},
    "2 o clock":        {"direction": "forward",  "angle": 60.0},
    "upstage right":    {"direction": "forward",  "angle": 45.0},

    "4 o'clock":        {"direction": "backward", "angle": 120.0},
    "4 o clock":        {"direction": "backward", "angle": 120.0},
    "5 o'clock":        {"direction": "backward", "angle": 150.0},
    "5 o clock":        {"direction": "backward", "angle": 150.0},
    "downstage right":  {"direction": "backward", "angle": 135.0},

    "7 o'clock":        {"direction": "backward", "angle": 210.0},
    "7 o clock":        {"direction": "backward", "angle": 210.0},
    "8 o'clock":        {"direction": "backward", "angle": 240.0},
    "8 o clock":        {"direction": "backward", "angle": 240.0},
    "downstage left":   {"direction": "backward", "angle": 225.0},

    "10 o'clock":       {"direction": "forward",  "angle": 300.0},
    "10 o clock":       {"direction": "forward",  "angle": 300.0},
    "11 o'clock":       {"direction": "forward",  "angle": 330.0},
    "11 o clock":       {"direction": "forward",  "angle": 330.0},
    "upstage left":     {"direction": "forward",  "angle": 315.0},
}

# Spatial scale → radius in meters
_SPATIAL_SCALE_MAP: dict[str, float] = {
    "tiny":   0.2,
    "small":  0.4,
    "medium": 0.7,
    "large":  1.2,
    "huge":   2.0,
}

# Speed quality → m/s (used for linear_speed and max_speed)
_SPEED_MAP: dict[str, float] = {
    "very slow":  0.10,
    "slow":       0.20,
    "medium":     0.35,
    "fast":       0.55,
    "very fast":  0.80,
    "explosive":  1.10,
}

# Pause quality → seconds
_PAUSE_MAP: dict[str, float] = {
    "none":    0.0,
    "breath":  0.2,
    "accent":  0.1,
    "short":   0.4,
    "medium":  0.8,
    "long":    1.5,
    "hold":    2.5,
}

# Acceleration profile → ramp_up_duration and ramp_down_duration in seconds
_ACCEL_PROFILE_MAP: dict[str, dict] = {
    "ease-in":     {"ramp_up_duration": 0.6,  "ramp_down_duration": 0.1},
    "ease-out":    {"ramp_up_duration": 0.1,  "ramp_down_duration": 0.6},
    "ease-in-out": {"ramp_up_duration": 0.4,  "ramp_down_duration": 0.4},
    "constant":    {"ramp_up_duration": 0.05, "ramp_down_duration": 0.05},
    "sharp":       {"ramp_up_duration": 0.02, "ramp_down_duration": 0.02},
    "gentle":      {"ramp_up_duration": 0.8,  "ramp_down_duration": 0.8},
}

# Intensity quality → 0–1 value
_INTENSITY_MAP: dict[str, float] = {
    "delicate":  0.1,
    "light":     0.3,
    "medium":    0.5,
    "strong":    0.7,
    "powerful":  0.9,
    "explosive": 1.0,
}

# Spin / rotation direction → clockwise bool
_SPIN_DIRECTION_MAP: dict[str, bool] = {
    "clockwise":         True,
    "cw":                True,
    "clock":             True,
    "counterclockwise":  False,
    "counter-clockwise": False,
    "ccw":               False,
    "anti-clockwise":    False,
}


# ── Translation ───────────────────────────────────────────────────────────────

def translate_params(params: dict, tempo_bpm: float = 120.0) -> dict:
    """Translate dance vocabulary parameters to technical values.

    Returns a new dict with recognised vocabulary keys replaced by their
    technical equivalents. Unrecognised keys are passed through unchanged.

    Args:
        params: Parameter dict, possibly containing dance vocabulary keys.
        tempo_bpm: Current sequence tempo in BPM; used to convert "beats" to seconds.

    Returns:
        New dict with vocabulary terms resolved to technical values.
    """
    if not params:
        return params

    result = dict(params)

    # ── direction ─────────────────────────────────────────────────────────────
    # Translate clock / stage direction strings. Already-valid values
    # ("forward", "backward", "left", "right") are still in the map, so they
    # resolve to the same canonical form (with side set when appropriate).
    if "direction" in result and isinstance(result["direction"], str):
        val = result["direction"].lower().strip()
        mapped = _DIRECTION_MAP.get(val)
        if mapped is not None:
            result.update(mapped)

    # ── spatial_scale → radius + track ───────────────────────────────────────
    if "spatial_scale" in result:
        val = str(result.pop("spatial_scale")).lower().strip()
        r = _SPATIAL_SCALE_MAP.get(val, 0.7)
        result.setdefault("radius", r)
        result.setdefault("track", r)

    # ── speed_quality → linear_speed + max_speed ──────────────────────────────
    if "speed_quality" in result:
        val = str(result.pop("speed_quality")).lower().strip()
        spd = _SPEED_MAP.get(val, 0.35)
        result.setdefault("linear_speed", spd)
        result.setdefault("max_speed", spd)
        result.setdefault("speed", spd)

    # ── beats → duration ──────────────────────────────────────────────────────
    if "beats" in result:
        raw = result.pop("beats")
        try:
            if isinstance(raw, (int, float)):
                n_beats = float(raw)
            else:
                # Accept "4 beats", "4", "4.0 beats"
                n_beats = float(str(raw).lower().replace("beats", "").replace("beat", "").strip())
            result.setdefault("duration", n_beats * (60.0 / max(1.0, tempo_bpm)))
        except (ValueError, TypeError):
            pass  # malformed — drop silently

    # ── pause_quality → pause_duration ────────────────────────────────────────
    if "pause_quality" in result:
        val = str(result.pop("pause_quality")).lower().strip()
        result.setdefault("pause_duration", _PAUSE_MAP.get(val, 0.5))

    # ── accel_profile → ramp_up_duration + ramp_down_duration ────────────────
    if "accel_profile" in result:
        val = str(result.pop("accel_profile")).lower().strip()
        ramps = _ACCEL_PROFILE_MAP.get(val)
        if ramps:
            result.update({k: v for k, v in ramps.items() if k not in result})

    # ── spin_direction / rotation_direction → clockwise ───────────────────────
    for key in ("spin_direction", "rotation_direction"):
        if key in result:
            val = str(result.pop(key)).lower().strip()
            cw = _SPIN_DIRECTION_MAP.get(val)
            if cw is not None:
                result.setdefault("clockwise", cw)

    # ── intensity_quality → intensity ─────────────────────────────────────────
    if "intensity_quality" in result:
        val = str(result.pop("intensity_quality")).lower().strip()
        result.setdefault("intensity", _INTENSITY_MAP.get(val, 0.5))

    return result


# ── LLM Prompt Description ───────────────────────────────────────────────────

def get_vocabulary_description() -> str:
    """Return a compact reference block for the LLM system prompt.

    Describes every vocabulary key with valid values and example usage.
    """
    return """\
━━ Dance Vocabulary (use in motif params) ━━
Instead of exact numbers, you may use expressive English terms in params.
All unknown keys pass through; mix vocabulary and technical params freely.

direction — clock position or stage term (also sets "side" when applicable)
  "12 o'clock"/"upstage"         → forward
  "6 o'clock"/"downstage"        → backward
  "3 o'clock"/"stage right"      → right  (also sets side="right")
  "9 o'clock"/"stage left"       → left   (also sets side="left")
  Diagonals: "1 o'clock"(30°), "2 o'clock"(60°), "4 o'clock"(120°),
             "5 o'clock"(150°), "7 o'clock"(210°), "8 o'clock"(240°),
             "10 o'clock"(300°), "11 o'clock"(330°)
  Stage diagonals: "upstage right"(45°), "upstage left"(315°),
                   "downstage right"(135°), "downstage left"(225°)
  Standard values still work: "forward", "backward", "left", "right"

spatial_scale — sets radius [m] (use instead of a numeric radius)
  "tiny"→0.2  "small"→0.4  "medium"→0.7  "large"→1.2  "huge"→2.0

speed_quality — sets linear_speed / max_speed [m/s]
  "very slow"→0.1  "slow"→0.2  "medium"→0.35  "fast"→0.55
  "very fast"→0.8  "explosive"→1.1

beats — duration as musical beats, auto-converted using sequence tempo_bpm
  {"beats": 4}  or  {"beats": "4 beats"}  →  duration = 4 × (60 / tempo_bpm) s

pause_quality — sets pause_duration [s]
  "none"→0  "accent"→0.1  "breath"→0.2  "short"→0.4
  "medium"→0.8  "long"→1.5  "hold"→2.5

accel_profile — sets ramp_up_duration + ramp_down_duration [s]
  "ease-in"      ramp_up=0.6, ramp_down=0.1
  "ease-out"     ramp_up=0.1, ramp_down=0.6
  "ease-in-out"  ramp_up=0.4, ramp_down=0.4
  "constant"     ramp_up=0.05, ramp_down=0.05
  "sharp"        ramp_up=0.02, ramp_down=0.02
  "gentle"       ramp_up=0.8,  ramp_down=0.8

spin_direction — sets clockwise [bool]
  "clockwise"/"CW"→true   "counterclockwise"/"CCW"→false

intensity_quality — sets intensity [0–1]
  "delicate"→0.1  "light"→0.3  "medium"→0.5  "strong"→0.7
  "powerful"→0.9  "explosive"→1.0

Example motif using vocabulary:
  {"move": "Glide", "params": {"direction": "upstage", "speed_quality": "slow",
   "accel_profile": "ease-in", "beats": 4}, "energy": 0.3, "texture": "honey"}\
"""
