# AuroraPlayer

一个基于 Qt6 和 FFmpeg 的简易音视频播放器，用于学习和理解多媒体播放的基本原理和实现方式。

## 项目简介

AuroraPlayer 是一个使用 C++ 编写的本地媒体播放器项目，旨在演示如何使用 Qt6 和 FFmpeg 构建一个功能完整的媒体播放器。该项目适合多媒体开发初学者、C++ 开发者以及对 Qt 和 FFmpeg 集成感兴趣的技术人员学习和参考。

## 功能特性

- 支持多种音视频格式的本地文件播放
- 基本播放控制功能：
  - 播放/暂停
  - 停止播放
  - 进度条拖拽定位
  - 音量控制
- 播放列表管理功能
- 使用 Qt6 构建图形用户界面
- 使用 FFmpeg 进行音视频解码
- 使用 Qt Multimedia 进行音频输出

## 技术架构

### 核心组件

1. **MainWindow** - 主窗口类，负责管理用户界面元素和交互逻辑
2. **PlayerController** - 播放控制器，协调播放逻辑
3. **MediaPlayer** - 媒体播放核心类，集成 FFmpeg 进行音视频解码
4. **PlaylistManager** - 播放列表管理类，负责管理播放列表
5. **Utils** - 工具类，提供初始化和错误处理功能

### 技术栈

- C++20
- Qt6 (Core, Widgets, Gui, Multimedia, MultimediaWidgets)
- FFmpeg (libavformat, libavcodec, libavutil, libswscale)
- CMake 构建系统

## 构建说明

### 环境要求

- C++20 兼容的编译器 (GCC 11+ 或 Clang)
- Qt6 开发环境
- FFmpeg 开发库
- SDL2 开发库
- CMake 3.16+

### Ubuntu/Debian 系统依赖安装

```bash
sudo apt-get install qt6-base-dev qt6-tools-dev libqt6multimedia6 libqt6multimediawidgets6 \
                     libavformat-dev libavcodec-dev libavutil-dev libswscale-dev libsdl2-dev \
                     cmake g++ pkg-config
```

### 构建步骤

```bash
cd AuroraPlayer
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### 运行程序

```bash
./AuroraPlayer
```

## 使用说明

1. 点击 "打开文件" 按钮选择要播放的媒体文件
2. 使用播放/暂停按钮控制播放状态
3. 使用停止按钮停止播放
4. 拖动进度条跳转到指定位置
5. 调整音量滑块控制播放音量
6. 使用播放列表功能管理多个媒体文件

## 项目结构

```
AuroraPlayer/
├── CMakeLists.txt                     # CMake 构建配置文件
├── AuroraPlayer.pro                   # Qt Creator 项目文件
├── src/                               # 源文件目录
│   ├── main.cpp                       # 程序入口文件
│   ├── core/                          # 核心模块
│   │   ├── MediaPlayer.h              # 媒体播放器类头文件
│   │   └── MediaPlayer.cpp            # 媒体播放器类实现
│   ├── player/                        # 播放器模块
│   │   ├── PlayerController.h         # 播放控制器类头文件
│   │   ├── PlayerController.cpp       # 播放控制器类实现
│   │   ├── PlaylistManager.h          # 播放列表管理类头文件
│   │   └── PlaylistManager.cpp        # 播放列表管理类实现
│   ├── ui/                            # 用户界面模块
│   │   ├── MainWindow.h               # 主窗口类头文件
│   │   ├── MainWindow.cpp             # 主窗口类实现
│   │   └── MainWindow.ui              # UI界面文件
│   └── utils/                         # 工具模块
│       ├── Utils.h                    # 工具类头文件
│       └── Utils.cpp                  # 工具类实现
├── include/                           # 公共头文件目录
│   ├── CommonState.h                  # 公共状态定义
│   └── CommonUtils.h                  # 公共工具定义
└── README.md                          # 项目说明文档
```

## 许可证

本项目采用 MIT 许可证，详情请见 [LICENSE](LICENSE) 文件。