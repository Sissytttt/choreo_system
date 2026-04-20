# Choreo System — Implementation Checklist

> 对照 `大纲.md` 逐层检查现有代码实现情况。
> 状态标记：✅ 已实现 | ⚠️ 部分实现/需要修改 | ❌ 未实现 | 🆕 本次新增

---

## 最近改动（2026-04-20）

| 文件 | 改动 |
|---|---|
| `dance_manager/dance_vocabulary.py` | 🆕 新建：全套映射表 + `translate_params()` + `get_vocabulary_description()` |
| `dance_manager/dance_moves.py` | 🆕 新增 `pacing()`, `sudden_stop()`, `chaine_turns()` 三个 primitive |
| `dance_manager/platforms/differential_drive.py` | 🆕 注册 3 个新 primitive；`execute_move()` 内自动调用 `translate_params()` |
| `dance_manager/choreographer.py` | 🆕 LLM prompt 注入 vocabulary 描述；`run_sequence()` 内用 `tempo_bpm` 翻译参数 |

---

## Layer 1 — Motion Primitives (`dance_moves.py`)

### 基础运动（Basic Locomotion）

| 大纲名称 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Simple Roll（直线运动） | `glide()` | ⚠️ | `glide` 是匀速，但大纲要求支持"constant or accelerated speed"；缺少加速模式。名字也不对应 |
| Inching Forward with Pause（停走爬行） | `inch_forward()` + 手动 pause | ⚠️ | 现有 `inch_forward` 只做一次冲刺，没有"move→pause→move"的循环停走逻辑，需要封装成完整行为 |
| Inching Forward（重复爬行） | `inch_forward()` / `pulse()` | ⚠️ | 大纲描述是"rapid short back-and-forth pushes creeping forward"，`pulse()` 接近但方向是原地前后，不是整体前进；需单独实现 |
| Stepping / Zigzag（之字前进） | `zigzag()` | ✅ | 已实现，参数对应（direction, turns, v_mag, track） |
| Free-form Skating（溜冰滑行） | `slalom()` | ⚠️ | `slalom()` 是规则正弦曲线，大纲要求"wide wave-like curves resembling ice-skating"，更自由；参数也不完全对应 |
| Pacing / Patrolling（来回巡逻） | `pacing()` | 🆕 | 新增：`distance`, `step_duration`, `repetitions`, `pause_duration`，内部用 `glide()` 实现 |
| In-place Oscillation（原地摇摆） | `vibrate()` / `shimmy()` | ⚠️ | `vibrate()` 是小幅前后震动，`shimmy()` 是角速度正弦。大纲说"small oscillations forward and backward in place"，两者都不完全匹配；需确认/合并 |
| Sudden Stop（急停） | `sudden_stop()` | 🆕 | 新增：`direction`, `max_speed`, `run_duration`, `brake_times`；sprint → `_brake()` → `_stop()` |

### 方向与旋转（Directional / Rotational Moves）

| 大纲名称 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Pivoting（以一个轮为轴旋转） | `tap_on_side()` / `pirouette()` | ⚠️ | 两者都有单轮支点旋转的逻辑，但语义混乱：`tap_on_side` 是短暂tap，`pirouette` 是持续旋转。大纲"Pivoting"是通用的以后轮为轴转动，需要梳理/重命名 |
| Spinning in Place（原地自旋） | `spin_on_axis()` | ✅ | 已实现，参数对应（rotations, spin_duration, clockwise） |
| Circular Motion / Arc Turn（圆弧运动） | `drive_arc()` / `teacup_spin()` / `spiral()` | ⚠️ | `drive_arc()` 做定角弧，`spiral()` 做螺旋。大纲描述"varying wheel speeds, can form spirals"——功能分散在多个函数，需整理命名 |
| Spinning on One Foot（单点旋摆） | `pirouette()` | ✅ | 已实现，side 参数控制支撑轮 |
| Sweeping L→R with Pause（左右扫视） | `glance()` / `peek_left_right()` | ⚠️ | 两者语义重复（`peek_left_right` 是 `glance` 的别名），但与大纲描述基本一致；需清理别名 |
| Slalom（蛇形前进） | `slalom()` | ✅ | 已实现，参数基本对应 |
| Alternating Pivot Spin（交替半转 / Chaîné turns） | `chaine_turns()` | 🆕 | 新增：`turns`, `half_turn_duration`, `track`；交替 left-fixed / right-fixed，全程 CCW |

### 命名与参数一致性问题

