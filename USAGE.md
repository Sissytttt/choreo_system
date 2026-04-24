# Choreo System — 使用指南

> 本文档覆盖系统的所有使用方式。根据你的目标选择对应章节。

---

## 目录

1. [环境准备（首次必读）](#0-环境准备首次必读)
2. [纯 Python 测试（不需要 ROS / 机器人）](#1-纯-python-测试不需要-ros--机器人)
3. [Web Studio — 仅 2D 轨迹预览（无需 ROS）](#2-web-studio--仅-2d-轨迹预览无需-ros)
4. [Gazebo 3D 仿真 + Web Studio 完整流程（Docker + noVNC）](#3-gazebo-3d-仿真--web-studio-完整流程docker--novnc)
5. [真机运行](#4-真机运行)
6. [Python API — 手写编排](#5-python-api--手写编排)
7. [AI 编舞器 — 自然语言生成编舞](#6-ai-编舞器--自然语言生成编舞)
8. [编舞结构概念速查](#7-编舞结构概念速查)
9. [舞蹈术语参数表（dance vocabulary）](#8-舞蹈术语参数表dance-vocabulary)
10. [Modifier 修饰符参考](#9-modifier-修饰符参考)

---

## 0. 环境准备（首次必读）

### 0.1 Python 依赖（Mac 本地）

```bash
cd /Users/sissytian/Desktop/choreo_system
pip install fastapi uvicorn google-genai
```

### 0.2 Google API Key

获取 Gemini API Key：https://aistudio.google.com/app/apikey

> **安全提示**：不要把 API key 粘贴进聊天、代码文件或 git commit。
> 如果 key 意外泄露，立即在上面的页面 Delete 并重新生成。

### 0.3 Docker Desktop（3D 仿真用）

打开 Docker Desktop，等待菜单栏鲸鱼图标**静止**后再继续。

```bash
open /Applications/Docker.app
```

---

## 1. 纯 Python 测试（不需要 ROS / 机器人）

所有命令在项目根目录运行：

```bash
cd /Users/sissytian/Desktop/choreo_system
```

### 1.1 测试参数映射层（dance vocabulary）

```bash
python3 -c "
import sys; sys.path.insert(0, 'dance_manager')
from dance_manager.dance_vocabulary import translate_params

print(translate_params({'direction': \"3 o'clock\"}))
# {'direction': 'right', 'side': 'right'}

print(translate_params({'beats': 4}, tempo_bpm=120))
# {'duration': 2.0}

print(translate_params({'spatial_scale': 'large'}))
# {'radius': 1.2, 'track': 1.2}

print(translate_params({'speed_quality': 'slow'}))
# {'linear_speed': 0.2, 'max_speed': 0.2, 'speed': 0.2}

print(translate_params({'accel_profile': 'ease-in'}))
# {'ramp_up_duration': 0.6, 'ramp_down_duration': 0.1}
"
```

### 1.2 测试三个新 primitive（pacing / sudden_stop / chaine_turns）

```bash
python3 -c "
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
python3 -c "
import sys; sys.path.insert(0, 'dance_studio')
from simulator import expand_motifs, DISPLACEMENTS

print('新动作:', [k for k in ('Pacing','SuddenStop','ChaineTurns') if k in DISPLACEMENTS])

motifs = [{'move': 'Glide',
           'params': {'direction': 'forward', 'side': 'left', 'angle': 30.0},
           'energy': 0.6, 'texture': 'smooth',
           'modifier': {'type': 'mirror', 'gap': 0.5}}]
r = expand_motifs(motifs, 120)
print(f'mirror 展开 {len(r)} 条（期望 2）')
print(f'  原始: {r[0][1]}')
print(f'  镜像: {r[1][1]}')

motifs2 = [{'move': 'Spin', 'params': {}, 'energy': 0.4, 'texture': 'staccato',
            'modifier': {'type': 'repeat_variation', 'n': 3, 'energy_delta': 0.1}}]
r2 = expand_motifs(motifs2, 120)
print(f'repeat_variation 能量: {[round(e,2) for _,_,_,e,_ in r2]}')
# 期望: [0.4, 0.5, 0.6]
"
```

### 1.4 测试 sections 格式的 simulate（新编舞结构）

```bash
python3 -c "
import sys; sys.path.insert(0, 'dance_studio')
from simulator import simulate

seq = {
  'tempo_bpm': 120,
  'form': 'ABA',
  'energy_arc': 'arch',
  'sections': [
    {
      'name': 'introduction', 'role': 'introduction',
      'effort': {'weight': 'light', 'time': 'sustained', 'flow': 'free'},
      'gap_after': 0.5,
      'phrases': [
        {'name': 'opening', 'arc': 'build', 'gap_after': 0.3,
         'motifs': [
           {'move': 'Glance', 'energy': 0.2, 'texture': 'cloud', 'gap_before': 0.5, 'params': {}},
           {'move': 'Pulse',  'energy': 0.35, 'texture': 'honey', 'gap_before': 0.3, 'params': {}}
         ]}
      ]
    },
    {
      'name': 'climax', 'role': 'climax',
      'effort': {'weight': 'strong', 'time': 'sudden', 'flow': 'free'},
      'gap_after': 1.0,
      'phrases': [
        {'name': 'peak', 'arc': 'punctuate', 'gap_after': 0.5,
         'motifs': [
           {'move': 'Spin', 'energy': 0.95, 'texture': 'staccato',
            'gap_before': 1.0, 'params': {'angle': 360}}
         ]}
      ]
    },
    {
      'name': 'resolution', 'role': 'resolution',
      'effort': {'weight': 'light', 'time': 'sustained', 'flow': 'bound'},
      'gap_after': 0.0,
      'phrases': [
        {'name': 'bow', 'arc': 'release', 'gap_after': 0.0,
         'motifs': [
           {'move': 'Bow', 'energy': 0.25, 'texture': 'honey', 'gap_before': 0.5, 'params': {}}
         ]}
      ]
    }
  ]
}
result = simulate(seq)
print(f'帧数: {len(result[\"frames\"])}  总时长: {result[\"total_duration\"]:.1f}s')
print(f'动作边界: {[b[\"move_name\"] for b in result[\"move_boundaries\"]]}')
"
```

---

## 2. Web Studio — 仅 2D 轨迹预览（无需 ROS）

适合**不需要机器人**的情况：只想拖拽编排、预览 2D 轨迹或用 AI 生成编舞文字结果。

> **注意**：Play 按钮需要 ROS 连接才能使用。没有 ROS 时只有 Simulate（2D 预览）可用。
> 如需 Play 控制 3D 仿真，请看 [Section 3](#3-gazebo-3d-仿真--web-studio-完整流程docker--novnc)。

### 2.1 启动

```bash
# 杀掉占用 8000 端口的旧进程
lsof -ti:8000 | xargs kill -9 2>/dev/null

export GOOGLE_API_KEY="你的key"
cd /Users/sissytian/Desktop/choreo_system/dance_studio
python3 app.py
```

浏览器打开：`http://localhost:8000`

### 2.2 使用 Simulate（无需机器人）

1. 在左侧动作列表拖动任意动作到时间轴
2. 点击 **Simulate** 按钮
3. 右侧出现机器人 2D 轨迹预览动画

### 2.3 使用 AI Generate

1. 在顶部 Generate 栏输入自然语言描述，例如：
   ```
   a slow patrol upstage then sudden explosive stop
   ```
2. 点击 **Generate**，AI 自动生成序列并填入时间轴
3. 点击 **Simulate** 预览 2D 轨迹

---

## 3. Gazebo 3D 仿真 + Web Studio 完整流程（Docker + noVNC）

macOS 上 ROS2 跑在 Docker 容器里，通过 noVNC 在浏览器访问 Ubuntu 桌面。
Web Studio 也必须在容器内启动，才能让 Play 按钮连通 ROS。

**两个入口**：

| 地址 | 内容 |
|------|------|
| http://localhost:6080 | noVNC — Gazebo 3D 仿真画面 |
| http://localhost:8000 | Dance Studio 编舞器（从 Mac 浏览器访问） |

---

### Step 1 — 确认 Docker Desktop 已运行

```bash
open /Applications/Docker.app
```

等待菜单栏鲸鱼图标静止。验证：

```bash
docker info > /dev/null 2>&1 && echo "Docker ready" || echo "Docker not running"
```

---

### Step 2 — 启动容器（Mac 终端）

```bash
docker run --rm -p 6080:80 -p 8000:8000 \
  -v ~/dancerobot_ws/src:/ros2_ws_host/src \
  -v /Users/sissytian/Desktop/choreo_system:/choreo_system \
  --shm-size=512m \
  tiryoh/ros2-desktop-vnc:humble
```

> `-p 8000:8000`：将容器的 8000 端口暴露给 Mac，使 Mac 浏览器可访问 Dance Studio。
> `-v /Users/sissytian/Desktop/choreo_system:/choreo_system`：把项目挂载进容器。
> `--rm`：容器退出后自动清理。每次重新启动都是全新环境，需要重新安装依赖和 build。

浏览器打开 **http://localhost:6080**，点击 **Connect**，进入 Ubuntu 桌面。

---

### Step 3 — noVNC 终端 1：安装依赖、编译、启动 Gazebo

在 noVNC 桌面右键 → 打开终端，运行：

```bash
# 安装 ROS Gazebo 包（每次新容器都需要执行）
sudo apt-get update && sudo apt-get install -y \
  ros-humble-ros-gz \
  ros-humble-ros-gz-sim \
  ros-humble-twist-mux \
  ros-humble-xacro

# 复制源码并编译
mkdir -p ~/ros2_ws/src
cp -r /ros2_ws_host/src/mobilehri2023 ~/ros2_ws/src/

cd ~/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --packages-select dance_interfaces dance_manager chair_dance_sim
source install/setup.bash

# 启动 Gazebo 仿真（包含 dance server，不要单独再启动 dance_server_launch.py）
ros2 launch chair_dance_sim simulation_launch.py
```

等待 Gazebo 窗口在 noVNC 中出现 → 仿真 ready。

> **常见错误**：`package 'ros_gz_sim' not found`
> 原因：`ros-humble-ros-gz` meta-package 有时不会自动拉 `ros_gz_sim`。
> 修复：确保 `ros-humble-ros-gz-sim` 也被显式安装（已包含在上面的命令中）。

---

### Step 4 — noVNC 终端 2：启动 Dance Studio

在 noVNC 桌面再开一个终端（右键 → 打开终端），运行：

```bash
# 设置 UTF-8 编码（防止 AI 生成中文内容时报 ascii codec 错误）
export PYTHONIOENCODING=utf-8
export LANG=C.UTF-8
export LC_ALL=C.UTF-8

# source ROS（必须在 app.py 之前，否则 Play 按钮无法连通 ROS）
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash

# 设置 API key
export GOOGLE_API_KEY="你的key"

# 安装 Python 依赖（每次新容器都需要执行）
pip3 install fastapi uvicorn google-genai

# 启动 Dance Studio
cd /choreo_system/dance_studio
python3 app.py
```

> **关键**：`export GOOGLE_API_KEY` 和 `python3 app.py` 必须在**同一个终端 session** 里执行。
> 新开终端需要重新 export。

---

### Step 5 — 使用

在 **Mac 浏览器**同时打开两个标签：

- **http://localhost:6080** — 查看 Gazebo 3D 仿真中机器人的实际运动
- **http://localhost:8000** — Dance Studio 编舞操作界面

**操作流程**：

1. 在 http://localhost:8000 的 Generate 栏输入自然语言，例如：
   ```
   happy dance with a spin finish
   ```
2. 点击 **Generate** → AI 生成编舞序列，填入时间轴
3. 点击 **Simulate** → 查看 2D top-down 轨迹预览
4. 点击 **Play** → Gazebo 里的机器人同步执行（Play 按钮亮起表示 ROS 已连通）

---

### Step 6 — 关闭

在 Mac 终端按 `Ctrl+C` 停止容器，容器自动清理（`--rm`）。

---

### 注意事项

| 场景 | 说明 |
|------|------|
| 每次重启容器 | 需要重新 `apt-get install` + `colcon build`，约 3–5 分钟 |
| Play 按钮灰色 | app.py 没有 source ROS 就启动；重新按 Step 4 操作 |
| Generate 报 ascii 错误 | 缺少 `PYTHONIOENCODING=utf-8`；重新按 Step 4 操作 |
| API key 无效 | export 了 key 但新开了终端；在同一终端重新 export |

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

真机环境下 ROS 已在本地安装，app.py 在 Mac 上运行即可：

```bash
export GOOGLE_API_KEY="你的key"
cd /Users/sissytian/Desktop/choreo_system/dance_studio
python3 app.py
```

打开 `http://localhost:8000`，ROS 连接成功后 Play 按钮点亮。

---

## 5. Python API — 手写编排

不依赖 LLM，直接用代码构建 Sequence。在 Mac 本地运行（需要 stub ROS，无需 Docker）。

### 5.1 基础结构（Section + Phrase + Motif）

```python
import sys, types
sys.path.insert(0, 'dance_manager')

# Stub ROS（Mac 本地无 ROS 时需要）
geo = types.ModuleType('geometry_msgs')
geo_msg = types.ModuleType('geometry_msgs.msg')
class Twist:
    class _V: x=y=z=0.0
    linear=_V(); angular=_V()
geo_msg.Twist = Twist; geo.msg = geo_msg
sys.modules['geometry_msgs'] = geo
sys.modules['geometry_msgs.msg'] = geo_msg

from dance_manager.choreographer import Motif, Phrase, Section, Sequence
from dance_manager.movement_modifiers import (
    seq_crescendo, seq_mirror, seq_repeat_variation, seq_tension
)

sequence = Sequence(
    title="Happy Dance",
    tempo_bpm=128.0,
    form="ABA",
    energy_arc="arch",
    mood="joyful",
    description="Playful robot waking up, building to a joyful spin climax, settling to a bow",
    sections=[
        Section(
            name="Introduction",
            role="introduction",
            intention="cautious curiosity — robot waking up, testing the space",
            effort={"weight": "light", "time": "sustained", "flow": "free"},
            spatial_path="circular",
            gap_after=0.5,
            phrases=[
                Phrase(
                    name="waking-up",
                    arc="build",
                    intent="first small movements, getting a feel for the space",
                    spatial="circle",
                    motifs=[
                        Motif("Glance", energy=0.2, texture="cloud", gap_before=0.5),
                        Motif("Pulse", energy=0.3, texture="honey", gap_before=0.3),
                        Motif("WagWalk", energy=0.35, params={"direction": "forward"},
                              texture="cloud"),
                    ],
                ),
            ],
        ),
        Section(
            name="Development",
            role="development",
            intention="growing confidence — movement gets bigger and more committed",
            effort={"weight": "strong", "time": "sudden", "flow": "free"},
            spatial_path="advance",
            gap_after=0.8,
            phrases=[
                Phrase(
                    name="building",
                    arc="build",
                    intent="A-A-A-B pattern: Tap repeats 3x then breaks into Zigzag",
                    spatial="advance",
                    gap_after=0.3,
                    motifs=[
                        Motif("Tap", params={"side": "right"}, energy=0.5,
                              texture="staccato", modifier=seq_crescendo(n=3)),
                        Motif("Zigzag", energy=0.65, texture="ice"),
                    ],
                ),
                Phrase(
                    name="contrast",
                    arc="question",
                    intent="soft contrast before the climax — builds anticipation",
                    spatial="stay",
                    gap_after=0.5,
                    motifs=[
                        Motif("Shimmy", energy=0.4, texture="honey", gap_before=0.3),
                        Motif("Pirouette", params={"side": "left"}, energy=0.5,
                              texture="cloud", modifier=seq_mirror(gap=0.4)),
                    ],
                ),
            ],
        ),
        Section(
            name="Climax",
            role="climax",
            intention="peak moment of joy — full commitment, maximum energy",
            effort={"weight": "strong", "time": "sudden", "flow": "free"},
            spatial_path="circular",
            gap_after=1.5,
            phrases=[
                Phrase(
                    name="peak",
                    arc="punctuate",
                    intent="the one peak — tension then explosion",
                    spatial="circle",
                    motifs=[
                        # tension builds anticipation before the spin
                        Motif("Spin", params={"angle": 360}, energy=0.95,
                              texture="staccato", gap_before=1.0),
                        Motif("ChaineTurns", params={"turns": 2.0}, energy=0.9,
                              texture="ice"),
                        Motif("SuddenStop", params={"max_speed": 0.6}, energy=1.0,
                              texture="staccato"),
                    ],
                ),
            ],
        ),
        Section(
            name="Resolution",
            role="resolution",
            intention="winding down — echo of the opening, settling to stillness",
            effort={"weight": "light", "time": "sustained", "flow": "bound"},
            spatial_path="return",
            gap_after=0.0,
            phrases=[
                Phrase(
                    name="settling",
                    arc="release",
                    intent="contrast to climax — soft, slow, closing",
                    spatial="retreat",
                    gap_after=0.5,
                    motifs=[
                        Motif("Pacing", params={"distance": 0.3, "repetitions": 2},
                              energy=0.25, texture="honey", gap_before=0.5),
                        Motif("Glance", energy=0.2, texture="cloud", gap_before=0.3),
                        Motif("Bow", energy=0.3, texture="honey"),
                    ],
                ),
            ],
        ),
    ],
)

# Preview the structure
ai_mock = type('A', (), {'describe': lambda self, s: str(s)})()
from dance_manager.choreographer import AIChoreographer
print(f"Form: {sequence.form}  Arc: {sequence.energy_arc}")
for section in sequence.sections:
    print(f"\n[{section.role.upper()}] {section.name}")
    print(f"  Intent: {section.intention}")
    for phrase in section.phrases:
        moves = [m.move for m in phrase.motifs if hasattr(m, 'move')]
        print(f"  Phrase '{phrase.name}' [{phrase.arc}]: {moves}")
```

运行：

```bash
cd /Users/sissytian/Desktop/choreo_system
python3 your_script.py
```

### 5.2 组合式编舞表达（嵌套 Phrase 组）

嵌套 `Phrase` 作为子组，对一组动作整体应用 modifier：

```python
from dance_manager.choreographer import Motif, Phrase, Section, Sequence
from dance_manager.movement_modifiers import seq_mirror, seq_repeat_variation

# 等价于：seq_repeat_variation(seq_mirror(A + B + C))
mirror_group = Phrase(
    modifier={"type": "mirror", "gap": 0.4},
    intent="mirror the A-B-C group as a unit",
    motifs=[
        Motif("Step",   energy=0.5, texture="ice"),
        Motif("Spin",   energy=0.6, texture="staccato", params={"angle": 90}),
        Motif("Shimmy", energy=0.4, texture="honey"),
    ],
)

phrase = Phrase(
    name="mirrored-buildup",
    arc="build",
    intent="the mirrored group repeats 3 times with growing energy",
    modifier={"type": "repeat_variation", "n": 3, "energy_delta": 0.15},
    motifs=[mirror_group],
)
```

---

## 6. AI 编舞器 — 自然语言生成编舞

### 6.1 不连接机器人（仅生成 + 打印，Mac 本地）

```bash
cd /Users/sissytian/Desktop/choreo_system
export GOOGLE_API_KEY="你的key"

python3 -c "
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
print(ai.describe(seq))
print('Form:', seq.form, '  Arc:', seq.energy_arc)
for section in seq.sections:
    print(f'  [{section.role}] {section.name}: {section.intention}')
"
```

### 6.2 AI 输出格式（sections 结构）

AI 现在返回包含 sections 的 JSON。示例输出（`"a happy dance"`）：

```json
{
  "title": "Joyful Burst",
  "tempo_bpm": 132,
  "form": "ABA",
  "energy_arc": "arch",
  "mood": "joyful",
  "description": "Playful awakening builds to explosive spinning joy then settles to a warm bow",
  "sections": [
    {
      "name": "Awakening",
      "role": "introduction",
      "intention": "small curious movements, establishing playful personality",
      "effort": {"weight": "light", "time": "sustained", "flow": "free"},
      "spatial_path": "circular",
      "gap_after": 0.5,
      "phrases": [
        {
          "name": "first-steps",
          "arc": "build",
          "intent": "testing the space with growing confidence",
          "spatial": "circle",
          "gap_after": 0.3,
          "modifier": null,
          "motifs": [
            {"move": "Glance", "energy": 0.2, "texture": "cloud", "gap_before": 0.5, "params": {}},
            {"move": "Pulse",  "energy": 0.35, "texture": "honey", "gap_before": 0.3, "params": {},
             "modifier": {"type": "repeat_variation", "n": 2, "energy_delta": 0.1}}
          ]
        }
      ]
    },
    {
      "name": "Climax",
      "role": "climax",
      "intention": "peak moment — full commitment and spinning joy",
      "effort": {"weight": "strong", "time": "sudden", "flow": "free"},
      "spatial_path": "circular",
      "gap_after": 1.0,
      "phrases": [
        {
          "name": "explosion",
          "arc": "punctuate",
          "intent": "the one peak — tension then release",
          "spatial": "circle",
          "gap_after": 0.5,
          "modifier": null,
          "motifs": [
            {"move": "Spin", "energy": 0.95, "texture": "staccato", "gap_before": 1.0,
             "params": {"angle": 360}},
            {"move": "ChaineTurns", "energy": 0.85, "texture": "ice", "gap_before": 0.0,
             "params": {"turns": 2.0}}
          ]
        }
      ]
    },
    {
      "name": "Resolution",
      "role": "resolution",
      "intention": "echo of opening — returning to warmth and stillness",
      "effort": {"weight": "light", "time": "sustained", "flow": "bound"},
      "spatial_path": "return",
      "gap_after": 0.0,
      "phrases": [
        {
          "name": "settling",
          "arc": "release",
          "intent": "soft contrast to climax — the robot comes home",
          "spatial": "stay",
          "gap_after": 0.0,
          "modifier": null,
          "motifs": [
            {"move": "Shimmy", "energy": 0.3, "texture": "honey", "gap_before": 0.5, "params": {}},
            {"move": "Bow",    "energy": 0.25, "texture": "honey", "gap_before": 0.3, "params": {}}
          ]
        }
      ]
    }
  ]
}
```

### 6.3 通过 Web Studio 生成（推荐）

按照 [Section 3](#3-gazebo-3d-仿真--web-studio-完整流程docker--novnc) 启动完整流程后，直接在 http://localhost:8000 的 Generate 栏输入描述即可。

### 6.4 命令行直接控制仿真（noVNC 终端内）

```bash
# 在 noVNC 终端（已 source ROS）内运行
export GOOGLE_API_KEY="你的key"

# 生成并执行
ros2 run dance_manager choreographer \
  'A curious, exploratory dance: start slow, grow more energetic, end with a bow'

# 干运行（只打印不执行）
ros2 run dance_manager choreographer \
  --dry-run 'An excited celebratory dance'

# 换用其他 Gemini 模型
ros2 run dance_manager choreographer \
  --model gemini-2.5-pro 'dramatic performance'
```

---

## 7. 编舞结构概念速查

### 7.1 Form（整体结构形式）

| Form | 说明 | 适用场景 |
|---|---|---|
| `ABA` | 引入(A) → 发展/对比(B) → 回归(A') | 最常见，给观众满足感（"回到了原点"） |
| `rondo` | A→B→A→C→A | 主题反复出现，中间插入对比段落 |
| `theme-variations` | 建立签名动作，然后系统地变形它 | 强调一个核心动作的进化 |
| `through-composed` | 持续发展，不重复 | 叙事性旅程，有明确的开头中间结尾 |
| `free` | 只靠戏剧弧线组织 | 实验性/即兴风格 |

### 7.2 Energy Arc（张力曲线）

| Arc | 形状 | 说明 |
|---|---|---|
| `arch` | 低→升→单峰→降 | 最自然，最令人满足 |
| `wave` | 多峰多谷 | 活泼、震荡感 |
| `rising` | 持续上升 | 庆祝、胜利感 |
| `falling` | 从高峰开始降 | 悲伤、结束感 |
| `flat` | 均匀能量 | 冥想、循环感（少用） |

### 7.3 Section Roles（段落角色）

| Role | 能量建议 | 典型特征 |
|---|---|---|
| `introduction` | 中低 | 建立个性，适度能量，设定情绪 |
| `development` | 中→高 | 积累张力，探索和变换开场材料 |
| `climax` | 最高 | 唯一的峰值，全力投入，最高能量 |
| `resolution` | 低 | 回归平静，呼应开场，制造闭合感 |
| `bridge` | 对比 | 与前后段落形成鲜明对比（ABA 中间） |
| `coda` | 最低 | 极简的最后陈述，留下最终印象 |

### 7.4 Effort 质量（Laban Movement Analysis）

| weight | time | flow | → texture | energy |
|---|---|---|---|---|
| strong | sudden | free | staccato | 0.8–1.0 |
| strong | sudden | bound | staccato | 0.7–0.9 |
| strong | sustained | free | honey / ice | 0.6–0.8 |
| light | sudden | bound | staccato | 0.3–0.6 |
| light | sustained | free | cloud | 0.1–0.4 |
| light | sustained | bound | honey | 0.2–0.5 |

### 7.5 Phrase Arc（乐句形状）

| Arc | 说明 | 典型结尾动作 |
|---|---|---|
| `build` | 张力逐渐增加 | 能量稍大的动作 |
| `sustain` | 维持峰值状态 | 重复式动作（crescendo） |
| `release` | 让步，解消张力 | Bow, Pacing, slow Glide |
| `punctuate` | 短暂强烈的重音 | SuddenStop, high-energy Spin |
| `question` | 悬而未决，向外延伸 | Glance, Pacing（不闭合） |
| `answer` | 解答前一个 question | Bow, 完整 Arc（闭合） |

### 7.6 七条编舞原则（快速参考）

1. **对比** — 相邻段落必须在能量/质感/方向至少一个维度上形成对比
2. **重复+变奏** — A-A-A-B：重复 3 次后第 4 次打破，制造惊喜
3. **静止的力量** — 高潮前 gap_before 0.8–1.5s；高潮后 gap_after 1.0s+
4. **乐句形状** — 每个 phrase 有 arc，不只是动作的列表
5. **唯一高潮** — 整支舞只有一个峰值，其余都为它服务
6. **空间旅程** — spatial_path 是编舞选择：圆形=探索，前进=自信，后退=内省
7. **结尾** — 结尾和开头同等重要；ABA 形式的满足感来自"回到了原点"

## 8. 舞蹈术语参数表（dance vocabulary）

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

## 9. Modifier 修饰符参考

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
