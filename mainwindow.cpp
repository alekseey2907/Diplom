#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);

    if (!udpSocket->bind(QHostAddress::Any, 12345)) {
        qDebug() << "Failed to bind UDP socket";
        return;
    }
    connect(ui->lineEdit_send, &QLineEdit::returnPressed, this, &MainWindow::on_PB_send_clicked);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram_read;
        datagram_read.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram_read.data(), datagram_read.size(), &sender, &senderPort);

        qDebug() << "Received datagram from" << sender.toString() << ":" << senderPort;
        qDebug() << "Data:" << datagram_read;
        ui->textBrowser_read->append(datagram_read);
    }
}

void MainWindow::on_PB_send_clicked()
{
       QByteArray datagram_send = ui->lineEdit_send->text().toUtf8();
       udpSocket->writeDatagram(datagram_send, receiverAddress, senderPort_send);
       if(udpSocket)
       {
           qDebug("good");
       }

}

