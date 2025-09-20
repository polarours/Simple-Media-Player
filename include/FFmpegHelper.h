/********************************************************************************
 * @file   : FFmpegHelper.h
 * @brief  : 定义了 FFmpegHelper 类。
 *
 * 该文件是 FFmpegHelper 类的头文件，用于处理 FFmpeg 库的错误信息。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef FFMPEGHELPER_H
#define FFMPEGHELPER_H

#include <QString>

class FFmpegHelper
{
public:
    static QString getErrorString(int error);
    static void initializeFFmpeg();
};

#endif // FFMPEGHELPER_H