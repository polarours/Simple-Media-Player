QT += core gui widgets multimedia multimediawidgets

CONFIG += c++17

TARGET = Simple-Media-Player
TEMPLATE = app

# Define the library paths
LIBS += -lffmpeg -lsdl2

# Include path
INCLUDEPATH += include

# Header files
HEADERS += \
    include/Simple-Media-Player/core/MediaPlayer.h \
    include/Simple-Media-Player/modules/player/PlayerController.h \
    include/Simple-Media-Player/modules/ui/MainWindow.h \
    include/Simple-Media-Player/modules/utils/Utils.h

# Source files
SOURCES += \
    src/main.cpp \
    src/core/MediaPlayer.cpp \
    src/modules/player/PlayerController.cpp \
    src/modules/ui/MainWindow.cpp \
    src/modules/utils/Utils.cpp

# UI files (if any)
FORMS +=

# Resource files
RESOURCES +=

# Distribution files
DISTFILES +=