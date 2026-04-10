#include "widget.h"

#include <QApplication>
#include<QSystemTrayIcon>
#include<QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    //创建系统托盘
    QSystemTrayIcon sysTray(QIcon(":/qq/qq_0.png"),&w);

    QMenu menu;
    auto showAct = new QAction("显示",&sysTray);
    auto quit = new QAction("退出",&sysTray);

    QObject::connect(showAct,&QAction::triggered,[&](){
        w.show();
    });

    QObject::connect(quit,&QAction::triggered,[&](){
        QApplication::quit();
    }) ;

    menu.addAction(showAct);
    menu.addAction(quit);

    sysTray.show();
    w.show();
    return a.exec();
}
