cmake_minimum_required(VERSION 3.16)

project(AuroraPlayer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动调用 MOC、RCC 和 UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置 Qt6 路径（如果需要）
# set(CMAKE_PREFIX_PATH "/path/to/your/Qt6")

# 查找 Qt6 组件
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets)

# 查找 FFmpeg 库
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWSCALE REQUIRED libswscale)
pkg_check_modules(SDL2 REQUIRED sdl2)

# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${AVCODEC_INCLUDE_DIRS})
include_directories(${AVFORMAT_INCLUDE_DIRS})
include_directories(${AVUTIL_INCLUDE_DIRS})
include_directories(${SWSCALE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

# 添加源文件
file(GLOB_RECURSE INCLUDE_HEADERS "include/*.h")
file(GLOB_RECURSE CORE_HEADERS "src/core/*.h")
file(GLOB_RECURSE PLAYER_HEADERS "src/player/*.h")
file(GLOB_RECURSE UI_HEADERS "src/ui/*.h")
file(GLOB_RECURSE UTILS_HEADERS "src/utils/*.h")
file(GLOB_RECURSE CORE_SOURCES "src/core/*.cpp")
file(GLOB_RECURSE PLAYER_SOURCES "src/player/*.cpp")
file(GLOB_RECURSE UI_SOURCES "src/ui/*.cpp")
file(GLOB_RECURSE UTILS_SOURCES "src/utils/*.cpp")
file(GLOB_RECURSE MAIN_SOURCES "src/main.cpp")

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
    ${CORE_SOURCES}
    ${PLAYER_SOURCES}
    ${UI_SOURCES}
    ${UTILS_SOURCES}
    ${CORE_HEADERS}
    ${PLAYER_HEADERS}
    ${UI_HEADERS}
    ${UTILS_HEADERS}
    ${INCLUDE_HEADERS}
)

# 链接库
target_link_libraries(${PROJECT_NAME} 
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    ${AVCODEC_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
    ${SDL2_LIBRARIES}
)

# 设置目标属性
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)