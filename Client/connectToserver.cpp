#include "widget.h"
#include "ui_widget.h"

void Widget::discovery() {
    QByteArray request("Ping");
    udpSocket->writeDatagram(request, QHostAddress::Broadcast, udpPort);
}

void Widget::udpSocketReadyRead() {
    timer->stop();
    QNetworkDatagram datagram = udpSocket->receiveDatagram();
    tcpSocket->connectToHost(datagram.senderAddress(), tcpPort);

    bool connected = tcpSocket->waitForConnected(10000);
    ui->pushButtonSend->setEnabled(connected);
    if(!connected) {
        ui->frameConnected->setStyleSheet("background-color: red;");
        tcpSocket->disconnectFromHost();
    }
    else{
        ui->frameConnected->setStyleSheet("background-color: green;");
    }
}
