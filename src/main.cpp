/********************************************************************************
 * @file   : main.cpp
 * @brief  : 程序入口文件。
 *
 * 该文件是程序的入口文件，负责初始化程序环境，创建主窗口，并启动程序。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include <QApplication>

#include "ui/MainWindow.h"
#include "utils/Utils.h"

/**
 * @brief 程序入口。
 *
 * 该函数是程序的入口函数，负责初始化程序环境，创建主窗口，并启动程序。
 */
int main(int argc, char *argv[])
{
    // 创建QApplication对象
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("AuroraPlayer");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("AuroraPlayer");

    // 初始化FFmpeg
    AuroraPlayer::Utils::initializeFFmpeg();

    // 创建主窗口
    MainWindow window;
    window.show();

    return app.exec();
}