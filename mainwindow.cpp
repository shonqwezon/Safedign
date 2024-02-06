#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(this)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); 

    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue(QCoreApplication::applicationName(), QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    settings.sync();

    runIcon = QIcon(":/trayIcons/icons/run.png");
    stopIcon = QIcon(":/trayIcons/icons/stop.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(runIcon);
    trayIcon->setToolTip("Safedign settings");
    QMenu *menu = new QMenu(this);
    QAction *app = new QAction("Показать", this);
    QAction *quitApp = new QAction("Выйти", this);
    appG = app;
    QObject::connect(app, &QAction::triggered, this, [this, app](){
        if(!this->isVisible()) {
            app->setText("Скрыть");
            this->show();
        }
        else hideApp();
    });
    QObject::connect(quitApp, &QAction::triggered, this, &QApplication::quit);
    menu->addAction(app);
    menu->addAction(quitApp);
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    ui->slider->setRange(1, 99);
    ui->slider->setSingleStep(1);
    QObject::connect(ui->slider, &QSlider::valueChanged, this, [this](){
        ui->valueView->setText(QString::number(ui->slider->value())+"%");
        volumeOS.setMinVolume((double)ui->slider->value()/100.0);
    });

    volumeOS.changeVolume(false);

    socket.bind(QHostAddress::Any, 52856);
    QObject::connect(&socket, &QUdpSocket::readyRead, this, &MainWindow::onReadyRead);
    QObject::connect(new QShortcut(QKeySequence(Qt::Key_Escape), this), &QShortcut::activated, this, &MainWindow::hideApp);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead() {
    QByteArray buffer;
    buffer.resize(socket.pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket.readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    qDebug() << "message:" << buffer;

    if(QHostAddress(sender.toIPv4Address()) == QHostAddress("192.168.1.61")) {
            if(modeSound) {
                if(buffer == opened && buffer != currentValue) {
                    qDebug() << "opened";
                    volumeOS.changeVolume(true);
                    currentValue = buffer;
                    return;
                }
                if(buffer == closed && buffer != currentValue) {
                    qDebug() << "closed";
                    volumeOS.changeVolume(false);
                    currentValue = buffer;
                    return;
                }

            }
    }
}

void MainWindow::writePositionSettings()
{
       QSettings settings;
       settings.beginGroup("settings");
       settings.setValue("geometry", saveGeometry());
       settings.setValue("pos", pos());
       settings.setValue("value", ui->slider->value());
       settings.endGroup();

}

void MainWindow::readPositionSettings() {
    QSettings settings;
    settings.beginGroup("settings");
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    ui->valueView->setText(settings.value("value", 15).toString());
    ui->slider->setValue(settings.value("value", 15).toInt());
    volumeOS.setMinVolume((double)(settings.value("value", 15).toInt()/100.0));
    settings.endGroup();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch(reason) {
        case QSystemTrayIcon::Trigger:
            modeSound = !modeSound;
            modeSound ? trayIcon->setIcon(runIcon) : trayIcon->setIcon(stopIcon);
            break;
    default:
        break;
    }
}

void MainWindow::hideApp() {
    appG->setText("Показать");
    writePositionSettings();
    this->hide();
}
