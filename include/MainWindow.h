/********************************************************************************
 * @file   : MainWindow.h
 * @brief  : 定义了 MainWindow 类。
 *
 * 该文件定义了 MainWindow 类，负责管理主窗口的 UI 元素和交互逻辑。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

// 前向声明
class QVideoWidget;
class PlayerController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化主窗口及其UI组件。
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
     * @brief 播放/暂停媒体文件。
     *
     * 如果当前正在播放，则暂停播放；如果当前处于暂停状态，则继续播放。
     */
    void playPause();

    /**
     * @brief 停止媒体文件的播放。
     *
     * 停止媒体文件的播放，并将播放器状态重置为初始状态。
     */
    void stop();

    /**
     * @brief 跳转到指定位置。
     *
     * @param position 要跳转到的位置，以毫秒为单位。
     */
    void seek(int position);

    /**
     * @brief 媒体文件时长改变时的处理函数。
     *
     * @param duration  媒体文件的时长，以毫秒为单位。
     */
    void durationChanged(qint64 duration);

    /**
     * @brief 媒体文件位置改变时的处理函数。
     *
     * @param position  媒体文件当前位置，以毫秒为单位。
     */
    void positionChanged(qint64 position);

private:
    /**
     * @brief 初始化 UI 元素。
     *
     * 该函数负责创建和设置 UI 元素，包括视频播放控件、进度条、按钮等。
     */
    void setupUI();

    /**
     * @brief 设置信号与槽的连接。
     *
     * 该函数负责连接 UI 元素和播放器控制器的信号与槽。
     */
    void setupConnections();

    // --- UI 元素 --- //
    QWidget* centralWidget;    ///< 中心控件
    QVideoWidget* videoWidget; ///< 视频播放控件
    QSlider* seekSlider;       ///< 进度条
    QSlider* volumeSlider;     ///< 音量条
    QPushButton* openButton;   ///< 打开文件按钮
    QPushButton* playButton;   ///< 播放/暂停按钮
    QPushButton* stopButton;   ///< 停止按钮
    QLabel* timeLabel;         ///< 时间标签

    // --- 播放器控制器 --- //
    PlayerController* playerController;  ///< 播放器控制器
};

#endif // MAINWINDOW_H