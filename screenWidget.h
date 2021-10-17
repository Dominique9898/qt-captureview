#ifndef SCREENCAPTURE_H
#include "UI/colortoolbarwidget/colortoolbarwidget.h"
#include "UI/toolbarwidget/toolbarwidget.h"
#include "selectwidget.h"
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMutex>
#include <QClipboard>
#include <QDateTime>
#include <QFileDialog>
#include "Shape/shape/shape.h"
#include <math.h>
#define SCREENCAPTURE_H


class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    // VOID 只第一次按下鼠标
    enum STATUS { SELECT, MOV, RESIZE, DRAW};

    enum MouseType {
        TOPLEFT_SIDE, // SizeFDiagCursor
        TOP_SIDE, //  SizeVerCursor
        TOPRIGHT_SIDE, // SizeBDiagCursor

        LEFT_SIDE, // SizeHorCursor
        RIGHT_SIDE, // SizeHorCursor

        BOTTOMLEFT_SIDE, // SizeBDiagCursor
        BOTTOM_SIDE, // SizeVerCursor
        BOTTOMRIGHT_SIDE, // SizeFDiagCursor,
        DEFAULT
    };

    ///控制选区变化的圆点
    QPoint circles[8] = {};

public:

    ScreenWidget(QWidget *parent = nullptr);
    ~ScreenWidget();

    // 创建窗口单例
    static ScreenWidget *Instance();

    static void destroy();
    void startCapture(int id);
    void setScreen(QScreen* screen);

    void setStatus(STATUS status);
    STATUS getStatus();
    void setDrawShape(Draw_Shape shape);
    void setDrawColor(Draw_Color color);
    void setDrawSize(Draw_Size size);
    void clearShapes();
    void saveCapture();

    /// 截图
    void capture();
    /// 关闭截图
    void closeCaptureWindows();
signals:
    void lastWindowClosed();

private:
    static ScreenWidget* self;
    static bool isActivity;
    int screenId; /// 屏幕Id
    int s_width;
    int s_height;
    int s_x; /// screen的左上角x位置
    int s_y; /// screen的左上角y位置
    bool isPress = false;
    bool isMoving = false;
    bool isDrawing = false;
    int scaleFactor;

    STATUS status;
    MouseType m_activeSide;

    /// captureWin 对应的screen
    QScreen* w_screen;

    /// 当前桌面屏幕的矩形数据
    QRect desktopRect;

    QPainter m_painter;

    /// 屏幕暗色背景图
    QPixmap    grayBackgroundScreen;

    /// 屏幕原画
    QPixmap    originBackgroundScreen;

    /// 选取的截图选区
    Shape m_captureRect;

    /// 移动选框的起始点
    QPoint s_movePoint;

    QPixmap tmpPixmap;

    /// 辅助涂鸦画布(resize点)
    QPixmap assistPixmap;

    SelectWidget* selectWidget;

    ToolbarWidget* toolbar;
    ColorToolbarWidget* colorbar;

protected:
//        /**
//         * @brief : 关闭窗口事件
//         */
//        virtual void closeEvent(QCloseEvent *);
//        /**
//         * @brief : 双击事件
//         */
//        virtual void mouseDoubleClickEvent(QMouseEvent*);
        /**
         * @brief : 鼠标按下事件
         */
        virtual void mousePressEvent(QMouseEvent *);
        /**
         * @brief : 鼠标释放事件
         */
        virtual void mouseReleaseEvent(QMouseEvent *e);
        /**
         * @brief : 鼠标移动事件
         */
        virtual void mouseMoveEvent(QMouseEvent *e);

        /**
         * @brief : 按键按下事件
         */
        virtual void keyPressEvent(QKeyEvent*);

        /**
         * @brief : 自绘事件
         */
        virtual void paintEvent(QPaintEvent *);

private:

    /// 初始化截图窗口(窗口类型, 状态, 边框)
    void initCaptureWindow();

    /// 获得屏幕的原画
    void initOriginBackgroundScreen();

    /// 获得暗色处理的屏幕图
    void initGrayBackgroundScreen();

    /// 获得当前屏幕的大小
    const QRect& getScreenRect();

    /// 获取选区框的width,height,dx,dy
    int getWidth();
    int getHeight();
    int getX();
    int getY();

    /// 绘制拉取的选框的原图
    void drawSelectRect();

    /// Resize 选框
    void updateSelectRect();

    ///绘制Resize的点
    void drawResizeCircles();

    void changeCurcorToAnchor(QPoint p);

    void updateToolBar();

    QPixmap getCaptureGrabPixmap();

};
#endif // SCREENCAPTURE_H
