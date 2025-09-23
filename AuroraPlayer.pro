QT += core gui widgets multimedia multimediawidgets

CONFIG += c++17

TARGET = AuroraPlayer
TEMPLATE = app

# Define the library paths
LIBS += -lffmpeg -lsdl2

# Include path
INCLUDEPATH += include

# Header files
HEADERS += \
    include/CommonState.h \
    include/CommonUtils.h \
    src/core/MediaPlayer.h \
    src/player/PlayerController.h \
    src/player/PlaylistManager.h \
    src/ui/MainWindow.h \
    src/utils/Utils.h

# Source files
SOURCES += \
    src/main.cpp \
    src/core/MediaPlayer.cpp \
    src/player/PlayerController.cpp \
    src/player/PlaylistManager.cpp \
    src/ui/MainWindow.cpp \
    src/utils/Utils.cpp

# UI files (if any)
FORMS += \
    src/ui/MainWindow.ui

# Resource files
RESOURCES +=

# Distribution files
DISTFILES +=