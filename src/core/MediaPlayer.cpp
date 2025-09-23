/********************************************************************************
 * @file   : MediaPlayer.cpp
 * @brief  : 实现了 MediaPlayer 类。
 *
 * 该文件实现了程序的 MediaPlayer 类，用于处理媒体播放。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "MediaPlayer.h"
#include "../utils/Utils.h"
#include <QVideoWidget>
#include <QAudioOutput>
#include <QFile>
#include <QTimer>
#include <QDebug>

extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
}

/**
 * @brief MediaPlayer 的构造函数。
 *
 * @param parent  父对象。
 */
MediaPlayer::MediaPlayer(QObject *parent)
    : QObject(parent)
    , m_state(AuroraPlayer::State::PlayerState::Stopped) // 初始状态为停止
    , currentPosition(0)                                 // 当前播放位置
    , mediaDuration(0)                                   // 媒体时长
    , positionTimer(new QTimer(this))              // 定时器
    , videoStreamIndex(-1)                               // 视频流索引
    , audioStreamIndex(-1)                               // 音频流索引
    , videoStream(nullptr)                               // 视频流
    , audioStream(nullptr)                               // 音频流
    , formatContext(nullptr)                             // 格式上下文
    , videoCodecContext(nullptr)                         // 视频编解码器上下文
    , audioCodecContext(nullptr)                         // 音频编解码器上下文
    , videoOutput(nullptr)                               // 视频输出组件
    , audioOutput(nullptr)                               // 音频输出组件
{
    // 连接定时器信号和槽
    connect(positionTimer, &QTimer::timeout, this, &MediaPlayer::updatePosition);
    positionTimer->setInterval(1000); // 1000ms更新一次
}

/**
 * @brief MediaPlayer 的析构函数。
 *
 * 该函数是 MediaPlayer 的析构函数，负责销毁 MediaPlayer 对象。
 */
MediaPlayer::~MediaPlayer()
{
    // TODO: 释放资源
}

/**
 * @brief 设置媒体文件路径。
 *
 * @param mediaPath  媒体文件路径。
 */
void MediaPlayer::setMedia(const QString& mediaPath)
{
    // 如果正在播放，则先停止
    if (m_state == AuroraPlayer::State::PlayerState::Playing || m_state == AuroraPlayer::State::PlayerState::Paused) {
        stop();
    }

    // 初始化 FFmpeg
    if (initializeFFmpeg(mediaPath)) {
        // 发出时长变化信号
        emit durationChanged(mediaDuration);
    } else {
        // 初始化失败，设置状态为错误
        setState(AuroraPlayer::State::PlayerState::Error);
    }
}

/**
 * @brief 设置视频输出组件。
 *
 * @param widget  视频输出组件。
 */
void MediaPlayer::setVideoOutput(QVideoWidget* widget)
{
    videoOutput = widget;
}

/**
 * @brief 获取媒体文件的总时长。
 *
 * @return qint64  媒体文件的总时长。
 */
qint64 MediaPlayer::duration() const
{
    return mediaDuration;
}

/**
 * @brief 获取媒体文件的当前播放位置。
 *
 * @return qint64  媒体文件的当前播放位置。
 */
qint64 MediaPlayer::position() const
{
    return currentPosition;
}

/**
 * @brief 获取当前播放状态
 * @return AuroraPlayer::PlayerState 当前播放状态
 */
AuroraPlayer::State::PlayerState MediaPlayer::state() const
{
    return m_state;
}

/**
 * @brief 播放媒体文件。
 *
 * 该函数负责播放媒体文件。
 */
void MediaPlayer::play()
{
    // 如果没有设置媒体文件，则返回
    if (m_state == AuroraPlayer::State::PlayerState::Stopped && !formatContext) {
        return;
    }

    // 如果是暂停状态，则恢复播放
    if (m_state == AuroraPlayer::State::PlayerState::Paused) {
        setState(AuroraPlayer::State::PlayerState::Playing);
        positionTimer->start();
        return;
    }

    // 如果是停止状态，则开始播放
    if (m_state == AuroraPlayer::State::PlayerState::Stopped) {
        setState(AuroraPlayer::State::PlayerState::Playing);
        positionTimer->start();
        return;
    }
}

