/********************************************************************************
 * @file   : Utils.cpp
 * @brief  : 实现了初始化和错误处理函数。
 *
 * 该文件实现了程序中用于初始化和错误处理的函数。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "Utils.h"

extern "C" {
#include <libavutil/error.h>
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace AuroraPlayer {
    namespace Utils {

        QString getErrorMessage(int errorCode) {
            char errorBuf[AV_ERROR_MAX_STRING_SIZE] = {0};
            av_strerror(errorCode, errorBuf, AV_ERROR_MAX_STRING_SIZE);
            return QString(errorBuf);
        }

        void initializeFFmpeg()
        {
            // 设置日志级别
            av_log_set_level(AV_LOG_INFO);
            
            // 注册所有可用的编解码器、解复用器等
            avformat_network_init();
            
#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(58, 9, 100)
            // 旧版本需要显式注册
            av_register_all();
#endif
        }

        QString formatTime(qint64 timeInMs) {
            qint64 seconds = timeInMs / 1000;
            qint64 minutes = seconds / 60;
            qint64 hours = minutes / 60;

            seconds %= 60;
            minutes %= 60;

            // 根据时间长度决定格式
            if (hours > 0) {
                return QString("%1:%2:%3")
                    .arg(hours, 2, 10, QLatin1Char('0'))
                    .arg(minutes, 2, 10, QLatin1Char('0'))
                    .arg(seconds, 2, 10, QLatin1Char('0'));
            } else {
                return QString("%1:%2")
                    .arg(minutes, 2, 10, QLatin1Char('0'))
                    .arg(seconds, 2, 10, QLatin1Char('0'));
            }
        }

    } // namespace Utils
}// namespace AuroraPlayer