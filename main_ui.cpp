#include "main_ui.h"
#include "./ui_main_ui.h"
#include <QSplitter>
#include <QMenu>
#include <QAction>
#include <QPushButton>

MainUI::MainUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);

    // 设备按钮
    auto *deviceMenu = new QMenu();
    auto *deviceAction1 = new QAction("未检测到设备");
    connect(deviceAction1, &QAction::triggered, this, [deviceAction1, this]{on_deviceMenuUpdate("未检测到设备");});
    deviceMenu->addAction(deviceAction1);
    auto *deviceAction2 = new QAction("测试上位机");
    connect(deviceAction2, &QAction::triggered, this, [deviceAction2, this]{on_deviceMenuUpdate("测试上位机");});
    deviceMenu->addAction(deviceAction2);
    ui->deviceButton->setMenu(deviceMenu);

    // 功能按钮
    auto *modeMenu = new QMenu();
    auto *modeAction1 = new QAction("不做调整");
    connect(modeAction1, &QAction::triggered, this, [modeAction1, this]{on_modeMenuUpdate("不做调整");});
    modeMenu->addAction(modeAction1);
    auto *modeAction2 = new QAction("女低音类型");
    connect(modeAction2, &QAction::triggered, this, [modeAction2, this]{on_modeMenuUpdate("女低音类型");});
    modeMenu->addAction(modeAction2);
    auto *modeAction3 = new QAction("女高音类型");
    connect(modeAction3, &QAction::triggered, this, [modeAction3, this]{on_modeMenuUpdate("女高音类型");});
    modeMenu->addAction(modeAction3);
    auto *modeAction4 = new QAction("男低音类型");
    connect(modeAction4, &QAction::triggered, this, [modeAction4, this]{on_modeMenuUpdate("男低音类型");});
    modeMenu->addAction(modeAction4);
    auto *modeAction5 = new QAction("男高音类型");
    connect(modeAction5, &QAction::triggered, this, [modeAction5, this]{on_modeMenuUpdate("男高音类型");});
    modeMenu->addAction(modeAction5);
    ui->modeButton->setMenu(modeMenu);

    // 录制按钮
    ui->startButton->setEnabled(true);
    ui->startButton->setText("开始");
    ui->pauseButton->setEnabled(false);
    ui->endButton->setEnabled(false);

    // 频谱图
    QVector<double> x(101), y(101);
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->inputView->addGraph();
    ui->inputView->graph(0)->setData(x, y);
    // set axes ranges, so we see all data:
    ui->inputView->xAxis->setRange(-1, 1);
    ui->inputView->yAxis->setRange(0, 1);
    ui->inputView->replot();
}


MainUI::~MainUI()
{
    delete ui;
}


auto MainUI::on_deviceButton_clicked() -> void
{
    ui->deviceButton->setChecked(false);
}


auto MainUI::on_deviceMenuUpdate(const QString name) -> void
{
    ui->deviceButton->setText(name);
    ui->deviceButton->setChecked(false);
}


auto MainUI::on_modeButton_clicked(bool checked) -> void
{
    ui->modeButton->setChecked(false);
}


auto MainUI::on_modeMenuUpdate(const QString name) -> void
{
    ui->modeButton->setText(name);
    ui->modeButton->setChecked(false);
}


auto MainUI::on_startButton_clicked() -> void
{
    ui->startButton->setEnabled(false);
    ui->startButton->setText("开始");
    ui->pauseButton->setEnabled(true);
    ui->endButton->setEnabled(true);
    ui->playButton->setEnabled(false);

    recorder.start();
}


auto MainUI::on_pauseButton_clicked() -> void
{
    ui->startButton->setEnabled(true);
    ui->startButton->setText("继续");
    ui->pauseButton->setEnabled(false);
    ui->endButton->setEnabled(true);
    ui->playButton->setEnabled(false);

    recorder.pause();
}


auto MainUI::on_endButton_clicked() -> void
{
    ui->startButton->setEnabled(true);
    ui->startButton->setText("开始");
    ui->pauseButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->playButton->setEnabled(true);

    recorder.end();
}


auto MainUI::on_playButton_clicked() -> void
{
    // player.play();
}

