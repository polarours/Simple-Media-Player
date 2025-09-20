/********************************************************************************
 * @file   : PlayerController.h
 * @brief  : 定义了 PlayerController 类。
 *
 * 该文件定义了程序的 PlayerController 类，用于控制媒体播放器。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QString>

// 前向声明
class QVideoWidget;
class QAudioOutput;

class PlayerController : public QObject
{
    Q_OBJECT

public:
    explicit PlayerController(QObject *parent = nullptr);
    ~PlayerController();

    void setVideoOutput(QVideoWidget *widget);
    void setMedia(const QString &mediaPath);

    bool isPlaying() const;
    qint64 duration() const;
    qint64 position() const;

public slots:
    void play();
    void pause();
    void stop();
    void setPosition(qint64 position);
    void setVolume(int volume);

signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private:
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // PLAYERCONTROLLER_H