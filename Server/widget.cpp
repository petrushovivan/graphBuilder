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

    bool serverOk = tcpServer->listen(QHostAddress::Any, tcpPort);
    bool udpOk = udpSocket->bind(udpPort);

    if(!udpOk&&serverOk){
        QMessageBox::information(this, "Внимание!", "Сервер не работает!");
    }
    //connect(tcpServer, &QTcpServer::newConnection, this, &Widget::clientNewConnection);

    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::udpSocketReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    painter = new QPainter(this);
    painter->translate(width()/2, height()/2);
    drawCoordinateSystem();
}

void Widget::drawCoordinateSystem()
{
    drawGrid();

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawLine(-width()/2, 0, width()/2, 0);
    painter->drawLine(0, -height()/2, 0, height()/2);
}

void Widget::drawGrid() {
    painter->setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

    const int gridStep = 50;
    int w = width();
    int h = height();

    for (int x = -w; x <= w; x += gridStep) {
        painter->drawLine(x, -h, x, h);
    }

    for (int y = -h; y <= h; y += gridStep) {
        painter->drawLine(-w, y, w, y);
    }
}

