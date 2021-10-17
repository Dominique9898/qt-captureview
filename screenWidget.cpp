#include "screenWidget.h"

ScreenWidget::ScreenWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "---ScreenWidget init---";

    toolbar = new ToolbarWidget(this);
    colorbar = new ColorToolbarWidget(this);

//    selectWidget = new SelectWidget(this);

    // 初始化devicePixel
    scaleFactor = this->devicePixelRatio();

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
        closeCaptureWindows();
    }
}
void ScreenWidget::mousePressEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton)) return;
    if (getStatus() != SELECT) changeCurcorToAnchor(e->pos());
    STATUS status = getStatus();

    switch (status) {
    case SELECT:
            qDebug() << "--- Press SELECT 选框 ---";
            isPress = true;
            m_captureRect.setStart(e->pos());
            break;
    case RESIZE:
        qDebug() << "--- Press RESIZE 选框---";
        isPress = true;
        s_movePoint = e->pos();
        updateToolBar();
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
        updateToolBar();
        this->setCursor(Qt::SizeAllCursor);
        break;
    case DRAW:
        updateToolBar();
        break;
    default:
        break;
    }
}

void ScreenWidget::mouseMoveEvent(QMouseEvent *e)
{
    STATUS status = getStatus();
    isMoving = true;
    switch (status) {
    case SELECT:
            qDebug() << "--- Move SELECT ---";
            m_captureRect.setEnd(e->pos());
            this->update();
            qDebug() << "--- Move UPDATE ---";
            break;
    case RESIZE:
        qDebug() << "--- Move RESIZE ---";
        m_captureRect.resize(e->pos() - s_movePoint, int(m_activeSide));
        s_movePoint = e->pos();
        this->update();
        qDebug() << "--- Move RESIZE UPDATE---";
        break;
    case MOV:
        qDebug() << "--- Move MOV ---";
//        int x = e->pos().x() - s_movePoint.x();
//        int y = e->pos().y() - s_movePoint.y();
//        QPoint p(x, y);
        m_captureRect.move(e->pos() - s_movePoint);
        s_movePoint = e->pos();
        this->update();
        qDebug() << "--- Move MOV UPDATE---";
        break;
//    case DRAW:
//        break;
//    default:
//        break;
    }
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isPress = false;
    if (getWidth() == 0 && getHeight() == 0 || !isMoving) return;
//    if (m_captureRect.isInArea(e->pos()) == false) return;
    STATUS status = getStatus();
    switch (status) {
    case SELECT:
            qDebug() << "--- Release 结束SELECT选框 ---";
            setStatus(MOV);
            updateToolBar();
            qDebug() << getX() << " " << getY()  << " " << getWidth()  << " " << getHeight();
            qDebug() << "--- Release 结束SELECT选框 UPDATE ---";
//            this->update();
            break;
    case RESIZE:
        this->setCursor(Qt::ArrowCursor);
        setStatus(MOV);
        updateToolBar();
        break;
    case MOV:
        qDebug() << "--- Release 结束MOV选框 ---";
        this->setCursor(Qt::ArrowCursor);
        updateToolBar();
        qDebug() << "--- Release 结束MOV选框 UPDATE ---";
//        this->update();
        break;
    case DRAW:
        updateToolBar();
        break;
    default:
        break;
    }
    isMoving = false;
}
void ScreenWidget::paintEvent(QPaintEvent*)
{
    STATUS status = getStatus();
    switch (status) {
    case SELECT:
           qDebug() << "--- paintEvent SELECT";
            drawSelectRect();
            break;
    case MOV:
        if (!isPress) return;
        qDebug() << "--- paintEvent MOV";
        drawSelectRect();
        break;
    case RESIZE:
        qDebug() << "--- paintEvent RESIZE";
        drawSelectRect();
        break;
    case DRAW:
        break;
    default:
        break;
    }

}
void ScreenWidget::drawSelectRect()
{
    qDebug() << "--- drawSelectRect start ---";
    if (!isPress && !isMoving) return;
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
    qDebug() << "--- drawSelectRect end ---";

}
void ScreenWidget::drawResizeCircles()
{
    qDebug() << "--- 开始画Resize点 ---";

    qDebug() << "isPress " << isPress << " isMoving " << isMoving;

    if (!isPress && !isMoving) return;

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

    qDebug() << "--- 结束画Resize点 ---";
}

