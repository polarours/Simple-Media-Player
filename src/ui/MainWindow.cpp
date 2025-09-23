/********************************************************************************
 * @file   : MainWindow.cpp
 * @brief  : 实现了 MainWindow 类。
 *
 * 该文件实现了程序的主窗口，负责创建主窗口的 UI，处理主窗口的信号和槽。
 *
 * @author : polarours
 * @date   : 2025/08/29
 ********************************************************************************/

#include "MainWindow.h"
#include "../player/PlayerController.h"
#include "../player/PlaylistManager.h"
#include "CommonUtils.h"

#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include <QVideoWidget>

/**
 * @brief MainWindow 的构造函数。
 *
 * @param parent  父窗口。
 *
 * 该函数是 MainWindow 的构造函数，负责创建主窗口的 UI，处理主窗口的信号和槽。
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , playerController(new PlayerController(this))
{
    setupUI();
    setupConnections();
    setWindowTitle(tr("AuroraPlayer"));
    resize(800, 600);
}

/**
 * @brief MainWindow 的析构函数。
 *
 * 该函数是 MainWindow 的析构函数，负责销毁 MainWindow 对象。
 */
MainWindow::~MainWindow()
{
    // TODO: 释放播放器控制器
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
    connect(playButton, &QPushButton::clicked, this, &MainWindow::togglePlayPause);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextMedia);
    connect(previousButton, &QPushButton::clicked, this, &MainWindow::previousMedia);

    // --- Slider connections --- //
    connect(seekSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::setVolume);

    // --- Player connections --- //
    connect(playerController, &PlayerController::durationChanged, this, &MainWindow::updateDuration);
    connect(playerController, &PlayerController::positionChanged, this, &MainWindow::updateTimeDisplay);
    
    // --- Playlist connections --- //
    connect(playerController, &PlayerController::playlistChanged, this, &MainWindow::onPlaylistChanged);
    connect(playlistWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onPlaylistItemDoubleClicked);
}

/**
 * @brief 打开文件。
 *
 * 该函数负责打开文件，并设置媒体。
 */
/**
 * @brief 打开文件对话框以选择媒体文件。
 *
 * 通过 QFileDialog 选择一个或多个媒体文件，并将其路径传递给播放控制器。
 */
void MainWindow::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
        this,
        tr("Open Media Files"),
        QDir::homePath(),
        tr("Media Files (*.mp3 *.mp4 *.avi *.mkv *.wav *.flv *.mov *.wmv)"));
    
    if (!fileNames.isEmpty()) {
        // 添加到播放列表
        playerController->playlistManager()->addFiles(fileNames);
        
        // 如果是第一次添加文件，自动播放第一个
        if (playerController->playlistManager()->count() == fileNames.size()) {
            playerController->play();
            playButton->setText(tr("Pause"));
        }
    }
}

/**
 * @brief 切换播放/暂停状态。
 */
