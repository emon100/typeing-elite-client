#include "changepassword.h"
#include "ui_changepassword.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariantMap>
#include <QMessageBox>
#include <QJsonArray>
#include <QTimer>
#include <QRegExp>
#include "allurl.h"
ChangePassword::ChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->setWindowIcon(QPixmap(Logo));        //logo
    this->ui->IDLineEdit->setPlaceholderText("请输入要修改账户的ID");
    this->ui->PasswordLineEdit->setPlaceholderText("请输入修改后的密码");
    this->ui->PhoneLineEdit->setPlaceholderText("请输入要修改账户的手机号");
    this->ui->EmailLineEdit->setPlaceholderText("请输入要修改账户的邮箱");
    this->ui->AgainPasswordLineEdit->setPlaceholderText("请再次输入密码");
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_BackPushButton_clicked()
{
    emit this->changepasswordwindowback();
}

void ChangePassword::on_ChangePushButton_clicked()
{
    QString Id = this->ui->IDLineEdit->text();
    QString Phone = this->ui->PhoneLineEdit->text();
    QString Email = this->ui->EmailLineEdit->text();
    QString Password = this->ui->PasswordLineEdit->text();
    QString AgainPassword = this->ui->AgainPasswordLineEdit->text();



    QRegExp exp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");//正则表达式
    QRegExp regx("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");

    if(Id==""||Password==""||Email==""||Phone==""||AgainPassword==""){
        QMessageBox::warning(this,"warning","信息不全！请完善！");
    }else if(Password.length()<6||Password.length()>16){
         QMessageBox::warning(this,"warning","请输入6到16位密码");
    }else if(!exp.exactMatch(Email)){
        QMessageBox::warning(this,"warning","邮箱格式不正确");
    }else if(!regx.exactMatch(Phone)){
        QMessageBox::warning(this,"warning","手机号输入错误");
    }else if(AgainPassword!=Password){
        QMessageBox::warning(this,"warning","两次输入密码不一致请重新输入");
    }
    else{
        QVariantMap map{{"username",Id},{"newPassword",Password},{"phoneNumber",Phone},{"email",Email}};

        QUrl url(changepasswordurl);
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
                QMessageBox::about(this,"修改成功！",json["msg"].toString());
                this->ui->IDLineEdit->clear();
                this->ui->EmailLineEdit->clear();
                this->ui->PasswordLineEdit->clear();
                this->ui->PhoneLineEdit->clear();
                this->ui->AgainPasswordLineEdit->clear();
            }
            else{
                QMessageBox::warning(this,"warning",json["msg"].toString());
            }

        });
    }
}//背景
void ChangePassword::paintEvent(QPaintEvent *)
{
    QPixmap pix;            //创建一个对象
    QPainter painter(this);    //画家 在this上画画
    painter.drawPixmap(0,0,this->width(),this->height(),pix) ;
    pix.load(Logo);
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap((this->width()-pix.width())/2,0,pix) ;
}

