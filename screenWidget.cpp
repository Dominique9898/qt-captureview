#include "screenWidget.h"

ScreenWidget::ScreenWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "---ScreenWidget init---";
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

    // 初始化devicePixel
    scaleFactor = this->devicePixelRatio();

    // 初始化截图状态
    setStatus(SELECT);

    // 初始化窗口设置
    initCaptureWindow();

    // 初始化背景图片 + Shape;
    initOriginBackgroundScreen();

    // 初始化灰色背景图片
    initGrayBackgroundScreen();
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

    m_captureRect.setSize(s_width, s_height);

    s_x = temp_rect.x();
    s_y = temp_rect.y();
    originBackgroundScreen = w_screen->grabWindow(winId(), s_x,
                                                s_y, s_width,
                                                s_height);
    qDebug() << "get originBackgroundScreen";
    qDebug() << "---initOriginBackgroundScreen end ---";
}
void ScreenWidget::initGrayBackgroundScreen()
{
    qDebug() << "---initGrayBackgroundScreen start --- ";

    /// 制作暗色屏幕背景
    QPixmap temp_dim_pix(s_width, s_height);
    temp_dim_pix.fill((QColor(0, 0, 0, 160)));

    grayBackgroundScreen = originBackgroundScreen;
    qDebug() << "get grayBackgroundScreen";

    QPainter p(&grayBackgroundScreen);
    qDebug() << "init grayBackgroundScreen QPainter";
    p.drawPixmap(0, 0, temp_dim_pix);
    qDebug() << "paint grayBackgroundScreen";

    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background,QBrush(grayBackgroundScreen));
    this-> setPalette( palette );
}
void ScreenWidget::setScreen(QScreen* screen)
{
    w_screen = screen;
}

ScreenWidget::STATUS ScreenWidget::getStatus()
{
    return status;
}
void ScreenWidget::setStatus(STATUS status)
{
    this->status = status;
}
int ScreenWidget::getWidth()
{
    return m_captureRect.getBottomRightPoint().x() - m_captureRect.getTopLeftPoint().x();
}
int ScreenWidget::getHeight()
{
    return m_captureRect.getBottomRightPoint().y() - m_captureRect.getTopLeftPoint().y();
}
int ScreenWidget::getX()
{
    return m_captureRect.getTopLeftPoint().x();
}
int ScreenWidget::getY()
{
    return m_captureRect.getTopLeftPoint().y();
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
void ScreenWidget::mousePressEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton)) return;
    STATUS status = getStatus();




    switch (status) {
    case SELECT:
            qDebug() << "--- Press SELECT 选框 ---";
            isPress = true;
            m_captureRect.setStart(e->pos());
            break;
    case MOV:
        if (!m_captureRect.isInArea(e->pos())) {
            qDebug() << "--- Press MOV 不在选框内 ---";
            isPress = false;
            return;
        }
        qDebug() << "--- Press MOV 选框 ---";
        s_movePoint = e->pos();
        isPress = true;
        this->setCursor(Qt::SizeAllCursor);
        break;
    case RESIZE:
        break;
    case DRAW:
        break;
    default:
        break;
    }
}

void ScreenWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton) || !isPress) return;
    STATUS status = getStatus();
    switch (status) {
    case SELECT:
            qDebug() << "--- Move SELECT ---";
            m_captureRect.setEnd(e->pos());
            this->update();
            qDebug() << "--- Move UPDATE ---";
            break;
    case MOV:
        qDebug() << "--- Move MOV ---";
        int x = e->pos().x() - s_movePoint.x();
        int y = e->pos().y() - s_movePoint.y();
        QPoint p(x, y);
        m_captureRect.move(p);
        s_movePoint = e->pos();
        this->update();
        qDebug() << "--- Move MOV UPDATE---";
        break;
//    case RESIZE:
//        break;
//    case DRAW:
//        break;
//    default:
//        break;
    }
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (!isPress) return;
    STATUS status = getStatus();
    switch (status) {
    case SELECT:
            qDebug() << "--- Release 结束SELECT选框 ---";
            m_captureRect.setEnd(e->pos());
            setStatus(MOV);
            isPress = false;

            assistPixmap = QPixmap(getWidth(), getHeight());
            assistPixmap.fill(Qt::transparent);
            m_painter.drawPixmap(getX(), getY(), assistPixmap);

            this->update();
            qDebug() << "--- Release 结束SELECT选框 UPDATE ---";
            break;
    case MOV:
        qDebug() << "--- Release 结束MOV选框 ---";
        isPress = false;
        assistPixmap = QPixmap(getWidth(), getHeight());
        assistPixmap.fill(Qt::transparent);
        m_painter.drawPixmap(getX(), getY(), assistPixmap);
        this->update();
        qDebug() << "--- Release 结束MOV选框 UPDATE ---";
        this->setCursor(Qt::ArrowCursor);
        break;
    case RESIZE:
        break;
    case DRAW:
        break;
    default:
        break;
    }
}
void ScreenWidget::paintEvent(QPaintEvent*)
{
    STATUS status = getStatus();
    switch (status) {
    case SELECT:
            if (!isPress) drawResizeCircles();
            drawSelectRect();
            break;
    case MOV:
        if (!isPress) drawResizeCircles();
        drawSelectRect();
        break;
    case RESIZE:
        break;
    case DRAW:
        break;
    default:
        break;
    }

}
void ScreenWidget::drawSelectRect()
{
    m_painter.begin(this);
    m_painter.save();
    QPen pen;
    pen.setColor(QColor("#67bade"));
    pen.setWidth(scaleFactor);
    pen.setStyle(Qt::SolidLine);
    m_painter.setPen(pen);

    if (getWidth() != 0 && getHeight() != 0) {
            m_painter.drawPixmap(getX(), getY(), originBackgroundScreen.copy(getX() * scaleFactor, getY() * scaleFactor, getWidth() * scaleFactor, getHeight() * scaleFactor));
    }

    m_painter.drawRect(getX(), getY(), getWidth(), getHeight());
    drawResizeCircles();
    m_painter.restore();
    m_painter.end();
}
void ScreenWidget::drawResizeCircles()
{
    qDebug() << "--- 开始画Resize点 ---";

//    m_painter.begin(this);
//    m_painter.save();
    int radius = 3 * scaleFactor;
    int x = getX();
    int y = getY();
    int w = getWidth();
    int h = getHeight();


    circles[0] = QPoint(x, y);
    circles[1] = QPoint(x+w/2, y);
    circles[2] = QPoint(x+w, y);

    circles[3] = QPoint(x, y+h/2);
    circles[4] = QPoint(x+w, y+h/2),

    circles[5] = QPoint(x, y+h),
    circles[6] = QPoint(x+w/2, y+h),
    circles[7] = QPoint(x+w, y+h);

    QPen pen;
    pen.setWidth(scaleFactor);
    pen.setColor(QColor("#67bade"));
    m_painter.setBrush(Qt::white);
    m_painter.setPen(pen);

    m_painter.drawEllipse(circles[0],radius,radius);
    m_painter.drawEllipse(circles[1],radius,radius);
    m_painter.drawEllipse(circles[2],radius,radius);
    m_painter.drawEllipse(circles[3],radius,radius);
    m_painter.drawEllipse(circles[4],radius,radius);
    m_painter.drawEllipse(circles[5],radius,radius);
    m_painter.drawEllipse(circles[6],radius,radius);
    m_painter.drawEllipse(circles[7],radius,radius);
//    m_painter.restore();
//    m_painter.end();
    qDebug() << "--- 结束画Resize点 ---";
}

