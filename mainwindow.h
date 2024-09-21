#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QDebug>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    quint16 senderPort_send = 12345;
    QHostAddress receiverAddress;// ("127.0.0.1");
private slots:
    void readPendingDatagrams();
    void on_PB_send_clicked();
};
#endif // MAINWINDOW_H
