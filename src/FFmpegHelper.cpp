/********************************************************************************
 * @file   : FFmpegHelper.cpp
 * @brief  : 实现了 FFmpegHelper 类。
 *
 * 该文件实现了程序中用于处理 FFmpeg 的辅助类，用于处理 FFmpeg 的错误信息。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "FFmpegHelper.h"

extern "C" {
#include <libavutil/error.h>
#include <libavutil/log.h>
}

QString FFmpegHelper::getErrorString(int error)
{
    char errorBuf[AV_ERROR_MAX_STRING_SIZE] = {0};
    av_strerror(error, errorBuf, AV_ERROR_MAX_STRING_SIZE);
    return QString(errorBuf);
}

void FFmpegHelper::initializeFFmpeg()
{
    // 设置日志级别
    av_log_set_level(AV_LOG_QUIET);
}