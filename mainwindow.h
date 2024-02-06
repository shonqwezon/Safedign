#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "volumeos.h"
#include <Windows.h>
#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QSettings>
#include <QShortcut>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readPositionSettings();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void onReadyRead();
    void writePositionSettings();
    void hideApp();


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    VolumeOS volumeOS;
    QUdpSocket socket;
    QByteArray data;
    QChar closed = '0';
    QChar opened = '1';
    QIcon runIcon;
    QIcon stopIcon;
    QAction *appG;
    QByteArray currentValue = "-1";
    bool modeSound = true;
};
#endif // MAINWINDOW_H
