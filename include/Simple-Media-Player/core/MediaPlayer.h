/********************************************************************************
 * @file   : MediaPlayer.h
 * @brief  : 定义了 MediaPlayer 类。
 *
 * 该文件定义了程序的 MediaPlayer 类，用于播放媒体文件，支持多种格式的媒体文件。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QString>
#include <QTimer>

// 前向声明 FFmpeg 的头文件
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/time.h>
}

class MediaPlayer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     *
     * 初始化程序的 MediaPlayer 类，负责处理媒体文件的加载、播放、暂停和停止。
     */
    explicit MediaPlayer(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     *
     * 释放程序的 MediaPlayer 类。
     */
    ~MediaPlayer();

    /**
     * @brief 加载媒体文件
     *
     * @param filePath  媒体文件路径
     * @return 媒体文件是否加载成功
     */
    bool loadMedia(const QString& filePath);

    /**
     * @brief 播放媒体文件
     */
    void play();

    /**
     * @brief 暂停媒体文件
     */
    void pause();

    /**
     * @brief 停止媒体文件
     */
    void stop();

    /**
     * @brief 获取媒体文件是否正在播放
     *
     * @return  媒体文件是否正在播放
     */
    bool isPlaying() const;

    /**
     * @brief 获取媒体文件的总时长
     *
     * @return 媒体文件的总时长
     */
    qint64 duration() const;

    /**
     * @brief 获取媒体文件的当前播放位置
     *
     * @return  媒体文件的当前播放位置
     */
    qint64 position() const;

    void updatePosition(qint64 position);

    /**
     * @brief 设置媒体文件的当前播放位置
     *
     * @param position  媒体文件的当前播放位置
     */
    void setPosition(qint64 position);

signals:
    /**
     * @brief 媒体文件的总时长改变信号
     *
     * @param duration  媒体文件的总时长
     */
    void durationChanged(qint64 duration);

    /**
     *  @brief 媒体文件的当前播放位置改变信号
     *
     * @param position  媒体文件的当前播放位置
     */
    void positionChanged(qint64 position);

    /**
     * @brief 媒体文件的播放状态改变信号
     *
     * @param state  媒体文件的播放状态
     *
     * 0=stopped, 1=playing, 2=pause
     */
    void stateChanged(int state);

private:
    // --- 播放状态 --- //
    bool playing; ///< 是否正在播放
    bool paused;  ///< 是否处于暂停状态

    // --- 播放位置参数 --- //
    qint64 currentPosition; ///< 当前播放位置
    QTimer* positionTimer;  ///< 播放位置定时器

    // --- 播放参数 --- //
    int videoStreamIndex; ///< 视频流索引
    int audioStreamIndex; ///< 音频流索引

    // --- FFmpeg 相关变量 --- //
    AVStream* videoStream;             ///< 视频流
    AVStream* audioStream;             ///< 音频流
    AVFormatContext* formatContext;    ///< 格式上下文
    AVCodecContext* videoCodecContext; ///< 视频编解码器上下文
    AVCodecContext* audioCodecContext; ///< 音频编解码器上下文
};

#endif // MEDIAPLAYER_H