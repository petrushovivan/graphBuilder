#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMessageBox>
#include <QPOintF>
#include <QVector>
#include <QDebug>
#include <math.h>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTimer>
#include <QNetworkDatagram>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonSend_clicked();

    void calculatePoints(int left, int right);

    void discovery();

    void udpSocketReadyRead();

    void disconectedFromServer();

private:
    QByteArray preparePoints();

    QVector<QPointF> points;

    ushort udpPort;
    QUdpSocket *udpSocket;
    QTimer *timer;

    ushort tcpPort;
    QTcpSocket *tcpSocket;

    Ui::Widget *ui;
};
#endif // WIDGET_H
