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
#include "PlaylistManager.h"
#include <QVideoWidget>
#include <QUrl>
#include <QAudioOutput>
#include <QMediaMetaData>

/**
 * @brief 构造函数。
 *
 * @param parent  父对象。
 */
PlayerController::PlayerController(QObject *parent)
    : QObject(parent)                                    ///< 继承自 QObject
    , mediaPlayer(new QMediaPlayer(this))          ///< 创建媒体播放器
    , audioOutput(new QAudioOutput(this))          ///< 创建音频输出
    , m_playlistManager(new PlaylistManager(this)) ///< 创建播放列表管理器
{
    mediaPlayer->setAudioOutput(audioOutput);
    
    // 设置播放器的视频输出为默认的null对象，稍后会通过setVideoOutput设置
    mediaPlayer->setVideoOutput(nullptr);
    
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &PlayerController::durationChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &PlayerController::positionChanged);
    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &PlayerController::playbackStateChanged);
    connect(mediaPlayer, &QMediaPlayer::metaDataChanged, this, &PlayerController::metaDataChanged);
    connect(mediaPlayer, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error error) {
                qDebug() << "Media player error:" << error << "-" << mediaPlayer->errorString();
                //emit errorOccurred();
            });
    
    // 连接播放列表管理器的信号
    connect(m_playlistManager, &PlaylistManager::currentIndexChanged, this, &PlayerController::onCurrentMediaChanged);
    connect(m_playlistManager, &PlaylistManager::playlistChanged, this, &PlayerController::playlistChanged);
}

/**
 * @brief 析构函数。
 */
PlayerController::~PlayerController()
{
    // TODO: 释放资源
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
void PlayerController::setMedia(const QString& mediaPath)
{
    m_playlistManager->addFile(mediaPath);
    m_playlistManager->setCurrentIndex(m_playlistManager->count() - 1);
    mediaPlayer->setSource(QUrl::fromLocalFile(mediaPath));
}

/**
 * @brief 获取播放列表管理器
 *
 * @return PlaylistManager* 播放列表管理器实例
 */
PlaylistManager* PlayerController::playlistManager() const
{
    return m_playlistManager;
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
 * @brief 暂停媒体播放
 */
void PlayerController::pause()
{
    mediaPlayer->pause();
}

/**
 * @brief 停止媒体播放
 */
void PlayerController::stop()
{
    mediaPlayer->stop();
}

/**
 * @brief 设置媒体播放位置
 *
 * @param position  播放位置（毫秒）
 */
void PlayerController::setPosition(qint64 position)
{
    mediaPlayer->setPosition(position);
}

/**
 * @brief 设置音量
 *
 * @param volume  音量（0-100）
 */
void PlayerController::setVolume(int volume)
{
    // 确保音量在有效范围内
    int clampedVolume = qBound(0, volume, 100);
    audioOutput->setVolume(clampedVolume / 100.0);
}

/**
 * @brief 获取当前音量
 *
 * @return int 当前音量（0-100）
 */
int PlayerController::volume() const
{
    return static_cast<int>(audioOutput->volume() * 100);
}

/**
 * @brief 播放下一个媒体文件
 */
void PlayerController::nextMedia()
{
    if (m_playlistManager->next()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(m_playlistManager->currentFile()));
        play();
    }
}

/**
 * @brief 播放上一个媒体文件
 */
void PlayerController::previousMedia()
{
    if (m_playlistManager->previous()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(m_playlistManager->currentFile()));
        play();
    }
}

/**
 * @brief 处理当前媒体文件变化
 *
 * @param mediaPath 新的媒体文件路径
 */
void PlayerController::onCurrentMediaChanged(const QString& mediaPath)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(mediaPath));
}