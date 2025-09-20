QT += core gui widgets multimedia multimediawidgets

CONFIG += c++17

TARGET = Simple-Media-Player
TEMPLATE = app

# Define the library paths
LIBS += -lffmpeg -lsdl2

# Include path
INCLUDEPATH += include

# Source files
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/PlayerController.cpp \
    src/MediaPlayer.cpp \
    src/FFmpegHelper.cpp

# Header files
HEADERS += \
    include/MainWindow.h \
    include/PlayerController.h \
    include/MediaPlayer.h \
    include/FFmpegHelper.h

# UI files (if any)
FORMS +=

# Resource files
RESOURCES +=

# Distribution files
DISTFILES +=