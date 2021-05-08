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

    int pos = 0;

  /*  QRegExp regx("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator regs(regx, 0);
    int posPhone = 0;
    QValidator::State res = regs.validate(Phone, posPhone);
    */

    if(Id==""||Password==""||Email==""||Phone==""){
        QMessageBox::warning(this,"warning","信息不全！请完善！");
    }else if(Password.length()<6||Password.length()>16){
         QMessageBox::warning(this,"warning","请输入6到16位密码");
    }else{
        QVariantMap map{{"username",Id},{"password",Password},{"phoneNumber",Phone},{"email",Email}};

        QNetworkRequest req(QUrl("http://192.168.137.1:3000/api/signup"));
        req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        manager->post(req,QJsonDocument(QJsonObject::fromVariantMap(map)).toJson());

        connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
            QByteArray raw =  reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(raw);

            qDebug()<<json["success"].toBool();
            qDebug()<<json["msg"].toString();
            if(json["success"].toBool()==true){
                QMessageBox::about(this,"注册成功！",json["msg"].toString());
                this->ui->IdLineEdit->clear();
                this->ui->EmailLineEdit->clear();
                this->ui->PasswordLineEdit->clear();
                this->ui->PhoneLineEdit->clear();
            }
            else{
                QMessageBox::warning(this,"warning",json["msg"].toString());
            }

        });
    }


}

void Register::on_BackButton_clicked()
{
    emit this->RegisterWindowBack();
}
