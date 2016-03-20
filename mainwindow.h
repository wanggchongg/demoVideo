#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include "externvar.h"
#include "decode_func.h"
#include "display_func.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void begin();
    void SDL_init();

signals:
    void frameReady();
    void gibertNumChanged();


private slots:
    void recv_real_videodata();
    void loseNumChange(int);
    void loseNum1Change(int);
    void decodeRateChanged(float);

private:
    Ui::MainWindow *ui;
    QUdpSocket *videoSocket;
    DecodeThread *decodeThread;
    ShowThread *showThread;
};

#endif // MAINWINDOW_H
