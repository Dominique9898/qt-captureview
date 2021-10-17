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
    this->setWindowFlags(windowFlags);

    setGeometry(0, 0, 200, 100);
//    update();
    show();

    QGraphicsScene scene(0, 0, 200, 100);
    QGraphicsView view(&scene);
    QGraphicsPixmapItem *item;
    QPixmap* painterPix;

    view.setMinimumSize(200, 100);
    view.setSceneRect(0, 0, 200, 100);

    auto rect = new QGraphicsRectItem(10, 10, 50, 50);
    rect->setPos(0, 0);
    scene.addItem(rect);
    view.show();

}

void SelectWidget::paintEvent(QPaintEvent *)
{
//    QPen pen;
//    pen.setColor(QColor("#67bade"));
//    pen.setWidth(2);
//    pen.setStyle(Qt::SolidLine);
//    QPainter painter;
//    painter.begin(this);
//    painter.drawRect(10,10,50,50);
//    painter.end();
}
