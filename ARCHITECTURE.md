# Choreo System — Architecture

> 本文档描述当前系统的完整架构、各层职责与数据流。
> 基于论文设计思路（dancer-informed thinking）实现，目前覆盖 Layer 1–4。

---

## 整体设计哲学

系统以**舞者思维（dancer-informed thinking）**为核心：不把机器人运动看作底层指令序列，而是从编舞的角度构建动作——用运动质感、时间结构、空间构图和高阶编排组织动作，使机器人的行为具备可感知的表达性。

核心洞见：
- **表达性来自动态质感，而非姿态形状**（速度曲线、停顿、节奏、曲率）
- **机器人应发展自己的动作语言**（椅式机器人 = 滚动、旋转、滑行、弧线）
- **结构性重复 + 变化**赋予动作叙事性
---

## 五层架构总览

```
┌──────────────────────────────────────────────────────────────────────┐
│  Layer 5 — Environment / Music Awareness             [ 未实现 ]      │
│  节拍检测 / 音乐对齐 / 实时节拍适应                                   │
├──────────────────────────────────────────────────────────────────────┤
│  Layer 4 — Choreographic Structure                   [ ✅ 已实现 ]   │
│  choreographer.py · AIChoreographer · MotifMemory                    │
│  四层结构：Sequence → Section → Phrase → Motif                       │
│  · form（ABA/rondo）+ energy_arc（arch/wave）= 宏观戏剧弧线          │
│  · Section：role + effort（Laban）+ spatial_path                      │
│  · Phrase：arc（build/release）+ 嵌套 Phrase 组合表达                │
│  · LLM 以编舞家视角生成（7条编舞原则 + Laban effort 指导）           │
├──────────────────────────────────────────────────────────────────────┤
│  Layer 3 — Modifiers                                 [ ✅ 已实现 ]   │
│  movement_modifiers.py · seq_* 系列                                  │
│  Motif 级 + Phrase 级 + 嵌套组级 三层 modifier 支持                  │
│  重复/镜像/渐强/漂移/环境调制 + 组合式表达（seq_mirror(A+B+C)）      │
├──────────────────────────────────────────────────────────────────────┤
│  Layer 2 — Dancer → Robot Mapping                    [ ✅ 已实现 ]   │
│  dance_vocabulary.py · translate_params()                             │
│  舞蹈术语 ↔ 技术参数双向映射（方位/速度/节拍/加速度曲线）            │
├──────────────────────────────────────────────────────────────────────┤
│  Layer 1 — Motion Primitives                         [ ✅ 已实现 ]   │
│  dance_moves.py · DiffDrivePlatform move registry                    │
│  22个原子动作（社交/线性/编织/自旋/弧线/复杂路径/打击/急停/连转）   │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 文件结构

```
choreo_system/
├── dance_interfaces/
│   └── action/Dance.action              # ROS action 接口定义
│
├── dance_manager/
│   └── dance_manager/
│       ├── platform.py                  # Platform 抽象基类（ABC）
│       ├── platforms/
│       │   └── differential_drive.py   # DiffDrivePlatform 实现
│       ├── dance_moves.py               # Layer 1：原子动作函数库
│       ├── dance_vocabulary.py          # Layer 2：舞蹈术语参数映射
│       ├── movement_modifiers.py        # Layer 3：seq_* 修饰符
│       ├── choreographer.py             # Layer 4：编排结构 + AI 生成
│       ├── dance_server.py              # ROS action server（平台无关dispatcher）
│       ├── dance_client.py              # ROS action client
│       ├── stage_tracker.py             # 舞台边界追踪（辅助工具）
│       └── dance_visualizer.py          # 可视化辅助
│
└── dance_studio/
    ├── app.py                           # FastAPI Web Studio 后端
    ├── simulator.py                     # 2D 轨迹模拟器（无需 ROS）
    └── storage.py                       # 编舞保存/加载
```

---

## 完整数据流

```
用户自然语言输入
        │
        ▼
