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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void playPause();
    void stop();
    void seek(int position);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private:
    void setupUI();
    void setupConnections();

    // UI 元素
    QWidget *centralWidget;
    QVideoWidget *videoWidget;
    QSlider *seekSlider;
    QSlider *volumeSlider;
    QPushButton *openButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    QLabel *timeLabel;

    PlayerController *playerController;
};

#endif // MAINWINDOW_H