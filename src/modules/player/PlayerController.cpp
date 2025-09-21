/********************************************************************************
 * @file   : PlayerController.cpp
 * @brief  : 实现了 PlayerController 类。
 *
 * 该文件实现了 PlayerController 类，负责管理媒体播放器的状态和播放。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "../../../include/Simple-Media-Player/modules/player/PlayerController.h"
#include <QVideoWidget>
#include <QUrl>
#include <QAudioOutput>

/**
 * @brief 构造函数。
 *
 * @param parent  父对象。
 */
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

/**
 * @brief 析构函数。
 */
PlayerController::~PlayerController()
{
    // 释放资源
}

/**
 * @brief 设置视频输出部件。
 *
 * @param widget  视频输出部件。
 */
void PlayerController::setVideoOutput(QVideoWidget *widget)
{
    mediaPlayer->setVideoOutput(widget);
}

/**
 * @brief 设置媒体文件。
 *
 * @param mediaPath  媒体文件路径。
 */
void PlayerController::setMedia(const QString &mediaPath)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(mediaPath));
}

/**
 * @brief 获取媒体是否正在播放。
 *
 * @return true  媒体正在播放。
 * @return false 媒体没有播放。
 */
bool PlayerController::isPlaying() const
{
    return mediaPlayer->playbackState() == QMediaPlayer::PlayingState;
}

/**
 * @brief 获取媒体文件的总时长。
 *
 * @return qint64  媒体文件的总时长。
 */
qint64 PlayerController::duration() const
{
    return mediaPlayer->duration();
}

/**
 * @brief 获取媒体文件的当前播放位置。
 *
 * @return qint64  媒体文件的当前播放位置。
 */
qint64 PlayerController::position() const
{
    return mediaPlayer->position();
}

/**
 * @brief 播放媒体文件。
 *
 * 该函数负责播放媒体文件。
 */
void PlayerController::play()
{
    mediaPlayer->play();
}

/**
 * @brief 暂停媒体文件。
 *
 * 该函数负责暂停媒体文件。
 */
void PlayerController::pause()
{
    mediaPlayer->pause();
}

/**
 * @brief 停止媒体文件。
 *
 * 该函数负责停止媒体文件。
 */
void PlayerController::stop()
{
    mediaPlayer->stop();
}

/**
 * @brief 设置媒体文件的播放位置。
 *
 * @param position  播放位置。
 */
void PlayerController::setPosition(qint64 position)
{
    mediaPlayer->setPosition(position);
}

/**
 * @brief 设置媒体文件的音量。
 *
 * @param volume  音量。
 */
void PlayerController::setVolume(int volume)
{
    audioOutput->setVolume(volume / 100.0);
}