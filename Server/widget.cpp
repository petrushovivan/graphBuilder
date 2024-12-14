#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    tcpPort = 40000;
    udpPort = 40001;

    tcpServer = new QTcpServer(this);

    bool serverOk = server->listen(QHostAddress::Any, tcpPort);

    bool udpOk = udpSocket->bind(udpPort);
    if(!udpOk&&serverOk){
        QMessageBox::information(this, "Внимание!", "Сервер не работает!");
    }
}

Widget::~Widget()
{
    delete ui;
}