┌──────────────────┐
│  AIChoreographer │  (choreographer.py)
│  Google Gemini   │  → 生成 Sequence JSON（含 sections）
└──────────────────┘
        │
        ▼
┌──────────────────────────────────────┐
│  Sequence（编舞乐谱）                 │  (Layer 4 数据结构)
│  · form, energy_arc, tempo_bpm       │
│  · sections: List[Section]           │
│    ├── role, intention, effort       │
│    └── phrases: List[Phrase]         │
│        ├── arc, spatial, intent      │
│        └── motifs: List[Motif|Phrase]│
│            · move, energy, texture   │
│            · modifier (seq_* spec)   │
└──────────────────────────────────────┘
        │
        │ run_sequence()  /  simulate()
        ▼
┌──────────────────────────────────┐
│  Section → Phrase 扁平化          │
│  （sections 按顺序合并为          │
│   all_phrases 列表）              │
└──────────────────────────────────┘
        │
        ▼
┌──────────────────────────────────┐
│  Modifier Expansion              │  (Layer 3 — _expand_items())
│  嵌套 Phrase 递归展开 →           │
│  Phrase-level modifier 应用 →    │
│  Motif-level modifier 展开 →     │
│  → list of (move, params, gap,   │
│             energy, texture)     │
└──────────────────────────────────┘
        │
        │ translate_params()
        ▼
┌──────────────────────────────────┐
│  dance_vocabulary.py             │  (Layer 2)
│  "3 o'clock" → direction="right" │
│  "slow" → linear_speed=0.2       │
│  beats=4 → duration=2.0s         │
└──────────────────────────────────┘
        │
        │ Dance.action goal
        ▼
┌──────────────────────────────────┐
│  DanceActionServer               │  (dance_server.py)
│  平台无关的 dispatcher            │
│  → platform.execute_move()       │
└──────────────────────────────────┘
        │
        ▼
┌──────────────────────────────────┐
│  DiffDrivePlatform               │  (platforms/differential_drive.py)
│  1. pre_roll()   §1 呼吸预备     │
│  2. _EnvPublisher wrap（环境力）  │
│  3. move_registry[name](params)  │
│  4. active_brake() §3 主动制动   │
└──────────────────────────────────┘
        │
        ▼
┌──────────────────────────────────┐
│  dance_moves.py                  │  (Layer 1)
│  glide / spin_on_axis / zigzag / │
│  pacing / sudden_stop / ...      │
│  → publish geometry_msgs/Twist   │
└──────────────────────────────────┘
        │
        ▼
   Gazebo 3D 物理仿真 / 真机
