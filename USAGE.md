# Choreo System — 使用指南

> 本文档覆盖系统的所有使用方式。根据你的目标选择对应章节。

---

## 目录

1. [环境准备（首次必读）](#0-环境准备首次必读)
2. [纯 Python 测试（不需要 ROS / 机器人）](#1-纯-python-测试不需要-ros--机器人)
3. [Web Studio — 可视化编排工具](#2-web-studio--可视化编排工具)
4. [Gazebo 3D 仿真（Docker）](#3-gazebo-3d-仿真docker)
5. [真机运行](#4-真机运行)
6. [Python API — 手写编排](#5-python-api--手写编排)
7. [AI 编舞器 — 自然语言生成编舞](#6-ai-编舞器--自然语言生成编舞)
8. [舞蹈术语参数表（dance vocabulary）](#7-舞蹈术语参数表dance-vocabulary)
9. [Modifier 修饰符参考](#8-modifier-修饰符参考)

---

## 0. 环境准备（首次必读）

### 0.1 Python 依赖

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system
pip install fastapi uvicorn google-genai
```

### 0.2 Docker Desktop（仿真 / 真机用）

打开 Docker Desktop，等待菜单栏鲸鱼图标**静止**后再继续。

```bash
open /Applications/Docker.app
```

---

## 1. 纯 Python 测试（不需要 ROS / 机器人）

所有命令在项目根目录运行：

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system
```

### 1.1 测试参数映射层（dance vocabulary）

```bash
python -c "
import sys; sys.path.insert(0, 'dance_manager')
from dance_manager.dance_vocabulary import translate_params

# 方向词 → 技术参数
print(translate_params({'direction': \"3 o'clock\"}))
# 输出: {'direction': 'right', 'side': 'right'}

# 节拍 → 时长（120 BPM）
print(translate_params({'beats': 4}, tempo_bpm=120))
# 输出: {'duration': 2.0}

# 空间尺度 → radius + track
print(translate_params({'spatial_scale': 'large'}))
# 输出: {'radius': 1.2, 'track': 1.2}

# 速度质感 → 速度值
print(translate_params({'speed_quality': 'slow'}))
# 输出: {'linear_speed': 0.2, 'max_speed': 0.2, 'speed': 0.2}

# 加速度 profile
print(translate_params({'accel_profile': 'ease-in'}))
# 输出: {'ramp_up_duration': 0.6, 'ramp_down_duration': 0.1}
"
```

### 1.2 测试三个新 primitive（pacing / sudden_stop / chaine_turns）

```bash
python -c "
import sys, types; sys.path.insert(0, 'dance_manager')

# Stub ROS（不需要安装 ROS）
geo = types.ModuleType('geometry_msgs')
geo_msg = types.ModuleType('geometry_msgs.msg')
class Twist:
    class _V: x=y=z=0.0
    linear=_V(); angular=_V()
geo_msg.Twist=Twist; geo.msg=geo_msg
sys.modules['geometry_msgs']=geo; sys.modules['geometry_msgs.msg']=geo_msg

from unittest.mock import MagicMock
from dance_manager.dance_moves import pacing, sudden_stop, chaine_turns

pub = MagicMock()

pacing(pub, distance=0.3, step_duration=0.2, repetitions=2, pause_duration=0.05)
print(f'pacing: publish called {pub.publish.call_count} times')
pub.reset_mock()

sudden_stop(pub, max_speed=0.4, run_duration=0.1, brake_times=3)
print(f'sudden_stop: publish called {pub.publish.call_count} times')
pub.reset_mock()

chaine_turns(pub, turns=1.0, half_turn_duration=0.2, track=0.3)
print(f'chaine_turns: publish called {pub.publish.call_count} times')
"
```

### 1.3 测试 simulator expand（modifier 展开逻辑）

```bash
python -c "
import sys; sys.path.insert(0, 'dance_studio')
from simulator import expand_motifs, DISPLACEMENTS

# 验证新动作已注册
print('新动作:', [k for k in ('Pacing','SuddenStop','ChaineTurns') if k in DISPLACEMENTS])

# mirror → 翻转所有空间参数
motifs = [{'move': 'Glide',
           'params': {'direction': 'forward', 'side': 'left', 'angle': 30.0},
           'energy': 0.6, 'texture': 'smooth',
           'modifier': {'type': 'mirror', 'gap': 0.5}}]
r = expand_motifs(motifs, 120)
print(f'mirror 展开 {len(r)} 条（期望 2）')
print(f'  原始: {r[0][1]}')
print(f'  镜像: {r[1][1]}')
# 期望: direction→backward, side→right, angle→-30

# repeat_variation → 能量递增
motifs2 = [{'move': 'Spin', 'params': {}, 'energy': 0.4, 'texture': 'staccato',
            'modifier': {'type': 'repeat_variation', 'n': 3, 'energy_delta': 0.1}}]
r2 = expand_motifs(motifs2, 120)
print(f'repeat_variation 能量: {[round(e,2) for _,_,_,e,_ in r2]}')
# 期望: [0.4, 0.5, 0.6]
"
```

---

## 2. Web Studio — 可视化编排工具

Web Studio 是一个浏览器界面，提供：
- 拖拽式编排动作序列
- 轨迹预览动画（Simulate，**不需要机器人**）
- AI 自然语言生成编舞（需要 API key）
- 连接 ROS 后可直接在浏览器点 Play 执行

### 2.1 启动

```bash
# 如果 8000 端口被占用，先释放
lsof -ti:8000 | xargs kill -9 2>/dev/null

cd /Users/zijiesmac/Documents/GitHub/choreo_system/dance_studio
python app.py
```

浏览器打开：`http://localhost:8000`

### 2.2 使用 Simulate（无需机器人）

1. 在左侧动作列表拖动任意动作到时间轴
2. 点击 **Simulate** 按钮
3. 右侧出现机器人轨迹预览动画

### 2.3 使用 AI Generate（需要 API key）

1. 在顶部 Generate 栏输入自然语言描述，例如：
   ```
   a slow patrol upstage then sudden explosive stop
   ```
2. 确保已设置环境变量：
   ```bash
   export GOOGLE_API_KEY="你的key"
   ```
3. 点击 **Generate**，AI 自动生成序列并填入时间轴
4. 点击 **Simulate** 预览

### 2.4 Play（需要 ROS 连接）

连接机器人或启动 Gazebo 仿真后，点击 **Play** 在真机/仿真中执行。

---

## 3. Gazebo 3D 仿真（Docker）

macOS 上 ROS2 跑在 Docker 容器里，通过浏览器访问 RViz 3D 界面。

### 3.1 首次：构建 Docker 镜像（约 10-15 分钟）

```bash
cd ~/dancerobot_ws
./sim.sh build
```

### 3.2 每次启动步骤

**终端 1 — 启动容器并进入**

```bash
cd ~/dancerobot_ws
./sim.sh up
./sim.sh shell
```

进入容器后：

```bash
export DISPLAY=:99
export LIBGL_ALWAYS_SOFTWARE=1
source /dancerobot_ws/install/setup.bash
ros2 launch chair_dance_sim simulation_launch.py headless:=true use_rviz:=true
```

**浏览器** 打开 `http://localhost:6080`，点击 **Connect**，RViz 出现后：
- Global Options → Fixed Frame 改为 `odom`

### 3.3 发送单个动作（终端 2）

```bash
cd ~/dancerobot_ws

# 原地旋转 360°
./sim.sh exec "ros2 action send_goal /dance dance_interfaces/action/Dance \
  \"{dance_move: 'Spin', params: '{\\\"angle\\\": 360}'}\""

# 向前滑行
./sim.sh exec "ros2 action send_goal /dance dance_interfaces/action/Dance \
  \"{dance_move: 'Glide', params: '{\\\"direction\\\": \\\"forward\\\"}'}\""

# 来回巡逻（新动作）
./sim.sh exec "ros2 action send_goal /dance dance_interfaces/action/Dance \
  \"{dance_move: 'Pacing', params: '{\\\"distance\\\": 0.4, \\\"repetitions\\\": 2}'}\""

# 急停（新动作）
./sim.sh exec "ros2 action send_goal /dance dance_interfaces/action/Dance \
  \"{dance_move: 'SuddenStop', params: '{\\\"max_speed\\\": 0.5}'}\""

# Chaîné turns（新动作）
./sim.sh exec "ros2 action send_goal /dance dance_interfaces/action/Dance \
  \"{dance_move: 'ChaineTurns', params: '{\\\"turns\\\": 2.0}'}\""
```

### 3.4 AI 编舞器（仿真内）

```bash
export GOOGLE_API_KEY="你的key"

# 生成并执行
./sim.sh exec "GOOGLE_API_KEY=$GOOGLE_API_KEY ros2 run dance_manager choreographer \
  'A curious, exploratory dance: start slow, grow more energetic, end with a bow'"

# 干运行（只打印不执行）
./sim.sh exec "GOOGLE_API_KEY=$GOOGLE_API_KEY ros2 run dance_manager choreographer \
  --dry-run 'An excited celebratory dance'"
```

### 3.5 关闭

```bash
cd ~/dancerobot_ws
./sim.sh down
```

### 3.6 Web Studio 连接 Gazebo

Gazebo 仿真启动后，在另一个终端启动 Web Studio：

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system/dance_studio
python app.py
```

打开 `http://localhost:8000`，此时 **Play 按钮**会激活，可在 Web UI 里直接控制仿真中的机器人。

---

## 4. 真机运行

### 4.1 前置条件

- 机器人已通电并连接同一 WiFi 或 USB
- 已 source ROS 环境：
  ```bash
  source /opt/ros/humble/setup.bash
  source ~/dancerobot_ws/install/setup.bash
  ```

### 4.2 启动 dance server

在机器人端（SSH 或本地）：

```bash
ros2 launch dance_manager dance_server_launch.py
```

### 4.3 发送指令

```bash
# 单个动作
ros2 action send_goal /dance dance_interfaces/action/Dance \
  "{dance_move: 'Spin', params: '{\"angle\": 360}'}"

# AI 编舞器
export GOOGLE_API_KEY="你的key"
ros2 run dance_manager choreographer "A slow patrol then explosive finish"
```

### 4.4 使用 Web Studio 控制真机

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system/dance_studio
python app.py
```

打开 `http://localhost:8000`，ROS 连接成功后 Play 按钮点亮。

---

## 5. Python API — 手写编排

不依赖 LLM，直接用代码构建 Sequence。

```python
import sys
sys.path.insert(0, 'dance_manager')

from dance_manager.choreographer import Motif, Phrase, Sequence, run_sequence
from dance_manager.movement_modifiers import (
    seq_repeat, seq_crescendo, seq_mirror, seq_decay,
    seq_repeat_variation, seq_env_modulation
)

sequence = Sequence(
    title="Demo Sequence",
    tempo_bpm=120.0,
    mood="playful",
    phrases=[
        Phrase(name="intro", intent="greet", motifs=[
            Motif("Glance", energy=0.4, texture="neutral"),
            Motif("WagWalk", energy=0.5, params={"direction": "forward"}),
        ]),
        Phrase(name="build", intent="build energy", gap_after=0.5, motifs=[
            # 重复 4 次，能量递增
            Motif("Tap", params={"side": "right"}, modifier=seq_crescendo(n=4)),
            # 镜像：左右各一次
            Motif("Pirouette", params={"side": "left"}, modifier=seq_mirror(gap=0.3)),
        ]),
        Phrase(name="climax", intent="peak moment", motifs=[
            Motif("Spin", params={"angle": 360}, energy=0.9, texture="staccato"),
            # 急停后 Chaîné
            Motif("SuddenStop", params={"max_speed": 0.6}, energy=1.0),
            Motif("ChaineTurns", params={"turns": 2.0}, energy=0.8, texture="ice"),
        ]),
        Phrase(name="outro", motifs=[
            # 模拟"地板有阻力"的环境调制
            Motif("Pacing", params={"distance": 0.4, "repetitions": 2},
                  modifier=seq_env_modulation(bias=0.1, resistance=0.15)),
            Motif("Bow", energy=0.3, texture="honey"),
        ]),
    ],
)

# run_sequence(action_client, sequence)  # 需要 ROS action client
# 或直接打印查看结构
import json
print(json.dumps({
    "title": sequence.title,
    "tempo_bpm": sequence.tempo_bpm,
    "phrases": [
        {"name": p.name, "motifs": [m.move for m in p.motifs]}
        for p in sequence.phrases
    ]
}, indent=2, ensure_ascii=False))
```

运行：

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system
python your_script.py
```

---

## 6. AI 编舞器 — 自然语言生成编舞

### 6.1 不连接机器人（仅生成 + 打印）

```bash
cd /Users/zijiesmac/Documents/GitHub/choreo_system
export GOOGLE_API_KEY="你的key"

python -c "
import sys, os; sys.path.insert(0, 'dance_manager')
from dance_manager.choreographer import AIChoreographer

class FakePlatform:
    def get_available_moves(self):
        return ['Glide','Step','Spin','Zigzag','Shimmy','Tap','Pirouette',
                'Bow','Glance','Pacing','SuddenStop','ChaineTurns']
    def get_move_displacements(self): return {}
    def get_move_categories(self): return {}
    def get_platform_description(self): return 'differential drive robot'

ai = AIChoreographer(api_key=os.environ['GOOGLE_API_KEY'], platform=FakePlatform())
seq = ai.generate('a slow curious patrol, then an explosive spin finish')
print(seq)
"
```

### 6.2 连接 Gazebo / 真机时

```bash
./sim.sh exec "GOOGLE_API_KEY=$GOOGLE_API_KEY \
  ros2 run dance_manager choreographer 'a slow patrol upstage then explosive stop'"

# 干运行（只看计划，不动）
./sim.sh exec "GOOGLE_API_KEY=$GOOGLE_API_KEY \
  ros2 run dance_manager choreographer --dry-run 'playful zigzag then chaîné turns'"
```

### 6.3 换用其他 Gemini 模型

```bash
./sim.sh exec "GOOGLE_API_KEY=$GOOGLE_API_KEY \
  ros2 run dance_manager choreographer --model gemini-2.5-pro 'dramatic performance'"
```

---

## 7. 舞蹈术语参数表（dance vocabulary）

在任意 `params` 字典里可用舞蹈术语代替数字，系统自动翻译。

| 参数键 | 可用值 | 翻译结果 |
|---|---|---|
| `direction` | `"upstage"` / `"12 o'clock"` | `direction="forward"` |
| | `"downstage"` / `"6 o'clock"` | `direction="backward"` |
| | `"stage right"` / `"3 o'clock"` | `direction="right", side="right"` |
| | `"stage left"` / `"9 o'clock"` | `direction="left", side="left"` |
| | `"1 o'clock"` ~ `"11 o'clock"` | `direction + angle`（斜向） |
| `spatial_scale` | `"tiny"` / `"small"` / `"medium"` / `"large"` / `"huge"` | radius = 0.2 / 0.4 / 0.7 / 1.2 / 2.0 m |
| `speed_quality` | `"very slow"` / `"slow"` / `"medium"` / `"fast"` / `"very fast"` / `"explosive"` | linear_speed = 0.1 / 0.2 / 0.35 / 0.55 / 0.8 / 1.1 m/s |
| `beats` | `4` 或 `"4 beats"` | `duration = 4 × (60 / tempo_bpm)` s |
| `pause_quality` | `"none"` / `"accent"` / `"breath"` / `"short"` / `"medium"` / `"long"` / `"hold"` | 0 / 0.1 / 0.2 / 0.4 / 0.8 / 1.5 / 2.5 s |
| `accel_profile` | `"ease-in"` / `"ease-out"` / `"ease-in-out"` / `"constant"` / `"sharp"` / `"gentle"` | ramp_up + ramp_down |
| `spin_direction` | `"clockwise"` / `"CW"` / `"counterclockwise"` / `"CCW"` | `clockwise=True/False` |
| `intensity_quality` | `"delicate"` / `"light"` / `"medium"` / `"strong"` / `"powerful"` / `"explosive"` | intensity = 0.1 / 0.3 / 0.5 / 0.7 / 0.9 / 1.0 |

示例：

```python
Motif("Glide", params={
    "direction": "upstage",
    "speed_quality": "slow",
    "accel_profile": "ease-in",
    "beats": 4,
})
# 等价于：
Motif("Glide", params={
    "direction": "forward",
    "linear_speed": 0.2,
    "max_speed": 0.2,
    "ramp_up_duration": 0.6,
    "ramp_down_duration": 0.1,
    "duration": 2.0,  # 假设 tempo_bpm=120
})
```

---

## 8. Modifier 修饰符参考

在 `Motif(modifier=...)` 中传入，从 `dance_manager.movement_modifiers` 导入。

| 修饰符 | 效果 | 常用参数 |
|---|---|---|
| `seq_repeat(n, gap)` | 重复 n 次 | `n=3, gap=0.2` |
| `seq_repeat_variation(n, energy_delta, scale_delta)` | 重复 n 次，每次能量/尺度渐变 | `n=3, energy_delta=0.1` |
| `seq_mirror(gap)` | 执行两次：原始 + 镜像（翻转所有方向参数） | `gap=0.3` |
| `seq_direction_flip(gap)` | 执行两次：原始 + 方向翻转 | `gap=0.3` |
| `seq_invert(factor)` | 能量取反（强→弱），可缩放半径 | `factor=0.8` |
| `seq_reverse()` | 时序倒放（单 Motif 为 no-op） | — |
| `seq_scale(factor)` | 缩放空间幅度（radius/distance） | `factor=0.5` 缩小 |
| `seq_speed_modulate(factor)` | 乘以 factor 调整能量 | `factor=1.5` 加速 |
| `seq_crescendo(n, factor)` | 重复 n 次，间隔递减（越来越急） | `n=4` |
| `seq_decay(n, factor)` | 重复 n 次，间隔递增（越来越慢） | `n=4` |
| `seq_tension(hold_duration)` | 动作前静止等待（制造悬念） | `hold_duration=1.0` |
| `seq_rhythm_shift(gap_scale)` | 缩放 gap_before 节奏感 | `<1` 紧张，`>1` 悬停 |
| `seq_alternate(other_move, n)` | 与另一个动作交替 A-B-A-B | `other_move="Tap", n=4` |
| `seq_asymmetric_pause(short, long, n)` | 交替短/长停顿，制造律动感 | `short=0.2, long=0.8` |
| `seq_drift(angle_delta)` | 给 angle 参数加偏移（慢漂移） | `angle_delta=15.0` |
| `seq_env_modulation(bias, resistance)` | 模拟环境力：bias=角度偏力，resistance=速度阻尼 | `bias=0.1, resistance=0.2` |

示例：

```python
from dance_manager.movement_modifiers import (
    seq_mirror, seq_crescendo, seq_env_modulation, seq_repeat_variation
)

# 镜像：左右各一次
Motif("Pirouette", params={"side": "left"}, modifier=seq_mirror(gap=0.4))

# Crescendo：4 次越来越急
Motif("Tap", params={"side": "right"}, modifier=seq_crescendo(n=4))

# 带环境阻力的巡逻（模拟地板摩擦）
Motif("Pacing", params={"distance": 0.4}, modifier=seq_env_modulation(resistance=0.2))

# 三次重复，能量递增
Motif("Spin", params={"angle": 90}, modifier=seq_repeat_variation(n=3, energy_delta=0.15))
```