void ScreenWidget::changeCurcorToAnchor(QPoint p) {
    qDebug() << "--- changeCurcorToAnchor start ---";
    int x = p.x();
    int y = p.y();
    int radius = 3 * scaleFactor;
    for (int i = 0; i < 8; i++)
    {
        QPoint c_Point = circles[i];

        if (abs(x - c_Point.x()) <= radius && abs(y - c_Point.y()) <= radius)
        {
            qDebug() << "has m_activeSide" << i;
            m_activeSide = MouseType(i);
            setStatus(RESIZE);
            break;
        } else {
            m_activeSide = DEFAULT;
            setCursor(Qt::ArrowCursor);
        }
    }
    qDebug() << "m_activeSide = " << m_activeSide;

    switch (m_activeSide) {
            case TOPLEFT_SIDE:
                setCursor(Qt::SizeFDiagCursor);
                break;
            case TOP_SIDE:
                setCursor(Qt::SizeVerCursor);
                break;
            case TOPRIGHT_SIDE:
                setCursor(Qt::SizeBDiagCursor);
                break;

            case LEFT_SIDE:
                setCursor(Qt::SizeHorCursor);
                break;
            case RIGHT_SIDE:
                setCursor(Qt::SizeHorCursor);
                break;

            case BOTTOMLEFT_SIDE:
                setCursor(Qt::SizeBDiagCursor);
                break;
            case BOTTOM_SIDE:
                setCursor(Qt::SizeVerCursor);
                break;
            case BOTTOMRIGHT_SIDE:
                setCursor(Qt::SizeFDiagCursor);
                break;
            default:
                setCursor(Qt::ArrowCursor);
                break;
        }
    qDebug() << "--- changeCurcorToAnchor end ---";
}

void ScreenWidget::updateToolBar()
{


    qDebug() << "--- updateToolBar start ---";

    QPoint p = m_captureRect.getBottomRightPoint();
    toolbar->setPosition(p);
    colorbar->setPosition(p);

    if (!isPress && getStatus() != SELECT) {
        toolbar->show();
    } else {
        toolbar->hide();
    }

    if (getStatus() == DRAW) {
        colorbar->show();
    }

    qDebug() << "--- updateToolBar end ---";

}
void ScreenWidget::setDrawShape(Draw_Shape shape)
{
    m_captureRect.setDrawShape(shape);
    setStatus(DRAW);
    colorbar->show();
}
void ScreenWidget::setDrawColor(Draw_Color color)
{
    m_captureRect.setDrawColor(color);
}
void ScreenWidget::setDrawSize(Draw_Size size)
{
    m_captureRect.setDrawSize(size);
}
void ScreenWidget::clearShapes()
{
    m_captureRect.clear();
}
void ScreenWidget::saveCapture()
{
    QString picName = "政务微信";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyyMMdd-hhmmss");
    picName += current_date;

    QString srcDirPath = QFileDialog::getSaveFileName(
                this,
                tr("存储"),
                QDir::homePath()+"/Desktop/"+picName,
                tr("Images (*.png *.bmp *.jpg)"));
    if (srcDirPath.isEmpty())
    {
        return;
    }
    QPixmap pix = getCaptureGrabPixmap();
    pix.toImage().save(srcDirPath);
    closeCaptureWindows();
}
void ScreenWidget::closeCaptureWindows()
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
QPixmap ScreenWidget::getCaptureGrabPixmap()
{
    qDebug() << "-- getCaptureGrabPixmap start --";

    int x = getX() * scaleFactor;
    int y = getY() * scaleFactor;
    int w = getWidth() * scaleFactor;
    int h = getHeight() * scaleFactor;

    qDebug() << x << " " << y  << " " << w  << " " << h;
    qDebug() << "-- getCaptureGrabPixmap end --";

    return originBackgroundScreen.copy(x, y, w, h);
}
void ScreenWidget::capture() {
    qDebug() << "--- capture start ---";
    QPixmap pix = getCaptureGrabPixmap();
    qDebug() << "capture pix=" << pix;
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setImage(pix.toImage());
    closeCaptureWindows();
    qDebug() << "--- capture end ---";
}
