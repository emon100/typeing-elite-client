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
#include <QTextEdit>

LoginWindow::LoginWindow(QString JWT,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WindowX,WindowY);            //大小
    this->setWindowTitle("打字精英");      //title
    this->JWT = JWT;

    n=startTimer(1000);
    this->ui->textEdit->setPlaceholderText("输入要发送的聊天内容");
    this->ui->textEdit->installEventFilter(this);

    this->ui->Name->setStyleSheet("color:white");
    this->ui->Score->setStyleSheet("color:white");
    this->ui->label->setStyleSheet("color:white");
    this->ui->ChatLabel->setStyleSheet("color:white");
    this->ui->Rank->setStyleSheet("color:white");

    this->ui->ChangeName->setVisible(false);
    this->ui->FinishChangeNameButton->setVisible(false);

    rankitem = new QStandardItemModel(10,2);
    this->ui->RankView->setModel(rankitem);

    this->ui->RankView->setSelectionMode( QAbstractItemView::NoSelection);
    this->ui->RankView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rankitem->setHeaderData(0,Qt::Horizontal, "昵称");
    rankitem->setHeaderData(1,Qt::Horizontal, "分数");
    UpdateInformation();




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
        if(reply->isFinished()==false&&flag){
            QMessageBox::warning(this,"warning","连接失败");
            reply->abort();
            flag = false;
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

        connect(gamewidget,&GameWidget::GameBack,[=](){
            UpdateInformation();
            n=startTimer(1000);
            //选择隐藏
            delete gamewidget;
            //自身显示
            this->show();
        });
    });



}

void LoginWindow::on_Help_clicked()
{
    QMessageBox::about(this,"游戏帮助","点击开始游戏进入游戏，会获得红色的3个字母作为角色的"
                                   "特征，如果被人敲打角色字母会死亡，响应的如果敲击敌人的3个字母"
                                   "敌人就会死亡。能攻击敌人或者移动到某处当且仅当响应字母在黑色矩形框内");
}


bool LoginWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent *>(event);
        if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Enter){
            if(this->ui->textEdit->toPlainText()!=""){
                this->on_Send_clicked();
            }
            return true;
        }else{
            return QObject::eventFilter(obj, event);
        }

    }else{
        return QObject::eventFilter(obj, event);
    }
}
void LoginWindow::UpdateInformation(){
    QUrl url(scoreurl);
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
        flag = true;
        //TODO json名
        qDebug()<<json;
        this->ui->Name->setText("昵称:"+json["nickname"].toString());
        this->ui->Score->setText(QString("分数:%1").arg(json["score"].toInt()));

    });


    //TODO 排行榜
    QUrl rankurl(getRankListurl);
    QNetworkRequest rankreq(rankurl);
    QNetworkAccessManager *rankmanager = new QNetworkAccessManager(this);
    rankreq.setRawHeader("authorization",JWT.toUtf8());
    auto rankreply = rankmanager->get(rankreq);

    QTimer::singleShot(3000,this ,[=]()
    {
        if(rankreply->isFinished()==false){
            QMessageBox::warning(this,"warning","开始失败");
            rankreply->abort();
            return;
        }
    });
    connect(rankmanager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        QByteArray raw =  reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(raw);
        flag = true;

        auto jsonarray = json["rankList"].toArray();
        for (int i=0;i<jsonarray.size();i++) {
            qDebug()<<jsonarray[i].toObject()["score"].toInt();
            rankitem->setItem(i, 0, new QStandardItem(jsonarray[i].toObject()["nickname"].toString()));
            rankitem->setItem(i, 1, new QStandardItem(QString("%1").arg(jsonarray[i].toObject()["score"].toInt())));
        }

    });
}

void LoginWindow::on_FinishChangeNameButton_clicked()
{
    this->ui->ChangeNameButton->setVisible(true);
    this->ui->Name->setVisible(true);
    this->ui->ChangeName->setVisible(false);
    this->ui->FinishChangeNameButton->setVisible(false);

    QString Name = this->ui->ChangeName->text();
    if(Name==""){
         QMessageBox::warning(this,"warning","昵称不能为空修改失败");
         return;
    }

    QVariantMap map{{"newNickname",Name}};
    QUrl url(changenicknameurl);
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
        QJsonDocument json = QJsonDocument::fromJson(raw);
        if(json["success"].toBool()){
            this->ui->Name->setText("昵称:"+this->ui->ChangeName->text());
            this->JWT=json["newJWT"].toString();
            qDebug()<<this->JWT;
            UpdateInformation();
        }
        else {
            QMessageBox::warning(this,"warning",json["msg"].toString());
        }
    });


}

void LoginWindow::on_ChangeNameButton_clicked()
{
    this->ui->ChangeNameButton->setVisible(false);
    this->ui->Name->setVisible(false);
    this->ui->ChangeName->setVisible(true);
    this->ui->FinishChangeNameButton->setVisible(true);
}
