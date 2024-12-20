#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushButtonSend->setEnabled(false);

    tcpPort = 40000;
    udpPort = 40001;

    ui->frameConnected->setStyleSheet("background-color: red;");

    udpSocket = new QUdpSocket(this);
    tcpSocket = new QTcpSocket(this);
    timer = new QTimer(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::udpSocketReadyRead);
    connect(timer, &QTimer::timeout, this, &Widget::discovery);

    connect(tcpSocket, &QTcpSocket::disconnected, this, &Widget::disconectedFromServer);
    discovery();
    timer->start(500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonSend_clicked()
{
    double leftVaue = ui->spinBoxLeftValue->value();
    double rightValue = ui->spinBoxRightValue->value();
    if(leftVaue>rightValue){
        QMessageBox::information(this, "Внимание!", "Введен неверный промежуток");
        return;
    }

    calculatePoints(leftVaue, rightValue);

    QByteArray pointsInByte = preparePoints();

    tcpSocket->write(pointsInByte);
}

void Widget::calculatePoints(int leftValue, int rightValue)
{
    points.clear();

    int power = ui->spinBoxPower->value();
    int coefficient = ui->spinBoxCoefficient->value();
    int freeMember = ui->spinBoxFreeMember->value();

    for(double i = leftValue; i<=rightValue; i+= 0.5){
        long long y = pow(i, power) + (coefficient * i) + freeMember;
        QPoint point((long long)i, y);
        qDebug()<<QString::number(i) +" " + QString::number(y);
        points.append(point);
    }
}

QByteArray Widget::preparePoints(){
    QString str;
    str.clear();
    for(QPointF p: points){
        str.append(QString::number(p.x()));
        str.append(" ");
        str.append(QString::number(p.y()));
        str.append(" ");
    }
    QByteArray buff = str.toUtf8();
    unsigned long size = buff.size();
    QByteArray message;
    message.append(reinterpret_cast<char*>(&size), sizeof(unsigned long));

    message.append(buff);
    return message;
}
