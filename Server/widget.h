#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QPainter>
#include <QByteArray>
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void udpSocketReadyRead();
    void clientNewConnection();
    void clientDisconnected();
    void clientReadyRead();
protected:
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event);

private:
    void drawCoordinateSystem(QPainter *painter);
    void drawGrid(QPainter *painter);
    void drawGraphic(QPainter *painter);

    QByteArray readMessage;

    QPoint lastMousePos;
    QPoint offset;

    ushort udpPort;
    ushort tcpPort;

    QUdpSocket *udpSocket;

    // TCP-сервер. Позволяет принимать входящие соединения.
    QTcpServer *tcpServer;
    QVector<QTcpSocket *> clients;
    QVector<QVector<QPointF>> userPoints;

    QStringList coordinates;

    Ui::Widget *ui;
};
#endif // WIDGET_H
