# include "widget.h"
#include<QPaintEvent>
#include<QPainter>
#include<QUrl>
#include<QList>
#include<QPixmap>
#include<QContextMenuEvent>
#include<QCursor>
#include<QMetaEnum>

void Widget::onMenuTriggered(QAction *act)
{
    QMetaEnum meta = QMetaEnum::fromType<roleAct>();
    bool flag;
    int temp = meta.keyToValue(act->text().toStdString().c_str(),&flag);

    if(!flag) return ;

    showAnimation(static_cast<roleAct>(temp));
}

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    time(new QTimer(this))
{
    this->installEventFilter(new dragFilter );
    //去除边框
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    menu = new QMenu(this);
    initMenu();


    connect(time,&QTimer::timeout,[this](){
        //记录当前的图片的索引
        static int index = 0;
        auto paths = this->action_mp.value(this->cur_role_act);
        this->cur_role_pix = paths[index++%paths.size()];
        this->update();
    });
    loadRoleActRes();
    showAnimation(act::act_1);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *e)
{

    QPainter paint(this);
    QPixmap pix ;
    pix.load(this->cur_role_pix.toLocalFile());
    paint.drawPixmap(0,0,pix);
}

void Widget::showAnimation(roleAct act)
{
    time->stop();
    this->cur_role_act = act;
    time->start(60);
}

void Widget::initMenu()
{
    menu->addAction("swing");
    menu->addAction("act_1");
    // menu->addAction("休息");

    QAction *action = new QAction("隐藏");

    connect(action,&QAction::triggered,[this](){
        this->hide();
    });
    menu->addAction(action);

    connect(this->menu,&QMenu::triggered,this,&Widget::onMenuTriggered);

}

void Widget::loadRoleActRes()
{
    auto addRes = [this](roleAct act,QString path,int cnt){
        QList<QUrl>paths;
        char buf[260];
        for(int i = 0;i<cnt;i++){
            memset(buf,0,sizeof(buf));
            snprintf(buf,260,path.toStdString().c_str(),i);
            paths.append(QUrl::fromLocalFile(buf));
        }
        this->action_mp.insert(act,paths);
    };

    addRes(roleAct::act_1,":/act_1/nl_%d.png",73);
    addRes(roleAct::swing,":/swim/qq_%d.png",110);

}

void Widget::contextMenuEvent(QContextMenuEvent *e)
{
    this->menu->popup(QCursor::pos());
}

