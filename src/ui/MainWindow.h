/********************************************************************************
 * @file   : MainWindow.h
 * @brief  : 声明了 MainWindow 类。
 *
 * 该文件声明了 MainWindow 类，负责创建主窗口的 UI，处理主窗口的信号和槽。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

// 前向声明
class QWidget;
class QPushButton;
class QSlider;
class QLabel;
class QListWidget;
class QVideoWidget;
class PlayerController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化主窗口及其UI组件。
     *
     * @param parent 父窗口指针，默认为 nullptr。
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * @brief 析构函数，释放资源。
     */
    ~MainWindow();

private slots:
    /**
     * @brief 打开文件对话框以选择媒体文件。
     *
     * 通过 QFileDialog 选择一个媒体文件，并将其路径传递给播放控制器。
     */
    void openFile();

    /**
     * @brief 切换播放/暂停状态。
     */
    void togglePlayPause();

    /**
     * @brief 停止播放。
     */
    void stop();

    /**
     * @brief 设置播放位置。
     *
     * @param position  播放位置（毫秒）
     */
    void setPosition(int position);

    /**
     * @brief 设置音量。
     *
     * @param volume  音量（0-100）
     */
    void setVolume(int volume);

    /**
     * @brief 更新播放时间显示。
     *
     * @param position  播放位置（毫秒）
     */
    void updateTimeDisplay(qint64 position);

    /**
     * @brief 更新播放器时长。
     *
     * @param duration  媒体时长（毫秒）
     */
    void updateDuration(qint64 duration);

    /**
     * @brief 播放下一个媒体文件
     */
    void nextMedia();

    /**
     * @brief 播放上一个媒体文件
     */
    void previousMedia();

    /**
     * @brief 处理播放列表变化
     */
    void onPlaylistChanged();

    /**
     * @brief 处理播放列表项双击事件
     *
     * @param item 被双击的项
     */
    void onPlaylistItemDoubleClicked(QListWidgetItem* item);

private:
    /**
     * @brief 初始化UI组件。
     */
    void setupUI();

    /**
     * @brief 建立信号和槽的连接。
     */
    void setupConnections();

    /**
     * @brief 格式化时间显示。
     *
     * @param duration  时间（毫秒）
     * @return QString  格式化后的时间字符串（mm:ss）
     */
    QString formatTime(qint64 duration) const;

private:
    QWidget*      centralWidget;   ///< 中心部件
    QVideoWidget* videoWidget;     ///< 视频显示部件
    QPushButton*  openButton;      ///< 打开文件按钮
    QPushButton*  playButton;      ///< 播放/暂停按钮
    QPushButton*  stopButton;      ///< 停止按钮
    QPushButton*  nextButton;      ///< 下一个按钮
    QPushButton*  previousButton;  ///< 上一个按钮
    QSlider*      seekSlider;      ///< 播放进度滑块
    QSlider*      volumeSlider;    ///< 音量控制滑块
    QLabel*       timeLabel;       ///< 时间显示标签
    QListWidget*  playlistWidget;  ///< 播放列表控件

    PlayerController* playerController;  ///< 播放控制器
};

#endif // MAINWINDOW_H