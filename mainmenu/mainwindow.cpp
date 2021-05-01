#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariantMap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->setWindowIcon(QPixmap(Logo));        //logo
}

MainWindow::~MainWindow()
{
    delete ui;
}

//背景
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap pix;            //创建一个对象
    QPainter painter(this);    //画家 在this上画画
    painter.drawPixmap(0,0,this->width(),this->height(),pix) ;
    pix.load(Logo);
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap((this->width()-pix.width())/2,0,pix) ;
}

//LogInButton
void MainWindow::on_LogInButton_clicked()
{
    QString Id = this->ui->IdLineEdit->text();
    QString Password = this->ui->PasswordLineEdit->text();

    QVariantMap map{{"username",Id},{"password",Password}};
    QNetworkRequest req(QUrl("http://192.168.137.1:3000/api/signin"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(req,QJsonDocument(QJsonObject::fromVariantMap(map)).toJson());

    connect(manager,&QNetworkAccessManager::finished,[](QNetworkReply *reply){
        QByteArray raw =  reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(raw);

        qDebug()<<json["success"].toBool();
        qDebug()<<json["token"].toString();
    });

    bool LogInRes = true;
    if(LogInRes == true){
        this->hide();
        loginwindow = new LoginWindow;
        loginwindow->show();

        connect(loginwindow,&LoginWindow::loginwindowback,[=](){

            delete loginwindow;
            this->show();
        });
    }
    else{
        QMessageBox::critical(this,"错误","账号密码错误","重新输入");
    }

}



void MainWindow::on_RegisterButton_clicked()
{
    this->hide();
    registerwindow = new Register;
    connect(registerwindow,&Register::RegisterWindowBack,[=](){
        //选择隐藏
        delete registerwindow;
        //自身显示
        this->show();
    });
    registerwindow->show();
}
void MainWindow::iSlot(QString GetData){
    qDebug()<<GetData;
}