- `greeting()` / `peek_left_right()` 是别名但名字暴露给了外部，与大纲语义不符，需清理
- `inch_forward` / `inch_forward_exponential` / `inch_backward` 三个函数重复逻辑，可合并为带 `profile` 参数的统一函数
- 参数表里出现的 `abs_brake` / `abs_brake_angular` 并非独立函数，而是 `_brake()` 的内部用法，外部不可调用

---

## Layer 2 — Dancer → Robot Mapping（参数映射层）

### 技术参数 vs. 舞蹈术语映射表

大纲定义了一套从舞蹈维度（Spatial / Temporal / Kinematic / Effort / Structure）到系统参数的映射。现有代码**没有形式化这个映射**，全部隐含在函数参数里。

| 维度 | 子类别 | 状态 | 说明 |
|---|---|---|---|
| Spatial / Direction | direction, side 参数 | ✅ | 已实现 |
| Spatial / Path Type | trajectory via radius, direction | ⚠️ | 隐含在各函数里，无统一接口；"path type"无法作为高层参数传入 |
| Spatial / Scale | `spatial_scale` → radius | 🆕 | `dance_vocabulary.py`：`"small"→0.4m`, `"large"→1.2m` 等 |
| Spatial / Rotation Orientation | `spin_direction` → clockwise | 🆕 | `"clockwise"/"CW"→True`, `"CCW"→False` |
| Temporal / Duration | `beats` → duration | 🆕 | `{"beats": 4}` 在 tempo_bpm=120 时 → `duration=2.0s` |
| Temporal / Tempo | speed (indirect), cmd_dt | ⚠️ | tempo_bpm 现在参与 beats 换算；cmd_dt 仍是技术参数 |
| Temporal / Pause | `pause_quality` → pause_duration | 🆕 | `"breath"→0.2s`, `"short"→0.4s`, `"long"→1.5s` 等 |
| Temporal / Rhythm Pattern | frequency | ⚠️ | 只在 slalom/shimmy 里有，没有统一的"rhythm pattern"控制接口 |
| Kinematic / Speed | `speed_quality` → linear_speed/max_speed | 🆕 | `"slow"→0.2 m/s`, `"fast"→0.55 m/s` 等 |
| Kinematic / Acceleration Profile | `accel_profile` → ramp_up/down | 🆕 | `"ease-in"`, `"sharp"`, `"gentle"` 等 6 种 profile |
| Kinematic / Motion Quality | oscillation_amp, frequency | ⚠️ | 只在特定函数里，不是通用参数 |
| Effort / Intensity | `intensity_quality` → intensity | 🆕 | `"light"→0.3`, `"strong"→0.7`, `"explosive"→1.0` |
| Effort / Energy Flow | acceleration + duration | ✅ | 已实现（ramp profiles） |
| Effort / Control | braking / ramp profiles | ✅ | 已实现 |
| Spatial / Direction | `direction` → clock/stage term | 🆕 | `"3 o'clock"`/`"stage right"` → `direction="right", side="right"` |
| Structure / Repetition | repetitions, tap_times | ✅ | 已实现 |
| Structure / Count System | `beats` → duration | 🆕 | 通过 `translate_params()` 用 tempo_bpm 换算 |
| Structure / Cycles | turns, orbit_turns, spin_turns | ✅ | 已实现 |

**本次实现：** 新建 `dance_vocabulary.py`，形式化了全套舞蹈术语→参数映射表（方向/速度/空间/节奏/加速度/强度），通过 `translate_params()` 在 `execute_move()` 和 `run_sequence()` 两处自动翻译，并注入 LLM prompt（`get_vocabulary_description()`）。

---

## Layer 3 — Modifiers (`movement_modifiers.py`)

### 重复与模式（Repetition & Pattern）

| 大纲修饰符 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Repetition（重复） | `seq_repeat()` | ✅ | 已实现 |
| Repeat with Variation（带变化的重复 A→A'→A''） | `seq_repeat_variation()` | 🆕 | energy_delta + scale_delta 控制每次变化量 |
| Pattern Sequence（A→A→B→A 结构） | `seq_alternate()` 部分 | ⚠️ | `seq_alternate` 只做 A/B 交替，不能表达任意 pattern 如 AABA |

### 变换（Transformation）

| 大纲修饰符 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Mirror（镜像） | `seq_mirror()` | 🆕 | **已修复**：现在同时翻转 side / direction / clockwise / angle |
| Reverse（时序倒放 ABC→CBA） | `seq_reverse()` | 🆕 | 单 Motif 为 no-op；phrase 级别反转待未来实现 |
| Invert（扩展/收缩反转） | `seq_invert(factor)` | 🆕 | energy→(1-energy)，可选 radius×factor |
| Direction Flip（方向对调） | `seq_direction_flip()` | 🆕 | 翻转 direction/side/clockwise/angle，和 mirror 逻辑相同但语义独立 |