```

---

## Layer 1 — Motion Primitives（`dance_moves.py`）

原子动作单元，每个函数直接发布 `geometry_msgs/Twist`。

### 当前实现的动作

| 外部名称（LLM/UI） | 内部函数 | 类别 |
|---|---|---|
| `Glance` | `glance()` | 社交姿态 |
| `Bow` | `bow_sequence()` | 社交姿态 |
| `Step` | `step()` | 线性运动 |
| `Glide` | `glide()` | 线性运动 |
| `Shimmy` | `shimmy()` | 原地表达 |
| `Pulse` | `pulse()` | 原地表达 |
| `Vibrate` | `vibrate()` | 原地表达 |
| `Tap` | `tap_on_side()` | 轴点旋转 |
| `Pirouette` | `pirouette()` | 轴点旋转 |
| `Spin` | `spin_on_axis()` | 原地自旋 |
| `Zigzag` | `zigzag()` | 编织路径 |
| `Slalom` | `slalom()` | 编织路径 |
| `WagWalk` | `wag_walking()` | 编织路径 |
| `Arc` | `drive_arc()` | 弧线/圆圈 |
| `TeacupSpin` | `teacup_spin()` | 弧线/圆圈 |
| `TeacupCircle` | `teacup()` | 弧线/圆圈 |
| `Spiral` | `spiral()` | 复杂路径 |
| `FigureEight` | `figure_eight()` | 复杂路径 |
| `Flower` | `flower()` | 复杂路径 |
| `Pacing` | `pacing()` | 往返巡逻（新增） |
| `SuddenStop` | `sudden_stop()` | 急停（新增） |
| `ChaineTurns` | `chaine_turns()` | Chaîné 转（新增） |

**设计特性**：每个函数通过 `ramp_up_duration` / `ramp_down_duration` 实现非线性速度曲线（对应舞者"内在时间细分"原则），而非恒速运动。

---

## Layer 2 — Dancer → Robot Mapping（`dance_vocabulary.py`）

将舞蹈语言（模糊、意象性）翻译为技术参数（精确、数字性）。

核心函数：`translate_params(params, tempo_bpm=120.0)`

### 支持的映射维度

| 参数键 | 输入示例 | 翻译输出 |
|---|---|---|
| `direction` | `"3 o'clock"` / `"stage right"` | `direction="right", side="right"` |
| `direction` | `"upstage"` / `"12 o'clock"` | `direction="forward"` |
| `direction` | `"1 o'clock"` | `direction="forward", angle=30.0` |
| `spatial_scale` | `"large"` | `radius=1.2, track=1.2` |
| `speed_quality` | `"slow"` | `linear_speed=0.2, max_speed=0.2` |
| `beats` | `4` | `duration=2.0` (at 120 BPM) |
| `pause_quality` | `"breath"` | `pause_duration=0.2` |
| `accel_profile` | `"ease-in"` | `ramp_up=0.6, ramp_down=0.1` |
| `spin_direction` | `"clockwise"` / `"CW"` | `clockwise=True` |
| `intensity_quality` | `"explosive"` | `intensity=1.0` |

映射在两处自动触发：
1. `DiffDrivePlatform.execute_move()` — 运行时执行
2. `run_sequence()` — 编排层执行（用于 `gap_before` 等 timing 参数）

---

## Layer 3 — Modifiers（`movement_modifiers.py`）

对动作或结构进行变换操作，均以 `seq_*` 命名，返回 spec dict。在 `_expand()` 中展开执行。

### 分类

**重复与模式**
| 函数 | 效果 |
|---|---|
| `seq_repeat(n, gap)` | 重复 n 次 |
| `seq_repeat_variation(n, energy_delta, scale_delta)` | 重复并渐变能量/尺度 |
| `seq_alternate(other_move, n, gap)` | A-B 交替 |
| `seq_asymmetric_pause(short, long, n)` | 交替短/长停顿 |

**变换**
| 函数 | 效果 |
|---|---|
| `seq_mirror(gap)` | 原始 + 镜像（翻转 side/direction/clockwise/angle） |
| `seq_direction_flip(gap)` | 方向对调（与 mirror 逻辑同，语义独立） |
| `seq_invert(factor)` | 能量取反（强→弱），可缩放 radius |
| `seq_reverse()` | 时序倒放（单 Motif 为 no-op） |

**参数与动态调制**
| 函数 | 效果 |
|---|---|
| `seq_scale(factor)` | 缩放空间幅度（radius/distance/speed） |
| `seq_speed_modulate(factor)` | 乘以 factor 调整 energy |
| `seq_crescendo(n, factor)` | 重复 n 次，间隔递减（越来越急） |
| `seq_decay(n, factor)` | 重复 n 次，间隔递增（越来越慢） |
| `seq_tension(hold_duration)` | 动作前静止等待（制造悬念） |
| `seq_rhythm_shift(gap_scale)` | 缩放 gap_before（节奏感调节） |

**有机变化**
| 函数 | 效果 |
|---|---|
| `seq_drift(angle_delta)` | angle 参数偏移（慢漂移） |
| `seq_env_modulation(bias, resistance)` | 环境力场：bias=角度偏力，resistance=速度阻尼 |

**环境调制机制**：`seq_env_modulation` 通过 `_EnvPublisher` 代理实现，在 publisher 层拦截每条 Twist 消息并叠加外部力，模拟"地板有阻力"/"环境风"效果。

---

## Layer 4 — Choreographic Structure（`choreographer.py`）

### 核心设计哲学转变

Layer 4 采用**舞蹈学（choreographic thinking）**而非程序员思维来组织编舞。LLM 现在以编舞家的视角工作：先确定整体形式和戏剧弧线，再决定每个段落的角色，最后选择动作和工具（modifier）来表达这个角色。

### 数据结构（四层）

```
Sequence（完整编舞乐谱）
├── title: str
├── tempo_bpm: float          # 节拍，用于 beats→duration 换算
├── form: str                 # 整体结构形式：ABA / rondo / theme-variations /
│                             # through-composed / free
├── energy_arc: str           # 全舞张力曲线：arch / wave / rising / falling / flat
├── mood: str
├── description: str          # 一句话编舞意图
├── sections: List[Section]   # 主结构（3–5个 section）
└── phrases: List[Phrase]     # 向后兼容（无 sections 时使用）

