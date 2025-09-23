/********************************************************************************
 * @file   : Utils.h
 * @brief  : 声明了初始化和错误处理函数。
 *
 * 该文件声明了程序中用于初始化和错误处理的函数。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace AuroraPlayer {
    namespace Utils {
        /**
         * @brief 初始化 FFmpeg
         */
        void initializeFFmpeg();

        /**
         * @brief 获取 FFmpeg 错误信息
         *
         * @param errorCode 错误码
         * @return QString 错误信息
         */
        QString getErrorMessage(int errorCode);

        /**
         * @brief 格式化时间（毫秒转换为 HH:MM:SS 格式）
         *
         * @param timeInMs 时间（毫秒）
         * @return QString 格式化后的时间字符串
         */
        QString formatTime(qint64 timeInMs);

    } // namespace Utils
}// namespace AuroraPlayer

#endif // UTILS_H