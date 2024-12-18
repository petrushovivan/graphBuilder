#include "widget.h"
#include "ui_widget.h"

void Widget::udpSocketReadyRead(){
    while(udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray response("Pong");
        udpSocket->writeDatagram(datagram.makeReply(response));
    }
}
