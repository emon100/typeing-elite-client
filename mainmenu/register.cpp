#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariantMap>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title

}

Register::~Register()
{
    delete ui;
}

void Register::on_RegisterButton_clicked()
{
    QString Id = this->ui->IdLineEdit->text();
    QString Email = this->ui->EmailLineEdit->text();
    QString Password = this->ui->PasswordLineEdit->text();
    QString Phone = this->ui->PhoneLineEdit->text();

    if(Id==""||Password==""){
        QMessageBox::warning(this,"warning","信息不全！请完善！");
    }
    else{
        QVariantMap map{{"username",Id},{"password",Password}};

        QNetworkRequest req(QUrl("http://192.168.137.1:3000/api/signup"));
        req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        manager->post(req,QJsonDocument(QJsonObject::fromVariantMap(map)).toJson());

        connect(manager,&QNetworkAccessManager::finished,[](QNetworkReply *reply){
            QByteArray raw =  reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(raw);

            qDebug()<<json["success"].toBool();
            qDebug()<<json["msg"].toString();
        });
    }




}

void Register::on_BackButton_clicked()
{
    emit this->RegisterWindowBack();
}
