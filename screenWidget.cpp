#include "screenWidget.h"

ScreenWidget::ScreenWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化截图窗口
    initCaptureWindow();
}
bool ScreenWidget::isActivity = false;
ScreenWidget* ScreenWidget::self = nullptr;
ScreenWidget* ScreenWidget::Instance() {
    if (!isActivity && self) {
        destroy();
    }
    static QMutex mutex;
    if (!self) {
       QMutexLocker locker(&mutex);
       if (!self) {
           isActivity = true;
           self = new ScreenWidget;
       }
    }
    return self;
}

ScreenWidget::~ScreenWidget()
{
}

void ScreenWidget::initCaptureWindow()
{


#ifdef WIN32

    initOriginBackgroundScreen();

    showFullScreen();

#elif __APPLE__

    Qt::WindowFlags windowFlags =  Qt::FramelessWindowHint |
            Qt::BypassWindowManagerHint |
            Qt::WindowStaysOnTopHint |
            Qt::NoDropShadowWindowHint;

    this->setWindowFlags(windowFlags);

    initOriginBackgroundScreen();

    show();
#endif
}

void ScreenWidget::destroy()
{
    if (!isActivity && self) {
        delete self;
        self = nullptr;
    }
}

void ScreenWidget::startCapture(int id)
{
    qDebug() << "startCapture screen_" << id;
    screenId = id;
    initOriginBackgroundScreen();
    initGrayBackgroundScreen();
    show();
}
void ScreenWidget::initOriginBackgroundScreen()
{
    qDebug() << screenId;
    qDebug() << "---initOriginBackgroundScreen start --- ";
    qDebug() << "screen" << screenId;

    // 截取当前桌面，作为截屏的背景图
    w_screen = QApplication::screens()[screenId];
    const QRect& temp_rect = w_screen->geometry();
    s_width = temp_rect.width();
    s_height = temp_rect.height();
    s_x = temp_rect.x();
    s_y = temp_rect.y();
    originBackgroundScreen = w_screen->grabWindow(winId(), s_x,
                                                s_y, s_width,
                                                s_height);
    qDebug() << "originBackgroundScreen" << originBackgroundScreen;
    qDebug() << "---initOriginBackgroundScreen end ---";
}
void ScreenWidget::initGrayBackgroundScreen()
{
    qDebug() << "---initGrayBackgroundScreen start --- ";

    /// 获得屏幕原画
    QPixmap temp_screen = originBackgroundScreen;

    /// 制作暗色屏幕背景
    QPixmap temp_dim_pix(s_width, s_height);
    temp_dim_pix.fill((QColor(0, 0, 0, 160)));

    grayBackgroundScreen = originBackgroundScreen;
    qDebug() << "grayBackgroundScreen 初始化为originBackgroundScreen" << originBackgroundScreen;

    QPainter p(&grayBackgroundScreen);
    qDebug() << "初始化 grayBackgroundScreen QPainter" << grayBackgroundScreen;
    p.drawPixmap(0, 0, temp_dim_pix);
    qDebug() << "灰色画布画在 grayBackgroundScreen" << grayBackgroundScreen;

    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background,QBrush(grayBackgroundScreen));
    this-> setPalette( palette );
}
void ScreenWidget::setScreen(QScreen* screen)
{
    w_screen = screen;
}
void ScreenWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        qDebug() << "-- 结束截图 --";
        qDebug() << "close ScreenWidget" << this;
        close();
        qDebug() << "emit lastWindowClosed";
        emit lastWindowClosed();
        qDebug() << "destroy ScreenWidget";
        destroy();
        QApplication::quit();
        qDebug() << "-- 结束截图 --";
    }
}

