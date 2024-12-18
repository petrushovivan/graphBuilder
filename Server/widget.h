#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QPainter>

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
protected:
    void paintEvent(QPaintEvent *) override;

private:
    void drawCoordinateSystem();
    void drawGrid();


    QPainter *painter;

    ushort udpPort;
    ushort tcpPort;

    QUdpSocket *udpSocket;

    // TCP-сервер. Позволяет принимать входящие соединения.
    QTcpServer *tcpServer;

    Ui::Widget *ui;
};
#endif // WIDGET_H