Section（宏观结构单元）
├── name: str
├── role: str                 # introduction / development / climax /
│                             # resolution / bridge / coda
├── intention: str            # 这个段落的编舞目的（一句话）
├── effort: dict              # Laban 努力质量：
│   ├── weight: "strong"|"light"  # 动作力量感
│   ├── time: "sudden"|"sustained" # 动作时间感
│   └── flow: "free"|"bound"      # 动作流动感
├── spatial_path: str         # 空间路径意图：circular / advance / retreat /
│                             # diagonal / stay / return
├── gap_after: float
└── phrases: List[Phrase]

Phrase（乐句，一个呼吸的运动）
├── name: str
├── intent: str               # WHY this phrase exists
├── arc: str                  # 乐句形状：build / sustain / release /
│                             # punctuate / question / answer
├── spatial: str              # 空间方向：advance / retreat / circle /
│                             # diagonal / stay
├── gap_after: float
├── modifier: dict            # Phrase 级别的整体 modifier（应用于全部 motifs）
└── motifs: List[Motif | Phrase]  # 支持嵌套 Phrase 作为子组

Motif（原子单元）
├── move: str                 # DiffDrivePlatform 注册的动作名称
├── params: dict              # 可含舞蹈术语，由 translate_params() 翻译
├── energy: float             # [0–1] 表达强度
├── texture: str              # "honey"|"staccato"|"ice"|"cloud"|"magnet"|"neutral"
├── gap_before: float
├── modifier: dict            # Motif 级别 modifier（seq_* 函数产生的 spec）
└── annotation: str
```

### 嵌套 Phrase 组（组合编舞表达）

`Phrase.motifs` 中的元素可以是 `Motif`，也可以是嵌套的 `Phrase`（作为子组）。子组的 `modifier` 在子组内所有元素展开后统一应用，实现组合式编舞结构：

```
seq_repeat_variation(seq_mirror(A + B + C))

↓ 对应 JSON 结构：