void MainWindow::togglePlayPause()
{
    if (playerController->playlistManager()->count() == 0) {
        // 如果播放列表为空，先打开文件
        openFile();
        return;
    }
    
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
 */
void MainWindow::stop()
{
    playerController->stop();
    playButton->setText(tr("Play"));
}

/**
 * @brief 设置播放位置。
 *
 * @param position  播放位置（毫秒）
 */
void MainWindow::setPosition(int position)
{
    playerController->setPosition(position);
}

/**
 * @brief 设置音量。
 *
 * @param volume  音量（0-100）
 */
void MainWindow::setVolume(int volume)
{
    playerController->setVolume(volume);
}

/**
 * @brief 更新播放时间显示。
 *
 * @param position  播放位置（毫秒）
 */
void MainWindow::updateTimeDisplay(qint64 position)
{
    qint64 duration = playerController->duration();
    timeLabel->setText(formatTime(position) + " / " + formatTime(duration));
    seekSlider->setValue(static_cast<int>(position));
}

/**
 * @brief 更新播放器时长。
 *
 * @param duration  媒体时长（毫秒）
 */
void MainWindow::updateDuration(qint64 duration)
{
    seekSlider->setRange(0, static_cast<int>(duration));
    seekSlider->setEnabled(duration > 0);
    timeLabel->setText("00:00 / " + formatTime(duration));
}

/**
 * @brief 播放下一个媒体文件
 */
void MainWindow::nextMedia()
{
    playerController->nextMedia();
}

/**
 * @brief 播放上一个媒体文件
 */
void MainWindow::previousMedia()
{
    playerController->previousMedia();
}

/**
 * @brief 处理播放列表变化
 */
void MainWindow::onPlaylistChanged()
{
    playlistWidget->clear();
    PlaylistManager* playlistManager = playerController->playlistManager();
    
    for (int i = 0; i < playlistManager->count(); ++i) {
        QString filePath = playlistManager->filePathAt(i);
        QFileInfo fileInfo(filePath);
        QListWidgetItem* item = new QListWidgetItem(fileInfo.fileName());
        item->setToolTip(filePath);
        playlistWidget->addItem(item);
    }
}

/**
 * @brief 处理播放列表项双击事件
 *
 * @param item 被双击的项
 */
void MainWindow::onPlaylistItemDoubleClicked(QListWidgetItem* item)
{
    int index = playlistWidget->row(item);
    playerController->playlistManager()->setCurrentIndex(index);
    playerController->play();
    playButton->setText(tr("Pause"));
}

/**
 * @brief 格式化时间显示。
 *
 * @param duration  时间（毫秒）
 * @return QString  格式化后的时间字符串（mm:ss）
 */
QString MainWindow::formatTime(qint64 duration) const
{
    return AuroraPlayer::Utils::formatTime(duration);
}

void MainWindow::setupUI()
{
    // 设置主窗口样式
    setStyleSheet(R"(
        QMainWindow {
            background-color: #2E2E2E;
        }
        
        QMenuBar {
            background-color: #3A3A3A;
            color: white;
        }
        
        QMenuBar::item {
            background: transparent;
        }
        
        QMenuBar::item:selected {
            background: #5A5A5A;
        }
        
        QMenu {
            background-color: #3A3A3A;
            color: white;
        }
        
        QMenu::item:selected {
            background-color: #5A5A5A;
        }
        
        QPushButton {
            background-color: #4A4A4A;
            color: white;
            border: 1px solid #6A6A6A;
            padding: 5px;
            border-radius: 4px;
            min-width: 70px;
        }
        
        QPushButton:hover {
            background-color: #5A5A5A;
        }
        
        QPushButton:pressed {
            background-color: #3A3A3A;
        }
        
        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 8px;
            background: #4A4A4A;
            margin: 2px 0;
            border-radius: 4px;
        }
        
        QSlider::handle:horizontal {
            background: #87CEFA;
            border: 1px solid #5c5c5c;
            width: 18px;
            margin: -5px 0;
            border-radius: 9px;
        }
        
        QSlider::sub-page:horizontal {
            background: #6A6A6A;
            border-radius: 4px;
        }
        
        QLabel {
            color: #E0E0E0;
        }
        
        QListWidget {
            background-color: #3A3A3A;
            color: white;
            border: 1px solid #5A5A5A;
            alternate-background-color: #4A4A4A;
        }
        
        QListWidget::item {
            padding: 4px;
        }
        
        QListWidget::item:selected {
            background-color: #87CEFA;
            color: black;
        }
        
        QStatusBar {
            background-color: #3A3A3A;
            color: white;
        }
        
        QToolBar {
            background-color: #3A3A3A;
            border: none;
        }
    )");

    // --- Central widget --- //
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // --- Video widget --- //
    videoWidget = new QVideoWidget(this);
    videoWidget->setStyleSheet("background-color: black;");
    playerController->setVideoOutput(videoWidget);

    // --- Control buttons --- //
    openButton = new QPushButton(tr("Open"), this);
    openButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    playButton = new QPushButton(tr("Play"), this);
    playButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    stopButton = new QPushButton(tr("Stop"), this);
    stopButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nextButton = new QPushButton(tr("Next"), this);
    nextButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    previousButton = new QPushButton(tr("Previous"), this);
    previousButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // --- Sliders --- //
    seekSlider = new QSlider(Qt::Horizontal, this);
    seekSlider->setRange(0, 0);
    seekSlider->setEnabled(false);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    // --- Labels --- //
    timeLabel = new QLabel(tr("00:00 / 00:00"), this);
    timeLabel->setMinimumSize(120, 0);
    timeLabel->setAlignment(Qt::AlignCenter);
    
    QLabel* volumeLabel = new QLabel(tr("Volume"), this);
    QLabel* playlistLabel = new QLabel(tr("Playlist"), this);

    // --- Playlist widget --- //
    playlistWidget = new QListWidget(this);

    // --- Layouts --- //
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* sliderLayout = new QHBoxLayout;
    QHBoxLayout* controlLayout = new QHBoxLayout;

    // --- Assemble layouts --- //
    mainLayout->addWidget(videoWidget, 3);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(playlistLabel);
    mainLayout->addWidget(playlistWidget, 1);

    sliderLayout->addWidget(seekSlider);
    sliderLayout->addWidget(timeLabel);

    controlLayout->addWidget(openButton);
    controlLayout->addWidget(previousButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(nextButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(volumeSlider);
    controlLayout->addWidget(volumeLabel);

    centralWidget->setLayout(mainLayout);

    // --- Create menu bar --- //
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    // --- Create toolbar --- //
    QToolBar* toolbar = addToolBar(tr("Playback"));
    toolbar->addAction(openAction);
    toolbar->addWidget(previousButton);
    toolbar->addWidget(playButton);
    toolbar->addWidget(nextButton);
    toolbar->addWidget(stopButton);

    // --- Create status bar --- //
    statusBar()->showMessage(tr("Ready"));
    
    // 设置窗口大小
    resize(1000, 700);
}