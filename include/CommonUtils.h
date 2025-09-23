/********************************************************************************
 * @file   : CommonUtils.h
 * @brief  : 定义了通用工具函数。
 *
 * 该文件定义了项目中通用的工具函数，方便在各个模块中使用。
 *
 * @author : polarours
 * @date   : 2025/09/22
 ********************************************************************************/

#ifndef AURORAPLAYER_COMMONUTILS_H
#define AURORAPLAYER_COMMONUTILS_H

#include <QString>

/**
 * @namespace AuroraPlayer::Utils
 * @brief 通用工具函数命名空间
 * 
 * 包含项目中常用的工具函数，如时间格式化等。
 */
namespace AuroraPlayer {
    namespace Utils {

        /**
         * @brief 格式化时间显示
         * @param duration 时间（毫秒）
         * @return QString 格式化后的时间字符串（mm:ss）
         */
        QString formatTime(qint64 duration);

        /**
         * @brief 从文件路径获取文件名
         * @param filePath 文件路径
         * @return QString 文件名
         */
        QString getFileNameFromPath(const QString& filePath);

        /**
         * @brief 获取 FFmpeg 错误信息
         * @param errorCode 错误码
         * @return QString 错误信息
         */
        QString getErrorMessage(int errorCode);
    } // namespace Utils
}// namespace AuroraPlayer

#endif // AURORAPLAYER_COMMONUTILS_H