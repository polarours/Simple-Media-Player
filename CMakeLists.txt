cmake_minimum_required(VERSION 4.0)
project(Simple-Media-Player)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 寻找相关库
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWSCALE REQUIRED libswscale)
pkg_check_modules(SDL2 REQUIRED sdl2)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${Qt6_INCLUDE_DIRS})
include_directories(${AVFORMAT_INCLUDE_DIRS})
include_directories(${AVCODEC_INCLUDE_DIRS})
include_directories(${AVUTIL_INCLUDE_DIRS})
include_directories(${SWSCALE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

# 链接目录
link_directories(${AVFORMAT_LIBRARY_DIRS})
link_directories(${AVCODEC_LIBRARY_DIRS})
link_directories(${AVUTIL_LIBRARY_DIRS})
link_directories(${SWSCALE_LIBRARY_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

# 源文件
set(SOURCES
    src/main.cpp
        src/MainWindow.cpp
        src/PlayerController.cpp
        src/MediaPlayer.cpp
        src/FFmpegHelper.cpp
)

# 头文件
set(HEADERS
        include/MainWindow.h
        include/PlayerController.h
        include/MediaPlayer.h
        include/FFmpegHelper.h
)

# 创建可执行文件
qt6_add_executable(Simple-Media-Player
    ${SOURCES}
    ${HEADERS}
)

# 链接库
target_link_libraries(Simple-Media-Player PRIVATE
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui 
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
    ${SDL2_LIBRARIES}
)

# 包含目录
target_include_directories(Simple-Media-Player PRIVATE include)