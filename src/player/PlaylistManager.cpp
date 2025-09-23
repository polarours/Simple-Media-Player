/********************************************************************************
 * @file   : PlaylistManager.cpp
 * @brief  : 实现了 PlaylistManager 类。
 *
 * 该文件实现了 PlaylistManager 类，负责管理播放列表功能。
 *
 * @author : polarours
 * @date   : 2025/09/22
 ********************************************************************************/

#include "PlaylistManager.h"
#include <CommonUtils.h>
#include <QDir>
#include <QUrl>
#include <QDebug>
#include <random>

// 创建一个静态随机数生成器
static std::random_device rd;
static std::mt19937 gen(rd());

/**
 * @brief PlaylistManager 的构造函数。
 *
 * @param parent  父对象。
 */
PlaylistManager::PlaylistManager(QObject *parent)
    : QObject(parent)
    , m_currentIndex(-1)
    , m_playlistMode(AuroraPlayer::State::PlaylistMode::Sequential)
{
    // TODO:
}

/**
 * @brief 析构函数
 */
PlaylistManager::~PlaylistManager()
{
    // TODO: 清理资源
}

/**
 * @brief 添加文件到播放列表。
 *
 * @param filePath  文件路径。
 */
void PlaylistManager::addFile(const QString& filePath)
{
    m_playlist.append(filePath);
    emit playlistChanged();
    
    // 如果是第一个文件，则设置为当前文件
    if (m_playlist.size() == 1) {
        setCurrentIndex(0);
    }
}

/**
 * @brief 批量添加文件到播放列表。
 *
 * @param filePaths  文件路径列表。
 */
void PlaylistManager::addFiles(const QStringList& filePaths)
{
    m_playlist.append(filePaths);
    emit playlistChanged();
    
    // 如果是第一次添加文件，则设置第一个文件为当前文件
    if (m_currentIndex == -1 && !filePaths.isEmpty()) {
        setCurrentIndex(0);
    }
}

/**
 * @brief 从播放列表中移除文件。
 *
 * @param index  文件索引。
 */
void PlaylistManager::removeFile(int index)
{
    if (index >= 0 && index < m_playlist.size()) {
        m_playlist.removeAt(index);
        
        // 调整当前索引
        if (m_currentIndex >= m_playlist.size()) {
            m_currentIndex = m_playlist.size() - 1;
        } else if (m_currentIndex > index) {
            m_currentIndex--;
        } else if (m_currentIndex == index) {
            // 如果删除的是当前文件，则尝试播放下一个文件
            if (m_currentIndex < m_playlist.size()) {
                // 当前索引仍然有效
            } else if (!m_playlist.isEmpty()) {
                // 当前索引超出范围，设置为最后一个文件
                m_currentIndex = m_playlist.size() - 1;
            } else {
                // 播放列表为空
                m_currentIndex = -1;
            }
            emit playlistChanged();
        }
    }
}

/**
 * @brief 清空播放列表
 */
void PlaylistManager::clear()
{
    m_playlist.clear();
    m_currentIndex = -1;
    emit playlistChanged();
}

/**
 * @brief 获取播放列表中的文件数量
 *
 * @return int 文件数量
 */
int PlaylistManager::count() const
{
    return m_playlist.size();
}

/**
 * @brief 获取当前播放文件的索引
 *
 * @return int 当前文件索引
 */
int PlaylistManager::currentIndex() const
{
    return m_currentIndex;
}

/**
 * @brief 获取指定索引的文件路径
 *
 * @param index 文件索引
 * @return QString 文件路径
 */
QString PlaylistManager::filePathAt(int index) const
{
    if (index >= 0 && index < m_playlist.size()) {
        return m_playlist.at(index);
    }
    return QString();
}

/**
 * @brief 获取当前播放的文件路径
 *
 * @return QString 当前文件路径
 */
QString PlaylistManager::currentFile() const
{
    return filePathAt(m_currentIndex);
}

/**
 * @brief 设置当前播放索引
 *
 * @param index 文件索引
 */
void PlaylistManager::setCurrentIndex(int index)
{
    if (index >= 0 && index < m_playlist.size() && index != m_currentIndex) {
        m_currentIndex = index;
        emit currentIndexChanged(m_playlist.at(index));
    }
}

/**
 * @brief 播放下一个文件。
 *
 * @return bool  是否成功切换到下一个文件。
 */
bool PlaylistManager::next()
{
    if (m_playlist.isEmpty()) {
        return false;
    }

    int nextIndex = m_currentIndex + 1;
    
    switch (m_playlistMode) {
        case AuroraPlayer::State::PlaylistMode::Sequential:
            if (nextIndex < m_playlist.size()) {
                setCurrentIndex(nextIndex);
                return true;
            }
            break;
            
        case AuroraPlayer::State::PlaylistMode::Loop:
            if (nextIndex >= m_playlist.size()) {
                nextIndex = 0;
            }
            setCurrentIndex(nextIndex);
            return true;
            
        case AuroraPlayer::State::PlaylistMode::Random:
            if (m_playlist.size() > 1) {
                // 简单的随机实现
                std::uniform_int_distribution<> dis(0, m_playlist.size() - 1);
                do {
                    nextIndex = dis(gen);
                } while (nextIndex == m_currentIndex && m_playlist.size() > 1);
                setCurrentIndex(nextIndex);
                return true;
            }
            break;
    }
    
    return false;
}

/**
 * @brief 播放上一个文件。
 *
 * @return bool  是否成功切换到上一个文件。
 */
bool PlaylistManager::previous()
{
    if (m_playlist.isEmpty()) {
        return false;
    }

    int prevIndex = m_currentIndex - 1;
    
    switch (m_playlistMode) {
        case AuroraPlayer::State::PlaylistMode::Sequential:
            if (prevIndex >= 0) {
                setCurrentIndex(prevIndex);
                return true;
            }
            break;
            
        case AuroraPlayer::State::PlaylistMode::Loop:
            if (prevIndex < 0) {
                prevIndex = m_playlist.size() - 1;
            }
            setCurrentIndex(prevIndex);
            return true;
            
        case AuroraPlayer::State::PlaylistMode::Random:
            if (m_playlist.size() > 1) {
                // 简单的随机实现
                std::uniform_int_distribution<> dis(0, m_playlist.size() - 1);
                do {
                    prevIndex = dis(gen);
                } while (prevIndex == m_currentIndex && m_playlist.size() > 1);
                setCurrentIndex(prevIndex);
                return true;
            }
            break;
    }
    
    return false;
}

/**
 * @brief 检查是否是第一个文件
 *
 * @return bool 是否是第一个文件
 */
bool PlaylistManager::isFirst() const
{
    return m_currentIndex == 0;
}

/**
 * @brief 检查是否是最后一个文件
 *
 * @return bool 是否是最后一个文件
 */
bool PlaylistManager::isLast() const
{
    return m_currentIndex == m_playlist.size() - 1;
}

/**
 * @brief 获取当前播放列表模式
 *
 * @return AuroraPlayer::PlaylistMode 播放列表模式
 */
AuroraPlayer::State::PlaylistMode PlaylistManager::playlistMode() const
{
    return m_playlistMode;
}

/**
 * @brief 设置播放列表模式
 *
 * @param mode 播放列表模式
 */
void PlaylistManager::setPlaylistMode(AuroraPlayer::State::PlaylistMode mode)
{
    m_playlistMode = mode;
}
