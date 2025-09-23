/********************************************************************************
 * @file   : CommonState.h
 * @brief  : 声明了通用的状态枚举类型。
 *
 * 该文件声明了程序中使用的通用状态枚举类型。
 *
 * @author : polarours
 * @date   : 2025/09/22
 ********************************************************************************/

#ifndef COMMONSTATE_H
#define COMMONSTATE_H

namespace AuroraPlayer {
    namespace State {
        /**
         * @brief 播放器状态枚举
         */
        enum class PlayerState {
            Stopped,  ///< 停止状态
            Playing,  ///< 播放状态
            Paused,   ///< 暂停状态
            Error     ///< 错误状态
        };

        /**
         * @brief 播放列表模式枚举
         */
        enum class PlaylistMode {
            Sequential,  ///< 顺序播放
            Loop,        ///< 循环播放
            Random       ///< 随机播放
        };
    }
}

#endif // COMMONSTATE_H