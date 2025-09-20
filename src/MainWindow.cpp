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
#include "PlayerController.h"
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDir>

#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , playerController(new PlayerController(this))
{
    setupUI();
    setupConnections();
    setWindowTitle(tr("Simple-Media-Player"));
    resize(800, 600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI()
{
    // Central widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Video widget
    videoWidget = new QVideoWidget(this);
    playerController->setVideoOutput(videoWidget);

    // Control buttons
    openButton = new QPushButton(tr("Open"), this);
    playButton = new QPushButton(tr("Play"), this);
    stopButton = new QPushButton(tr("Stop"), this);

    // Sliders
    seekSlider = new QSlider(Qt::Horizontal, this);
    seekSlider->setRange(0, 0);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    // Time label
    timeLabel = new QLabel(tr("00:00 / 00:00"), this);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *controlLayout = new QHBoxLayout;
    QHBoxLayout *sliderLayout = new QHBoxLayout;

    // Assemble layouts
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

    // Create menu bar
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addSeparator();
    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    quitAction->setShortcut(QKeySequence::Quit);

    // Create toolbar
    QToolBar *toolbar = addToolBar(tr("Playback"));
    toolbar->addAction(openAction);
    toolbar->addWidget(playButton);
    toolbar->addWidget(stopButton);

    // Connect menu actions
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::setupConnections()
{
    // Button connections
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playPause);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stop);

    // Slider connections
    connect(seekSlider, &QSlider::sliderMoved, this, &MainWindow::seek);
    connect(volumeSlider, &QSlider::valueChanged, playerController, &PlayerController::setVolume);

    // Player connections
    connect(playerController, &PlayerController::durationChanged, this, &MainWindow::durationChanged);
    connect(playerController, &PlayerController::positionChanged, this, &MainWindow::positionChanged);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Media File"), QDir::homePath());
    if (!fileName.isEmpty()) {
        playerController->setMedia(fileName);
        playButton->setText(tr("Play"));
    }
}

void MainWindow::playPause()
{
    if (playerController->isPlaying()) {
        playerController->pause();
        playButton->setText(tr("Play"));
    } else {
        playerController->play();
        playButton->setText(tr("Pause"));
    }
}

void MainWindow::stop()
{
    playerController->stop();
    playButton->setText(tr("Play"));
}

void MainWindow::seek(int position)
{
    playerController->setPosition(position);
}

void MainWindow::durationChanged(qint64 duration)
{
    seekSlider->setRange(0, duration);
}

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