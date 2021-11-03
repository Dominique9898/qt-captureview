#include "selectwidget.h"

SelectWidget* SelectWidget::self = nullptr;
SelectWidget* SelectWidget::Instance() {
    if (!self)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self)
        {
            self = new SelectWidget;
        }
    }
    return self;
}

SelectWidget::SelectWidget(QWidget *parent)
{
    qDebug() << "--- selectWidget init ---";

    Qt::WindowFlags windowFlags =  Qt::FramelessWindowHint |
            Qt::BypassWindowManagerHint |
            Qt::WindowStaysOnTopHint |
            Qt::NoDropShadowWindowHint;
    setWindowFlags(windowFlags);
    setAttribute(Qt::WA_TranslucentBackground, true);
//    setGeometry(0, 0, 200, 100);
    update();
    hide();
}

void SelectWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.begin(this);
    painter.drawRect(10,10,50,50);
    painter.end();
}
void SelectWidget::Show(int sx, int sy, int w, int h)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    _show = true;
    setGeometry(sx, sy, w, h);
    show();
//    update();
}

void SelectWidget::Hide()
{
    _show = false;
    this->hide();
}

bool SelectWidget::isShow()
{
    return _show;
}
