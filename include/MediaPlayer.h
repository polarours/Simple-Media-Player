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
    explicit MediaPlayer(QObject *parent = nullptr);
    ~MediaPlayer();

    bool loadMedia(const QString &filePath);
    void play();
    void pause();
    void stop();
    bool isPlaying() const;
    qint64 duration() const;
    qint64 position() const;
    void setPosition(qint64 position);

signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void stateChanged(int state); // 0=stopped, 1=playing, 2=pause

private:
    // FFmpeg 相关变量
    AVFormatContext *formatContext;
    AVCodecContext *videoCodecContext;
    AVCodecContext *audioCodecContext;
    AVStream *videoStream;
    AVStream *audioStream;
    int videoStreamIndex;
    int audioStreamIndex;

    bool playing;
    bool paused;
};

#endif // MEDIAPLAYER_H