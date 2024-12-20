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

    coordinates.clear();

    tcpServer = new QTcpServer(this);

    bool serverOk = tcpServer->listen(QHostAddress::Any, tcpPort);
    bool udpOk = udpSocket->bind(udpPort);

    if(!udpOk&&serverOk){
        QMessageBox::information(this, "Внимание!", "Сервер не работает!");
    }
    connect(tcpServer, &QTcpServer::newConnection, this, &Widget::clientNewConnection);

    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::udpSocketReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::clientNewConnection(){
    while(tcpServer->hasPendingConnections()){
        QTcpSocket *client = tcpServer->nextPendingConnection();
        connect(client, &QTcpSocket::readyRead, this, &Widget::clientReadyRead);
        connect(client, &QTcpSocket::disconnected, this, &Widget::clientDisconnected);

        clients << client;
    }
}

void Widget::clientDisconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    int index = clients.indexOf(client);
    if(index >= 0) {
        clients.removeAt(index);
    }
}

void Widget::clientReadyRead()
{
    QByteArray data;
    QTcpSocket *client = (QTcpSocket*)sender();

    readMessage.append(client->readAll());

    while ((uint32_t)readMessage.size() >= sizeof(unsigned long)) {

        unsigned long dataSize = 0;
        memcpy(&dataSize, readMessage.constData(), sizeof(unsigned long));

        if ((uint32_t)readMessage.size() < sizeof(unsigned long) + dataSize)
            return;

        data = readMessage.mid(sizeof(unsigned long), dataSize);
        readMessage.remove(0, sizeof(unsigned long) + dataSize);

        QStringList usersCoordinate = QString::fromUtf8(data).split(" ");

        coordinates = usersCoordinate;
        update();
    }
}

void Widget::drawGraphic(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine));

    for (const QVector<QPointF>& points : userPoints) {
        QPointF prevPoint;
        bool firstPoint = true;

        for (QPointF& point : points) {
            QPointF shiftedPoint = point + offset;
            if (!firstPoint) {
                painter->drawLine(prevPoint, shiftedPoint);
            }
            firstPoint = false;

            prevPoint = shiftedPoint;
        }
    }

    QVector<QPointF> points;

    QPointF prevPoint;
    bool firstPoint = true;
    for (int i = 1; i<coordinates.length(); i++) {
        double x = coordinates[i-1].toDouble();
        double y = - coordinates[i].toDouble();

        QPointF point(x, y);
        points.append(point);

        point+=offset;

        if (!firstPoint) {
            painter->drawLine(prevPoint, point);
        }
        firstPoint = false;

        prevPoint = point;
        i++;
    }
    userPoints.append(points);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.translate(width() / 2, height() / 2);

    drawCoordinateSystem(&p);
    drawGraphic(&p);
    p.end();
}

