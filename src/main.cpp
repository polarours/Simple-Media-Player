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
#include "MainWindow.h"
#include "FFmpegHelper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Learn Media Player");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Simple-Media-Player");

    FFmpegHelper::initializeFFmpeg();

    MainWindow window;
    window.show();
    
    return app.exec();
}