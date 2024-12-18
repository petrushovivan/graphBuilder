#include "widget.h"
#include "ui_widget.h"

void Widget::disconectedFromServer(){
    ui->frameConnected->setStyleSheet("background-color: red;");
    timer->start(500);
    discovery();
    ui->pushButtonSend->setEnabled(false);
}
