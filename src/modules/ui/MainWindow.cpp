/********************************************************************************
 * @file   : MainWindow.cpp
 * @brief  : 实现了 MainWindow 类。
 *
 * 该文件实现了程序的主窗口，负责创建主窗口的 UI，处理主窗口的信号和槽。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "Simple-Media-Player/modules/ui/MainWindow.h"
#include "Simple-Media-Player/modules/player/PlayerController.h"
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDir>

#include <QVideoWidget>

/**
 * @brief MainWindow 的构造函数。
 *
 * @param parent  父窗口。
 *
 * 该函数是 MainWindow 的构造函数，负责创建主窗口的 UI，处理主窗口的信号和槽。
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , playerController(new PlayerController(this))
{
    setupUI();
    setupConnections();
    setWindowTitle(tr("Simple-Media-Player"));
    resize(800, 600);
}

/**
 * @brief MainWindow 的析构函数。
 *
 * 该函数是 MainWindow 的析构函数，负责销毁 MainWindow 对象。
 */
MainWindow::~MainWindow()
{
    // 释放播放器控制器
}

/**
 * @brief 设置 UI。
 *
 * 该函数负责创建 UI，并设置 UI 的布局。
 */
void MainWindow::setupUI()
{
    // --- Central widget --- //
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // --- Video widget --- //
    videoWidget = new QVideoWidget(this);
    playerController->setVideoOutput(videoWidget);

    // --- Control buttons --- //
    openButton = new QPushButton(tr("Open"), this);
    playButton = new QPushButton(tr("Play/Pause"), this);
    stopButton = new QPushButton(tr("Stop"), this);

    // --- Sliders --- //
    seekSlider = new QSlider(Qt::Horizontal, this);
    seekSlider->setRange(0, 0);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    // --- Time label --- //
    timeLabel = new QLabel(tr("00:00 / 00:00"), this);

    // --- Layouts --- //
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* controlLayout = new QHBoxLayout;
    QHBoxLayout* sliderLayout = new QHBoxLayout;

    // --- Assemble layouts --- //
    mainLayout->addWidget(videoWidget);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(controlLayout);

    sliderLayout->addWidget(seekSlider);
    sliderLayout->addWidget(timeLabel);

    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(volumeSlider);

    centralWidget->setLayout(mainLayout);

    // --- Create menu bar --- //
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addSeparator();
    QAction* quitAction = fileMenu->addAction(tr("&Quit"));
    quitAction->setShortcut(QKeySequence::Quit);

    // --- Create toolbar --- //
    QToolBar* toolbar = addToolBar(tr("Playback"));
    toolbar->addAction(openAction);
    toolbar->addWidget(playButton);
    toolbar->addWidget(stopButton);

    // --- Connect menu actions --- //
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
}

/**
 * @brief 设置连接。
 *
 * 该函数负责设置各个控件之间的连接。
 */
void MainWindow::setupConnections()
{
    // --- Button connections --- //
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playConvert);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stop);

    // --- Slider connections --- //
    connect(seekSlider, &QSlider::sliderMoved, this, &MainWindow::seek);
    connect(volumeSlider, &QSlider::valueChanged, playerController, &PlayerController::setVolume);

    // --- Player connections --- //
    connect(playerController, &PlayerController::durationChanged, this, &MainWindow::durationChanged);
    connect(playerController, &PlayerController::positionChanged, this, &MainWindow::positionChanged);
}

/**
 * @brief 打开文件。
 *
 * 该函数负责打开文件，并设置媒体。
 */
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Media File"), QDir::homePath());
    if (!fileName.isEmpty()) {
        playerController->setMedia(fileName);
        playButton->setText(tr("Play"));
    }
}

/**
 * @brief 播放/暂停。
 *
 * 该函数负责播放/暂停媒体。
 */
void MainWindow::playConvert()
{
    if (playerController->isPlaying()) {
        playerController->pause();
        playButton->setText(tr("Play"));
    } else {
        playerController->play();
        playButton->setText(tr("Pause"));
    }
}

/**
 * @brief 停止播放。
 *
 * 该函数负责停止播放媒体。
 */
void MainWindow::stop()
{
    playerController->stop();
    playButton->setText(tr("Play"));
}

/**
 * @brief 跳转到指定位置。
 *
 * @param position  播放位置。
 */
void MainWindow::seek(qint64 position)
{
    playerController->setPosition(position);
}

/**
 * @brief 媒体时长改变。
 *
 * @param duration  媒体时长。
 */
void MainWindow::durationChanged(qint64 duration)
{
    seekSlider->setRange(0, duration);
}

/**
 * @brief 播放位置改变。
 *
 * @param position  播放位置。
 */
void MainWindow::positionChanged(qint64 position)
{
    if (!seekSlider->isSliderDown()) {
        seekSlider->setValue(position);
    }

    // 更新时间标签
    qint64 duration = playerController->duration();
    QTime currentTime(0, 0);
    currentTime = currentTime.addMSecs(position);
    QTime totalTime(0, 0);
    totalTime = totalTime.addMSecs(duration);
    timeLabel->setText(currentTime.toString("mm:ss") + " / " + totalTime.toString("mm:ss"));
}