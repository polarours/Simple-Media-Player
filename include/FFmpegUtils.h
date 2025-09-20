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

class FFmpegUtils
{
public:
    /**
     * @brief 获取错误信息
     *
     * @param errorCode 错误码
     * @return QString 错误信息
     */
    static QString getErrorMessage(int errorCode);

    /**
     *  @brief 初始化 FFmpeg
     */
    static void initializeFFmpeg();
};

#endif // FFMPEGHELPER_H