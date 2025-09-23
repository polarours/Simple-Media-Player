/********************************************************************************
 * @file   : PlaylistManager.h
 * @brief  : 声明了 PlaylistManager 类。
 *
 * 该文件声明了 PlaylistManager 类，负责管理播放列表功能。
 *
 * @author : polarours
 * @date   : 2025/09/22
 ********************************************************************************/

#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include <QStringList>
#include "CommonState.h"

/**
 * @class PlaylistManager
 * @brief 播放列表管理类
 * 
 * 该类负责管理媒体文件的播放列表，包括添加文件、移除文件、
 * 切换曲目等功能。
 */
class PlaylistManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit PlaylistManager(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~PlaylistManager();

    /**
     * @brief 添加文件到播放列表
     *
     * @param filePath 文件路径
     */
    void addFile(const QString& filePath);

    /**
     * @brief 批量添加文件到播放列表
     *
     * @param filePaths 文件路径列表
     */
    void addFiles(const QStringList& filePaths);

    /**
     * @brief 从播放列表中移除文件
     *
     * @param index 文件索引
     */
    void removeFile(int index);

    /**
     * @brief 清空播放列表
     */
    void clear();

    /**
     * @brief 获取播放列表中的文件数量
     *
     * @return int 文件数量
     */
    int count() const;

    /**
     * @brief 获取当前播放文件的索引
     *
     * @return int 当前文件索引
     */
    int currentIndex() const;

    /**
     * @brief 获取指定索引的文件路径
     *
     * @param index 文件索引
     * @return QString 文件路径
     */
    QString filePathAt(int index) const;

    /**
     * @brief 获取当前播放的文件路径
     *
     * @return QString 当前文件路径
     */
    QString currentFile() const;

    /**
     * @brief 设置当前播放索引
     *
     * @param index 文件索引
     */
    void setCurrentIndex(int index);

    /**
     * @brief 播放下一个文件
     *
     * @return bool 是否成功切换到下一个文件
     */
    bool next();

    /**
     * @brief 播放上一个文件
     *
     * @return bool 是否成功切换到上一个文件
     */
    bool previous();

    /**
     * @brief 检查是否是第一个文件
     *
     * @return bool 是否是第一个文件
     */
    bool isFirst() const;

    /**
     * @brief 检查是否是最后一个文件
     *
     * @return bool 是否是最后一个文件
     */
    bool isLast() const;

    /**
     * @brief 获取当前播放列表模式
     *
     * @return AuroraPlayer::State::PlaylistMode 播放列表模式
     */
    AuroraPlayer::State::PlaylistMode playlistMode() const;

    /**
     * @brief 设置播放列表模式
     *
     * @param mode 播放列表模式
     */
    void setPlaylistMode(AuroraPlayer::State::PlaylistMode mode);

signals:
    /**
     * @brief 播放列表发生变化信号
     */
    void playlistChanged();

    /**
     * @brief 当前播放项发生变化信号
     *
     * @param mediaPath 新的媒体文件路径
     */
    void currentIndexChanged(const QString& mediaPath);

private:
    QStringList m_playlist;                           ///< 播放列表
    int m_currentIndex;                               ///< 当前播放索引
    AuroraPlayer::State::PlaylistMode m_playlistMode; ///< 播放列表模式
};

#endif // AURORAPLAYER_PLAYER_PLAYLISTMANAGER_H