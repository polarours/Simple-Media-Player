/********************************************************************************
 * @file   : PlayerController.cpp
 * @brief  : 实现了 PlayerController 类。
 *
 * 该文件实现了 PlayerController 类，负责管理媒体播放器的状态和播放。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "PlayerController.h"
#include <QVideoWidget>
#include <QUrl>
#include <QAudioOutput>

PlayerController::PlayerController(QObject *parent)
    : QObject(parent)
    , mediaPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    mediaPlayer->setAudioOutput(audioOutput);
    
    connect(mediaPlayer, &QMediaPlayer::durationChanged, 
            this, &PlayerController::durationChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, 
            this, &PlayerController::positionChanged);
}

PlayerController::~PlayerController()
{
    //
}

void PlayerController::setVideoOutput(QVideoWidget *widget)
{
    mediaPlayer->setVideoOutput(widget);
}

void PlayerController::setMedia(const QString &mediaPath)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(mediaPath));
}

bool PlayerController::isPlaying() const
{
    return mediaPlayer->playbackState() == QMediaPlayer::PlayingState;
}

qint64 PlayerController::duration() const
{
    return mediaPlayer->duration();
}

qint64 PlayerController::position() const
{
    return mediaPlayer->position();
}

void PlayerController::play()
{
    mediaPlayer->play();
}

void PlayerController::pause()
{
    mediaPlayer->pause();
}

void PlayerController::stop()
{
    mediaPlayer->stop();
}

void PlayerController::setPosition(qint64 position)
{
    mediaPlayer->setPosition(position);
}

void PlayerController::setVolume(int volume)
{
    audioOutput->setVolume(volume / 100.0);
}