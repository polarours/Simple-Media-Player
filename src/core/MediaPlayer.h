/********************************************************************************
 * @file   : MediaPlayer.h
 * @brief  : 定义了 MediaPlayer 类。
 *
 * 该文件定义了程序的 MediaPlayer 类，用于处理媒体播放。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef AURORAPLAYER_MEDIAPLAYER_H
#define AURORAPLAYER_MEDIAPLAYER_H


#include <QTimer>
#include <QString>

#include "CommonState.h"

// --- FFmpeg 头文件 --- //
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

// --- 前向声明 --- //
class QVideoWidget;
class QAudioOutput;

class MediaPlayer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     *
     * @param parent 父对象
     */
    explicit MediaPlayer(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MediaPlayer();

    /**
     * @brief 设置媒体文件路径
     *
     * @param mediaPath  媒体文件路径
     */
    void setMedia(const QString& mediaPath);

    /**
     * @brief 设置视频输出组件
     *
     * @param widget  视频输出组件
     */
    void setVideoOutput(QVideoWidget* widget);

    /**
     * @brief 获取媒体文件的总时长
     *
     * @return qint64  媒体文件的总时长
     */
    qint64 duration() const;

    /**
     * @brief 获取媒体文件的当前播放位置
     *
     * @return qint64  媒体文件的当前播放位置
     */
    qint64 position() const;

    /**
     * @brief 获取当前播放状态
     *
     * @return AuroraPlayer::State::PlayerState 当前播放状态
     */
    AuroraPlayer::State::PlayerState state() const;

public slots:
    /**
     * @brief 播放媒体文件
     *
     * 该函数负责播放媒体文件。
     */
    void play();

    /**
     * @brief 暂停媒体播放
     */
    void pause();

    /**
     * @brief 停止媒体播放
     */
    void stop();

    /**
     * @brief 设置媒体播放位置
     *
     * @param position  播放位置（毫秒）
     */
    void setPosition(qint64 position);

    /**
     * @brief 设置音量
     *
     * @param volume  音量（0-100）
     */
    void setVolume(int volume);

signals:
    /**
     * @brief 媒体文件的播放状态改变信号
     *
     * @param state  媒体文件的播放状态
     */
    void stateChanged(AuroraPlayer::State::PlayerState state);

    /**
     * @brief 媒体文件的播放位置改变信号
     *
     * @param duration  媒体文件的总时长
     */
    void durationChanged(qint64 duration);

    /**
     * @brief 媒体文件的播放位置改变信号
     *
     * @param position  播放位置（毫秒）
     */
    void positionChanged(qint64 position);

private slots:
    /**
     * @brief 更新播放位置
     */
    void updatePosition();

private:
    /**
     * @brief 初始化 FFmpeg
     *
     * @param mediaPath  媒体文件路径
     * @return bool  初始化是否成功
     */
    bool initializeFFmpeg(const QString& mediaPath);

    /**
     * @brief 清理 FFmpeg 资源
     */
    void cleanupFFmpeg();

    /**
     * @brief 设置播放状态
     *
     * @param state 新的播放状态
     */
    void setState(AuroraPlayer::State::PlayerState state);

private:
    // --- 播放状态 --- //
    AuroraPlayer::State::PlayerState m_state; ///< 当前播放状态

    // --- 播放位置参数 --- //
    qint64 currentPosition; ///< 当前播放位置
    qint64 mediaDuration;   ///< 媒体总时长
    QTimer* positionTimer;  ///< 播放位置定时器

    // --- 播放参数 --- //
    int videoStreamIndex; ///< 视频流索引
    int audioStreamIndex; ///< 音频流索引

    // --- FFmpeg 相关变量 --- //
    AVStream* videoStream;             ///< 视频流
    AVStream* audioStream;             ///< 音频流
    AVFormatContext* formatContext;    ///< 格式上下文
    AVCodecContext* videoCodecContext; ///< 视频解码器上下文
    AVCodecContext* audioCodecContext; ///< 音频解码器上下文
    QVideoWidget* videoOutput;         ///< 视频输出组件
    QAudioOutput* audioOutput;         ///< 音频输出组件
};

#endif // AURORAPLAYER_MEDIAPLAYER_H