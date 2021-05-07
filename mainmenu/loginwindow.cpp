#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "game/gamewidget.h"
#include <QTimer>
#include <QPainter>
LoginWindow::LoginWindow(QString JWT,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->JWT = JWT;

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    emit this->loginwindowback();
}

void LoginWindow::on_BeginGameButton_clicked()
{
    gamewidget = new GameWidget();
    QTimer::singleShot(200,this ,[=]()
    {
        this->hide();
        gamewidget->show();
    });
    //TODO  返回
    connect(gamewidget,&GameWidget::GameBack,[=](){
        //选择隐藏
        delete gamewidget;
        //自身显示
        this->show();
    });
}

void LoginWindow::paintEvent(QPaintEvent *)
{
    QPixmap pix;            //创建一个对象
    QPainter painter(this);    //画家 在this上画画
    painter.drawPixmap(0,0,this->width(),this->height(),pix) ;
    pix.load(backgroud);
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix) ;

}