### 参数与动态调制（Parametric & Dynamic Modulation）

| 大纲修饰符 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Scale（缩放空间幅度） | `seq_scale(factor)` | 🆕 | 缩放 radius/distance/linear_speed/max_speed |
| Speed up / Slow down | `seq_speed_modulate(factor)` | 🆕 | 直接乘以 energy |
| Rhythm shift（节奏变化） | `seq_rhythm_shift(gap_scale)` | 🆕 | gap_scale < 1 = 紧凑，> 1 = 悬停 |
| Intensity / Energy modulate | `seq_crescendo()` / `seq_decay()` | ✅ | 已实现 |
| Smoothness / Sharpness | Texture 系统（honey/staccato） | ⚠️ | 通过 texture 实现，不是独立 modifier，但够用 |
| Weight（轻/重） | `weight_to_accel()` | ⚠️ | 存在 helper，可通过 MoveContext.weight 传入 |

### 有机变化（Organic Variation）

| 大纲修饰符 | 代码对应 | 状态 | 说明 |
|---|---|---|---|
| Noise（随机抖动） | `with_noise()` / `add_noise()` | ✅ | 已实现 |
| Timing Offset / Delay | `seq_asymmetric_pause()` + `seq_rhythm_shift()` | ✅ | 已实现 |
| Asymmetry（非对称） | `seq_asymmetric_pause()` | ⚠️ | 时间维度；空间非对称可通过 seq_mirror 的 gap 实现 |
| Decay（幅度衰减） | `seq_decay()` | ✅ | 已实现 |
| Drift（慢速漂移） | `seq_drift(angle_delta)` | 🆕 | 给 angle 参数加偏移量；env_bias 实现连续漂移效果 |

---

## Layer 4 — Choreographic Structure (`choreographer.py`)

### 4.1 Sequence（序列编排）

| 功能 | 状态 | 说明 |
|---|---|---|
| 线性序列 A→B→C | ✅ | `Sequence` / `Phrase` / `Motif` 数据结构完整 |
| 重复序列 A→A'→A'' | ⚠️ | `seq_repeat` 已有，但 A' 的"slight variation"无自动生成机制 |
| 模式序列 A→A→B→A | ⚠️ | 需手动构建，无声明式 pattern 语法 |
| 嵌套结构 A→(BC)→D | ✅ | Phrase 内嵌 Motif，Sequence 包含 Phrase，支持层级 |

### 4.2 Phrase（短句结构）

| 功能 | 状态 | 说明 |
|---|---|---|
| Phrase 作为高层结构 | ✅ | `Phrase` 类已实现，含 name / intent / gap_after |
| 对整个 sequence 应用修饰 | ⚠️ | modifier 在 Motif 层，Phrase 整体变换未实现 |
| 层级组合 | ✅ | Sequence → Phrase → Motif 三层 |
| Motif Memory（签名动作） | ✅ | `MotifMemory` 实现了回溯和变体召回 |

### 4.3 主题调制（Thematic Modulation）

| 功能 | 状态 | 说明 |
|---|---|---|
| **Motion-level modulation**（内部参数调制） | ✅ | Texture 系统 + energy + ramp profiles 已实现 |
| **Environment-level modulation**（外部力场调制） | 🆕 | **已实现**：`_EnvPublisher` 代理 + `seq_env_modulation(bias, resistance)`；env_bias [rad/s] = 方向偏力，env_resistance [0-1] = 速度阻尼；spatial constraints 仍只有 StageTracker 边界检测 |

### 4.4 LLM 集成（AIChoreographer）

| 功能 | 状态 | 说明 |
|---|---|---|
| 自然语言 → Sequence 生成 | ✅ | `AIChoreographer.generate()` 使用 Gemini 已实现 |
| Prompt 包含 platform 能力描述 | ✅ | 已实现（available moves, displacements, categories, description） |
| Prompt 包含舞台尺寸约束 | ✅ | 已实现 |
| Prompt 包含 Dancer Design Thinking 原则 | ✅ | 11条原则已写入 system prompt |
| JSON 解析容错 / retry | ✅ | 已实现（max_retries=2） |
| LLM 理解 Modifier 语法 | ⚠️ | Modifier schema 在 prompt 里用 prose 描述，但 LLM 生成 modifier 的可靠性未验证 |
| LLM 使用舞蹈术语描述 → 参数映射 | ⚠️ | Prompt 里有 texture/energy 说明，但"dance terminology → 参数"的映射表（大纲 Layer 2 表格）未注入 LLM prompt |
| 描述已生成的 Sequence（`describe()`） | ✅ | 已实现 |

