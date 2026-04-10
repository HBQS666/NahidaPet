#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMap>
#include<QList>
#include<QTimer>
#include<QUrl>
#include<QEvent>
#include<QMouseEvent>
#include<QContextMenuEvent>
#include<QMenu>

class QPaintEvent;

namespace act{
Q_NAMESPACE
enum roleAct{
    swing,
    sleep,
    sayhello,
    act_1
};
Q_ENUM_NS(roleAct)
}

using namespace act;

class Widget : public QWidget
{
    Q_OBJECT
public slots:
    void onMenuTriggered(QAction*act);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *e);



    //存储角色当前动作路径的QUrl
    QMap<roleAct,QList<QUrl>>action_mp;
    QTimer *time;
    roleAct cur_role_act;
    QMenu * menu;
    //当前所用的图片 Url
    QUrl cur_role_pix;

    //显示动作
    void showAnimation(roleAct act);

    void initMenu();

    // 加载路径
    void loadRoleActRes();

    void contextMenuEvent(QContextMenuEvent *e);
};
#endif // WIDGET_H

//拖拽设置
class dragFilter:public QObject{
public:
    bool eventFilter(QObject *obj,QEvent* e){
        auto w = dynamic_cast<QWidget*>(obj);

        if(!w) return false;

        //如果当前事件是鼠标点击
        if(e->type() == QMouseEvent::MouseButtonPress){
            auto mouse = dynamic_cast<QMouseEvent*>(e);
            if(!mouse) return false;
            pos = mouse->pos();
        }

        //如果当前事件是鼠标拖拽
        else if(e->type() == QMouseEvent::MouseMove){
            auto mouse = dynamic_cast<QMouseEvent*>(e);
            if(!mouse) return false;
            if(mouse->buttons()&Qt::MouseButton::LeftButton){
                w->move(mouse->globalPosition().toPoint()-pos);
            }
        }

        return QObject::eventFilter(obj,e);

    }

    //记录当前鼠标位置
    QPoint pos;
};




