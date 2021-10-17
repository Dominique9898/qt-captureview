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
//        m_screens[i].setGeometry(screens[i]->geometry());
        m_screens[i].setGeometry(0, 0, 500, 500);
        m_screens[i].setScreen(screens[i]);
        m_screens[i].startCapture(i);
    }
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    int result = a.exec();
    for (int i = 0; i < nums; i++) {
        delete  screens[i];
    }
    return result;
}