Phrase(
  modifier={"type":"repeat_variation","n":3,"energy_delta":0.15},
  motifs=[
    Phrase(
      modifier={"type":"mirror","gap":0.4},
      motifs=[A, B, C]
    )
  ]
)
```

### 七条编舞原则（System Prompt 中对 LLM 的指导）

LLM 在生成编舞时被要求遵循舞蹈学原则：

1. **对比（Contrast）** — 相邻段落/乐句必须在至少一个维度上形成对比
2. **重复+变奏（Repetition+Variation）** — A-A-A-B 模式：重复建立意义，第4次打破产生惊喜
3. **静止（Stillness）** — 高潮前的 gap_before 0.8–1.5s 制造期待，高潮后的停顿制造共鸣
4. **乐句形状（Phrase Arc）** — 每个 phrase 有 build/sustain/release 的戏剧形状
5. **唯一高潮（Single Climax）** — 整支舞只有一个峰值，不能有多个等高的高潮
6. **空间旅程（Spatial Journey）** — 机器人在空间中的路径是编舞选择，不是动作的副产品
7. **结尾（Endings）** — 结尾和开头同样重要；ABA 形式的价值来自"回到原点"

### Effort 质量 → 执行参数映射

| Effort 组合 | energy 范围 | 推荐 texture | gap_before |
|---|---|---|---|
| strong + sudden + free | 0.8–1.0 | staccato | 0.5–1.0s |
| strong + sudden + bound | 0.7–0.9 | staccato | 0–0.3s |
| strong + sustained + free | 0.6–0.8 | honey / ice | 0.3–0.8s |
| light + sudden + bound | 0.3–0.6 | staccato | 0–0.2s |
| light + sustained + free | 0.1–0.4 | cloud | 0.5–1.5s |
| light + sustained + bound | 0.2–0.5 | honey | 0–0.3s |

### Motif Memory（签名动作记忆）

`MotifMemory` 类追踪已使用动作的频率，在序列中周期性召回"签名动作"，构建机器人的"个性"。对应设计文档中的 **"Repeat but Variate"** 原则。

### AIChoreographer

- 使用 Google Gemini API（默认 `gemini-2.5-flash`）
- System prompt 结构：
  - 平台能力描述（available moves + categories）
  - 编舞形式（form / energy_arc / section roles）
  - Laban Effort 质量指南
  - 七条编舞原则
  - Modifier schema
  - 完整 JSON 输出 schema（sections 为顶层结构）
  - 舞台边界约束（displacement table）
- 输出严格 JSON，经 `_parse_json()` 容错解析（去除 markdown fence、trailing comma）
- `_dict_to_sequence()` 支持 sections 格式（新）和 phrases 格式（旧，向后兼容）
- 失败时最多 retry 2 次

---

## Platform 抽象层（`platform.py` + `platforms/`）

### 设计意图

实现关注点分离：编排层（Layer 4）永远不直接接触 Twist 或 diff-drive 逻辑，只通过 `RobotPlatform` ABC 交互。

```
choreographer.py → Dance.action → DanceActionServer → RobotPlatform.execute_move()
                                                              ↓
                                                    DiffDrivePlatform
                                                              ↓
                                                       dance_moves.py → Twist
```

### RobotPlatform ABC（必须实现的接口）

| 方法 | 舞者设计思维映射 |
|---|---|
| `get_available_moves()` | 平台的动作词汇表 |
| `execute_move(name, context)` | 主执行入口 |
| `pre_roll(move_name, context)` | §1 呼吸/预备动作 |
| `active_brake(context)` | §3 主动制动（freeze = 张力，不是零功率） |
| `stop()` | 紧急停止 |
| `apply_texture(texture)` | §1 纹理预设 → 电机参数 |
| `spotting_anchor(heading)` | §3 旋转中的感知重置（placeholder） |
| `lean_into_error(residual)` | §3 误差 → 变化（placeholder） |

### MoveContext（表达意图载体）

```python
@dataclass
class MoveContext:
    energy: float = 0.5        # 强度 [0–1]
    texture: Texture = NEUTRAL # 运动质感
    weight: str = "neutral"    # Laban 重量质感（定义但未完全用于执行）
    noise_level: float = 0.0   # 有机随机性（定义但未完全用于执行）
    enable_pre_roll: bool = True
    enable_active_brake: bool = True
    params: dict = ...         # 动作特定参数
```

### Texture 预设（DiffDrivePlatform 实现）

| Texture | 物理类比 | ramp_up | ramp_down | damping |
|---|---|---|---|---|
| `neutral` | 标准 | 1.0× | 1.0× | 1.0 |
| `honey` | 粘稠液体 | 2.0× | 2.0× | 2.0 |
| `staccato` | 瞬间冲击 | 0.3× | 0.2× | 0.5 |
| `ice` | 无摩擦滑行 | 0.5× | 3.0× | 0.2 |
| `cloud` | 漂浮轻盈 | 1.5× | 1.5× | 0.8 |
| `magnet` | 吸引/排斥 | 0.4× | 0.4× | 1.5 |

### Dance.action 接口

```
# Request
string dance_move      # 动作名称
float32 energy  0.5    # 表达强度
string texture neutral # 运动纹理
string params          # JSON 编码的动作参数

