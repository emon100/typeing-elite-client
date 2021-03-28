#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>

class QTcpSocket;

class GameModel;
class GameView;
class KeyboardInput;
class NetworkIO;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent=nullptr);

signals:


private:
    void initWidget();

    GameModel *model;
    GameView  *view;

    KeyboardInput *kb;
    QTcpSocket *client;

};

#endif // GAMEWIDGET_H