---

## Layer 5 — Environment / Music（环境与音乐感知）

| 功能 | 状态 | 说明 |
|---|---|---|
| Beat detection（节拍检测） | ❌ | 大纲标注"future implementation" |
| Phrase alignment（动作对齐音乐短句） | ❌ | 同上 |
| Tempo adaptation（实时节拍适应） | ❌ | 同上 |

---

## 整体架构问题

| 问题 | 严重程度 | 说明 |
|---|---|---|
| **Motion Primitive 命名与大纲不对齐** | 🔴 高 | 代码用 `glide` / `step` / `shimmy`，大纲用 "Simple Roll" / "Inching Forward" 等。LLM prompt 和 Web UI 暴露的是代码名，导致大纲语义丢失 |
| **Layer 2 映射表没有形式化** | 🔴 高 | 大纲 Layer 2 的舞蹈维度→参数映射表是设计核心，但现有代码完全隐含，无法被 LLM 或用户以舞蹈语言控制 |
| **两套 modifier 系统并存** | 🟡 中 | `movement_modifiers.py` 里有两套：直接操作 `twist_pub` 的函数（`repeat()` 等）和返回 spec dict 的函数（`seq_repeat()` 等）。前者是遗留代码，后者是新架构；应统一 |
| **dance_moves.py 直接 publish Twist** | 🟡 中 | Layer 1 直接耦合 ROS，不符合 `RobotPlatform` 抽象的精神；平台抽象层（platform.py）虽然存在，但 dance_moves.py 仍直接依赖 twist_pub |
| **pacing() 函数缺失** | 🔴 高 | 参数表大量引用 pacing 函数的参数，但函数体不存在 |
| **Modifier 扩展逻辑散落** | 🟡 中 | `run_sequence()` 里有 modifier expand 逻辑，`simulator.py` 里也有独立的 `expand_motifs()`，两处不同步 |
| **Web UI 的 Move 列表与大纲 Primitive 列表不对应** | 🟡 中 | `dance_studio` 展示的 moves 来自 `DiffDrivePlatform`，名字与大纲不同 |
| **别名函数污染命名空间** | 🟢 低 | `greeting` / `peek_left_right` / `inch_backward` 等别名不应对外暴露 |

---

## 优先级汇总

### ✅ 已完成（本次）
1. ~~新增缺失的 primitive：`pacing()`, `sudden_stop()`, `chaine_turns()`~~ **已完成**
2. ~~形式化 Layer 2 映射表，注入 LLM prompt~~ **已完成**（`dance_vocabulary.py`）
3. ~~`translate_params()` 集成到 `execute_move()` 和 `run_sequence()`~~ **已完成**
4. ~~beats → duration（tempo_bpm 换算）~~ **已完成**

### ✅ 已完成（第二批）
5. ~~实现缺失的 modifiers~~ **已完成**：`seq_reverse`, `seq_invert`, `seq_direction_flip`, `seq_scale`, `seq_speed_modulate`, `seq_rhythm_shift`, `seq_drift`, `seq_repeat_variation`, `seq_env_modulation`
6. ~~完善 `mirror` modifier~~ **已完成**：现在同时翻转 side / direction / clockwise / angle
7. ~~实现 Environment-level modulation~~ **已完成**：`_EnvPublisher` 代理 + `seq_env_modulation()`，env_bias（角度偏力）和 env_resistance（速度衰减）
8. ~~统一两套 modifier 系统~~ **已完成**：删除了 legacy twist_pub wrappers（repeat/mirror/decay/crescendo/with_noise/tension/release/alternate），只保留 seq_* 系列

### ✅ 已完成（第三批）
10. ~~同步 `simulator.py` modifier expand 逻辑~~ **已完成**：新增 repeat_variation / direction_flip / invert / reverse / scale / speed_modulate / rhythm_shift / drift / env_modulation；修复 mirror（现在用 `_flip_params()` 翻转全部空间参数）；新增 Pacing / SuddenStop / ChaineTurns 到 DISPLACEMENTS 和 CATEGORIES
11. ~~`spatial_scale` 也应影响 `track` 参数~~ **已完成**：`translate_params()` 中 `spatial_scale` 同时设 `radius` 和 `track`

### 🟢 优化改进（低优先级，未做）
9. 清理别名函数（greeting, peek_left_right, inch_backward）— 用户说 Layer 1 不需要改动太多