# Result
int32 result_code

# Feedback
int32 progress
```

---

## Web Studio（`dance_studio/`）

独立的 FastAPI 应用，提供可视化编排界面。

| 组件 | 功能 |
|---|---|
| `app.py` | FastAPI 后端，含 `/api/generate`、`/api/simulate`、`/api/execute` |
| `simulator.py` | 纯 Python 2D 轨迹模拟（无需 ROS） |
| `storage.py` | 编舞 JSON 的本地保存/加载 |

**运行模式**：
- **无 ROS**：Simulate 功能正常，Play 按钮禁用
- **有 ROS**（在 Docker 容器内）：Play 按钮激活，通过 `ROSBridge` 发送 Dance.action goal

---

## 代码与设计文档的差异（待改进项）

以下是当前代码与设计文档（`项目介绍.md` / `paperInProgress.md`）**有出入**的地方：

### Layer 1 — Primitive 命名不对应设计文档原名

| 设计文档名称 | 当前代码名称 | 说明 |
|---|---|---|
| Simple Roll（直线运动） | `Glide` / `Step` | 外部名与设计描述语义不完全对应 |
| Inching Forward with Pause（停走爬行） | 无独立 primitive | 需用 Glide + gap 手动模拟；未封装 |
| In-place Oscillation（原地摇摆） | `Vibrate` / `Shimmy` | 两者都是近似，不完全匹配"前后小幅震荡" |
| Pivoting（以一轮为轴的通用旋转） | `Tap` / `Pirouette` | 语义混杂，Tap 是短暂动作，Pirouette 是持续旋转 |
| Circular Motion / Arc Turn | `Arc` / `TeacupSpin` / `Spiral` | 设计为一个概念，代码拆成三个 |

### Layer 2 — 部分映射维度未完全打通

| 维度 | 状态 | 说明 |
|---|---|---|
| Rhythm Pattern（even/syncopated） | ⚠️ | `frequency` 只在特定函数里，无通用"节奏模式"控制接口 |
| Motion Quality（smooth/jerky） | ⚠️ | 通过 texture 近似，不是独立映射维度 |
| Tempo（全局 BPM） | ⚠️ | `tempo_bpm` 只用于 `beats` 换算，不影响全局执行速度 |

### Platform 层 — 部分 dancer 概念为 placeholder

| 功能 | 状态 | 说明 |
|---|---|---|
| `spotting_anchor()` | ⚠️ placeholder | 需要 IMU/odometry 集成才能实现真正的"定点旋转锁定" |
| `lean_into_error()` | ⚠️ placeholder | 目前 forward/backward 都返回 "Glide"，未区分漂移方向 |
| `MoveContext.weight` | ⚠️ 定义未使用 | `weight` 字段在 MoveContext 中定义，但执行链中未消费 |
| `MoveContext.noise_level` | ⚠️ 定义未使用 | 同上 |
| `checkpoint()` | ❌ 未实现 | PLAN.md 中提到的关键帧朝向控制，Platform ABC 中未包含此方法 |

### Layer 5 — 整体未实现（设计为 future work）

节拍检测、音乐短句对齐、实时节拍适应均标记为 future implementation。

---

## 已验证可工作的完整路径

```
自然语言描述
    → AIChoreographer.generate()（Gemini API）
    → Sequence（含 sections / form / energy_arc）
    → _dict_to_sequence()（解析 sections 格式或旧 phrases 格式）
    → simulator.py 的 simulate()
      （sections → phrases 扁平化 → expand_motifs() → 2D 轨迹预览，无需 ROS）
    → 或 run_sequence()
      （sections 扁平化为 all_phrases → _expand_items() → DanceActionServer）
      → DiffDrivePlatform → Gazebo 3D 仿真（Docker + noVNC）
```
