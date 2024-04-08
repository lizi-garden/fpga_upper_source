#ifndef MAINUI_H
#define MAINUI_H

#include "recorder.h"
#include "player.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainUI; }
QT_END_NAMESPACE

class MainUI : public QWidget
{
    Q_OBJECT

public:
    MainUI(QWidget *parent = nullptr);
    ~MainUI();

private:
    Ui::MainUI *ui;

    Recorder recorder;
    Player player;

private slots:
    auto on_deviceButton_clicked() -> void;
    auto on_deviceMenuUpdate(const QString name) -> void;

    auto on_modeButton_clicked(bool checked) -> void;
    auto on_modeMenuUpdate(const QString name) -> void;

    auto on_startButton_clicked() -> void;
    auto on_pauseButton_clicked() -> void;
    auto on_endButton_clicked() -> void;


    void on_playButton_clicked();
};
#endif // MAINUI_H
