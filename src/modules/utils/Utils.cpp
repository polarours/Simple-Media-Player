/********************************************************************************
 * @file   : FFmpegHelper.cpp
 * @brief  : 实现了 FFmpegHelper 类。
 *
 * 该文件实现了程序中用于处理 FFmpeg 的辅助类，用于处理 FFmpeg 的错误信息。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "../../../include/Simple-Media-Player/modules/utils/Utils.h"

#include <bits/codecvt.h>

extern "C" {
#include <libavutil/error.h>
#include <libavutil/log.h>
}

/**
 * @brief 获取 FFmpeg 错误信息。
 *
 * @param errorCode 错误码。
 * @return QString 错误信息。
 */
QString Utils::getErrorMessage(int  errorCode) {
    char errorBuf[AV_ERROR_MAX_STRING_SIZE] = {0};
    av_strerror(errorCode, errorBuf, AV_ERROR_MAX_STRING_SIZE);
    return QString(errorBuf);
}

/**
 * @brief 初始化 FFmpeg。
 */
void Utils::initializeFFmpeg()
{
    // 设置日志级别
    av_log_set_level(AV_LOG_QUIET);
}