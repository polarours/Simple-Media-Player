/********************************************************************************
 * @file   : MediaPlayer.cpp
 * @brief  : 实现了 MediaPlayer 类。
 *
 * 该文件实现了 MediaPlayer 类，负责处理媒体文件的加载、播放、暂停和停止。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "MediaPlayer.h"
#include <QDebug>

extern "C" {
#include <libavutil/log.h>
}

/**
 * @brief 构造函数
 *
 * 该函数是 MediaPlayer 类的构造函数，负责初始化媒体播放器。
 */
MediaPlayer::MediaPlayer(QObject *parent)
    : QObject(parent)
    , formatContext(nullptr)
    , videoCodecContext(nullptr)
    , audioCodecContext(nullptr)
    , videoStream(nullptr)
    , audioStream(nullptr)
    , videoStreamIndex(-1)
    , audioStreamIndex(-1)
    , playing(false)
    , paused(false)
{
    // 设置FFmpeg日志级别
    av_log_set_level(AV_LOG_QUIET);
}

/**
 * @brief 析构函数
 *
 * 该函数是 MediaPlayer 类的析构函数，负责清理媒体播放器的资源。
 */
MediaPlayer::~MediaPlayer()
{
    stop();

    if (videoCodecContext) {
        avcodec_free_context(&videoCodecContext);
    }

    if (audioCodecContext) {
        avcodec_free_context(&audioCodecContext);
    }

    if (formatContext) {
        avformat_close_input(&formatContext);
    }
}

/**
 * @brief 加载媒体文件
 *
 * 该函数用于加载指定的媒体文件。
 *
 * @param filePath 媒体文件的路径
 * @return 加载成功返回 true，否则返回 false
 */
bool MediaPlayer::loadMedia(const QString& filePath)
{
    // 关闭媒体文件
    if (formatContext) {
        avformat_close_input(&formatContext);
    }

    // 打开媒体文件
    if (avformat_open_input(&formatContext, filePath.toUtf8().constData(), nullptr, nullptr) < 0) {
        qDebug() << "Failed to open media file:" << filePath;
        return false;
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qDebug() << "Failed to retrieve stream information";
        return false;
    }

    // 找到视频和音频流
    videoStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    audioStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);

    if (videoStreamIndex >= 0) {
        videoStream = formatContext->streams[videoStreamIndex];
        
        // 找到视频解码器
        const AVCodec *videoCodec = avcodec_find_decoder(videoStream->codecpar->codec_id);
        if (!videoCodec) {
            qDebug() << "Unsupported video codec";
            return false;
        }

        // 分配视频解码器上下文
        videoCodecContext = avcodec_alloc_context3(videoCodec);
        if (!videoCodecContext) {
            qDebug() << "Failed to allocate video codec context";
            return false;
        }

        // 将视频流参数复制到解码器上下文
        if (avcodec_parameters_to_context(videoCodecContext, videoStream->codecpar) < 0) {
            qDebug() << "Failed to copy video codec parameters to context";
            return false;
        }

        // 打开视频解码器
        if (avcodec_open2(videoCodecContext, videoCodec, nullptr) < 0) {
            qDebug() << "Failed to open video codec";
            return false;
        }
    }

    if (audioStreamIndex >= 0) {
        audioStream = formatContext->streams[audioStreamIndex];

        // 找到音频解码器
        const AVCodec *audioCodec = avcodec_find_decoder(audioStream->codecpar->codec_id);
        if (!audioCodec) {
            qDebug() << "Unsupported audio codec";
        } else {
            // 分配音频解码器上下文
            audioCodecContext = avcodec_alloc_context3(audioCodec);
            if (!audioCodecContext) {
                qDebug() << "Failed to allocate audio codec context";
            } else {
                // 将音频流参数复制到解码器上下文
                if (avcodec_parameters_to_context(audioCodecContext, audioStream->codecpar) < 0) {
                    qDebug() << "Failed to copy audio codec parameters to context";
                } else {
                    // 打开音频解码器
                    if (avcodec_open2(audioCodecContext, audioCodec, nullptr) < 0) {
                        qDebug() << "Failed to open audio codec";
                    }
                }
            }
        }
    }

    // 发出媒体时长改变信号
    emit durationChanged(formatContext->duration / 1000); // Convert from microseconds to milliseconds

    return true;
}

/**
 * @brief 播放媒体文件
 *
 * 该函数用于播放媒体文件。
 */
void MediaPlayer::play()
{
    if (!formatContext)
        return;

    playing = true;
    paused = false;
    emit stateChanged(1); // Playing
}

/**
 * @brief 暂停媒体文件
 *
 * 该函数用于暂停媒体文件。
 */
void MediaPlayer::pause()
{
    if (!playing)
        return;

    paused = !paused;
    if (paused) {
        emit stateChanged(2); // Paused
    } else {
        emit stateChanged(1); // Playing
    }
}

/**
 * @brief 停止媒体文件
 *
 * 该函数用于停止媒体文件。
 */
void MediaPlayer::stop()
{
    playing = false;
    paused = false;
    emit stateChanged(0); // Stopped
}

/**
 * @brief 获取媒体文件是否正在播放
 *
 * 该函数用于获取媒体文件是否正在播放。
 *
 * @return 正在播放返回 true，否则返回 false
 */
bool MediaPlayer::isPlaying() const
{
    return playing && !paused;
}

/**
 * @brief 获取媒体文件的总时长
 *
 * 该函数用于获取媒体文件的总时长。
 */
qint64 MediaPlayer::duration() const
{
    if (!formatContext)
        return 0;

    return formatContext->duration / 1000;
}

/**
 * @brief 获取当前播放位置
 *
 * 该函数用于获取当前播放位置。
 */
qint64 MediaPlayer::position() const
{
    return 0;
}

/**
 * @brief 设置当前播放位置
 *
 * @param position 要设置的播放位置
 *
 * 该函数用于设置当前播放位置。
 */
void MediaPlayer::setPosition(qint64 position)
{
    Q_UNUSED(position);
}