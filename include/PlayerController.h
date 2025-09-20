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
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit PlayerController(QObject *parent = nullptr);

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
     * @brief 判断是否正在播放
     *
     * @return  是否正在播放
     */
    bool isPlaying() const;

    /**
     * @brief 获取媒体文件时长
     *
     * @return  媒体文件时长
     */
    qint64 duration() const;

    /**
     * @brief 获取当前播放位置
     *
     * @return  当前播放位置
     */
    qint64 position() const;

public slots:
    /**
     * @brief 播放媒体文件
     */
    void play();

    /**
     * @brief 暂停播放媒体文件
     */
    void pause();

    /**
     *  @brief 停止播放媒体文件
     */
    void stop();

    /**
     * @brief 设置播放位置
     *
     * @param position  播放位置
     */
    void setPosition(qint64 position);

    /**
     * @brief 设置音量
     *
     * @param volume 音量
     */
    void setVolume(int volume);

signals:
    /**
     * @brief 媒体文件时长改变信号
     *
     * @param duration 媒体文件时长
     */
    void durationChanged(qint64 duration);

    /**
     * @brief 媒体文件播放位置改变信号
     *
     * @param position 媒体文件播放位置
     */
    void positionChanged(qint64 position);

private:
    QMediaPlayer* mediaPlayer; ///< 媒体播放器
    QAudioOutput* audioOutput; ///< 音频输出
};

#endif // PLAYERCONTROLLER_H