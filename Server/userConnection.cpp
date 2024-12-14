#include "widget.h"
#include "ui_widget.h"

void Widget::udpSocketReadyRead(){
    while(udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        qDebug() << "Pong" << datagram.senderAddress();
        QByteArray response("Pong");
        udpSocket->writeDatagram(datagram.makeReply(response));
    }
}
