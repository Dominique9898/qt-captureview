#include "screenWidget.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QList>
typedef struct{
 int screen_no;
 QRect rect;
}M_SCREEN;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<QScreen*> screens = QGuiApplication::screens();
    int nums = screens.size();
    ScreenWidget m_screens[nums];


    for (int i = 0; i < nums; i++)
    {
        m_screens[i].setGeometry(screens[i]->geometry());
        m_screens[i].setScreen(screens[i]);
        m_screens[i].startCapture(i);
    }
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    qDebug() << "-- 一个截图窗口关闭 收到结束截图信号 --";
    int result = a.exec();
    for (int i = 0; i < nums; i++) {
        delete  screens[i];
    }
    qDebug() << "-- 结束截图信号 --";
    return result;
}