/**
 * @brief 暂停媒体播放。
 */
void MediaPlayer::pause()
{
    if (m_state == AuroraPlayer::State::PlayerState::Playing) {
        setState(AuroraPlayer::State::PlayerState::Paused);
        positionTimer->stop();
    }
}

/**
 * @brief 停止媒体播放。
 */
void MediaPlayer::stop()
{
    if (m_state != AuroraPlayer::State::PlayerState::Stopped) {
        setState(AuroraPlayer::State::PlayerState::Stopped);
        positionTimer->stop();
        currentPosition = 0;
        emit positionChanged(0);
    }
}

/**
 * @brief 设置媒体播放位置。
 *
 * @param position  播放位置（毫秒）。
 */
void MediaPlayer::setPosition(qint64 position)
{
    if (position >= 0 && position <= mediaDuration) {
        currentPosition = position;
        emit positionChanged(position);
    }else {
        qWarning() << "Invalid position:" << position;
    }
}

/**
 * @brief 设置音量。
 *
 * @param volume  音量（0-100）。
 */
void MediaPlayer::setVolume(int volume)
{
    // TODO: 实现音量控制
    Q_UNUSED(volume);
}

/**
 * @brief 初始化 FFmpeg。
 *
 * @param mediaPath  媒体文件路径。
 * @return bool  初始化是否成功。
 */
bool MediaPlayer::initializeFFmpeg(const QString& mediaPath)
{
    // 检查文件是否存在
    QFile file(mediaPath);
    if (!file.exists()) {
        qWarning() << "File does not exist:" << mediaPath;
        return false;
    }

    // 打开媒体文件
    if (avformat_open_input(&formatContext, mediaPath.toLocal8Bit().constData(), nullptr, nullptr) < 0) {
        qWarning() << "Failed to open media file:" << mediaPath;
        return false;
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qWarning() << "Failed to find stream info:" << mediaPath;
        return false;
    }

    // 查找视频和音频流
    videoStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    audioStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);

    // 获取视频流
    if (videoStreamIndex >= 0) {
        videoStream = formatContext->streams[videoStreamIndex];
    }

    // 获取音频流
    if (audioStreamIndex >= 0) {
        audioStream = formatContext->streams[audioStreamIndex];
    }

    // 获取媒体时长（毫秒）
    if (formatContext->duration != AV_NOPTS_VALUE) {
        mediaDuration = formatContext->duration / 1000;
    }

    return true;
}

/**
 * @brief 清理 FFmpeg 资源。
 */
void MediaPlayer::cleanupFFmpeg()
{
    // 清理视频解码器上下文
    if (videoCodecContext) {
        avcodec_free_context(&videoCodecContext);
    }

    // 清理音频解码器上下文
    if (audioCodecContext) {
        avcodec_free_context(&audioCodecContext);
    }

    // 清理格式上下文
    if (formatContext) {
        avformat_close_input(&formatContext);
    }

    // 重置流索引
    videoStreamIndex = -1;
    audioStreamIndex = -1;
}

/**
 * @brief 更新播放位置。
 */
void MediaPlayer::updatePosition()
{
    if (m_state == AuroraPlayer::State::PlayerState::Playing) {
        currentPosition += 1000; // 每秒增加1秒
        if (currentPosition >= mediaDuration) {
            // 播放完成
            stop();
        } else {
            emit positionChanged(currentPosition);
        }
    }
}

/**
 * @brief 设置播放状态
 *
 * @param state 新的播放状态
 */
void MediaPlayer::setState(AuroraPlayer::State::PlayerState state)
{
    if (m_state != state) {
        m_state = state;
        emit stateChanged(m_state);
    }
}