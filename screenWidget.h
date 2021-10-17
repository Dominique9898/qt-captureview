#ifndef SCREENCAPTURE_H
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMutex>
#include "Shape/shape/shape.h"

#define SCREENCAPTURE_H


class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    // VOID 只第一次按下鼠标
    enum STATUS { SELECT, MOV, RESIZE, DRAW};

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
    bool isRelease = true;
    int scaleFactor;

    STATUS status;

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

    void closeCaptureWindows();

    /// 绘制拉取的选框的原图
    void drawSelectRect();

    ///绘制Resize的点
    void drawResizeCircles();
};
#endif // SCREENCAPTURE_H
