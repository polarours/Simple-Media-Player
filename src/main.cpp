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

#include "Simple-Media-Player/modules/ui/MainWindow.h"
#include "Simple-Media-Player/modules/utils/Utils.h"

/**
 * @brief 程序入口。
 *
 * @param argc 参数个数
 * @param argv 参数列表
 * @return  int 程序退出码
 *
 * 该函数是程序的入口函数，负责初始化程序环境，创建主窗口，并启动程序。
 */
int main(int argc, char *argv[])
{
    // 创建QApplication对象
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("Simple-Media-Player");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Simple-Media-Player");

    // 初始化FFmpeg
    Utils::initializeFFmpeg();

    // 创建主窗口
    MainWindow window;
    window.show();

    return app.exec();
}