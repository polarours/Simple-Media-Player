/********************************************************************************
 * @file   : PlayerController.h
 * @brief  : 定义了 PlayerController 类。
 *
 * 该文件定义了程序的 PlayerController 类，用于控制媒体播放器。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef AURORAPLAYER_PLAYERCONTROLLER_H
#define AURORAPLAYER_PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QString>
#include "CommonState.h"

// 前向声明
class PlaylistManager;

class PlayerController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     *
     * @param parent 父对象
     */
    explicit PlayerController(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~PlayerController();

    /**
     * @brief 设置视频输出组件
     *
     * @param widget  视频输出组件
     */
    void setVideoOutput(QVideoWidget* widget);

    /**
     * @brief 设置媒体文件路径
     *
     * @param mediaPath  媒体文件路径
     */
    void setMedia(const QString& mediaPath);

    /**
     * @brief 获取播放列表管理器
     *
     * @return PlaylistManager* 播放列表管理器实例
     */
    PlaylistManager* playlistManager() const;

    /**
     * @brief 获取媒体是否正在播放。
     *
     * @return true  媒体正在播放。
     * @return false 媒体未播放。
     */
    bool isPlaying() const;

    /**
     * @brief 获取媒体文件的总时长。
     *
     * @return qint64  媒体文件的总时长。
     */
    qint64 duration() const;

    /**
     * @brief 获取媒体文件的当前播放位置。
     *
     * @return qint64  媒体文件的当前播放位置。
     */
    qint64 position() const;

    /**
     * @brief 获取当前音量
     *
     * @return int 当前音量（0-100）
     */
    int volume() const;

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

    /**
     * @brief 播放下一个媒体文件
     */
    void nextMedia();

    /**
     * @brief 播放上一个媒体文件
     */
    void previousMedia();

signals:
    /**
     * @brief 媒体时长变化信号
     *
     * @param duration  媒体时长（毫秒）
     */
    void durationChanged(qint64 duration);

    /**
     * @brief 媒体播放位置变化信号
     *
     * @param position  播放位置（毫秒）
     */
    void positionChanged(qint64 position);

    /**
     * @brief 播放状态变化信号
     */
    void stateChanged();

    /**
     * @brief 播放列表发生变化信号
     */
    void playlistChanged();

    /**
     * @brief 发生错误信号
     */
    void errorOccured();
    
    /**
     * @brief 播放状态变化信号
     *
     * @param state 播放状态
     */
    void playbackStateChanged(QMediaPlayer::PlaybackState state);
    
    /**
     * @brief 媒体元数据变化信号
     */
    void metaDataChanged();

private slots:
    /**
     * @brief 处理当前媒体文件变化
     *
     * @param mediaPath 新的媒体文件路径
     */
    void onCurrentMediaChanged(const QString& mediaPath);

private:
    QMediaPlayer* mediaPlayer;          ///< 媒体播放器
    QAudioOutput* audioOutput;          ///< 音频输出
    PlaylistManager* m_playlistManager; ///< 播放列表管理器
};

#endif // AURORAPLAYER_PLAYERCONTROLLER_H