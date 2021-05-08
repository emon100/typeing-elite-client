#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QRegExp>
#include <QTimer>
#include "allurl.h"

using namespace std;
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->ui->IdLineEdit->setPlaceholderText("请输入ID");
    this->ui->PasswordLineEdit->setPlaceholderText("请输入6到16位密码");
    this->ui->PhoneLineEdit->setPlaceholderText("请输入11位手机号");
    this->ui->EmailLineEdit->setPlaceholderText("请输入邮箱");
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

    QRegExp exp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");//正则表达式
    QRegExp regx("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");

    if(Id==""||Password==""||Email==""||Phone==""){
        QMessageBox::warning(this,"warning","信息不全！请完善！");
    }else if(Password.length()<6||Password.length()>16){
         QMessageBox::warning(this,"warning","请输入6到16位密码");
    }else if(!exp.exactMatch(Email)){
        QMessageBox::warning(this,"warning","邮箱格式不正确");
    }else if(!regx.exactMatch(Phone)){
        QMessageBox::warning(this,"warning","手机号输入错误");
    }
    else{
        QVariantMap map{{"username",Id},{"password",Password},{"phoneNumber",Phone},{"email",Email}};
        QUrl url(signupurl);
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

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
