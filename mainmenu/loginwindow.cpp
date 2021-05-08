#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "game/gamewidget.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariantMap>
#include <QMessageBox>
#include <QJsonArray>
#include "allurl.h"
LoginWindow::LoginWindow(QString JWT,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->JWT = JWT;

    n=startTimer(1000);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Exit_clicked()
{
    emit this->loginwindowback();
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

void LoginWindow::on_Send_clicked()
{
    QString text = this->ui->textEdit->toPlainText();
    qDebug()<<text;
    this->ui->textEdit->clear();
    QVariantMap map{{"messageBody",text}};
    QUrl url(chaturl);
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("authorization",JWT.toUtf8());
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    auto reply =  manager->post(req,QJsonDocument(QJsonObject::fromVariantMap(map)).toJson());

    QTimer::singleShot(3000,this ,[=]()
    {
        if(reply->isFinished()==false){
            QMessageBox::warning(this,"warning","连接失败");
            reply->abort();
            return;
        }
    });

    connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        QByteArray raw =  reply->readAll();
        qDebug()<<raw;
        QJsonDocument json = QJsonDocument::fromJson(raw);
    });


}

void LoginWindow::timerEvent(QTimerEvent *event)
{
    QUrl url(chaturl);
    QNetworkRequest req(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    req.setRawHeader("authorization",JWT.toUtf8());
    auto reply = manager->get(req);

    QTimer::singleShot(3000,this ,[=]()
    {
        if(reply->isFinished()==false){
            QMessageBox::warning(this,"warning","连接失败");
            reply->abort();
            return;
        }
    });


    connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        QByteArray raw =  reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(raw);
        QString Text;
        auto jsonarray = json.array();
        for (int i=0;i<jsonarray.size();i++) {
            Text+=jsonarray[i].toObject()["sender"].toString()+"("+jsonarray[i].toObject()["time"].toString()+"):"+jsonarray[i].toObject()["messageBody"].toString()+"\n";
        }
        this->ui->Message->setText(Text);
        this->ui->Message->moveCursor(QTextCursor::End);
    });
}

void LoginWindow::on_Start_clicked()
{
    QUrl url(starturl);
    QNetworkRequest req(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    req.setRawHeader("authorization",JWT.toUtf8());
    auto reply = manager->get(req);

    QTimer::singleShot(3000,this ,[=]()
    {
        if(reply->isFinished()==false){
            QMessageBox::warning(this,"warning","开始失败");
            reply->abort();
            return;
        }
    });
    connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        QByteArray raw =  reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(raw);
        killTimer(n);
        auto good_jwt = JWT.right(JWT.size()-4);
        gamewidget = new GameWidget("1.116.238.196",json["port"].toInt(),good_jwt);
        QTimer::singleShot(200,this ,[=]()
        {
                this->hide();
                gamewidget->show();
        });
    });

    //TODO  返回
    /*
    connect(gamewidget,&GameWidget::GameBack,[=](){
        //n=startTimer(1000);
        //选择隐藏
        delete gamewidget;
        //自身显示
        this->show();
    });
    */
}
