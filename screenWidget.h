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
#define SCREENCAPTURE_H


class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    ScreenWidget(QWidget *parent = nullptr);
    ~ScreenWidget();

    // 创建窗口单例
    static ScreenWidget *Instance();

    static void destroy();
    void startCapture(int id);
    void setScreen(QScreen* screen);

signals:
    void lastWindowClosed();

private:
    // 初始化截图窗口(窗口类型, 状态, 边框)
    void initCaptureWindow();

private:
    static ScreenWidget* self;
    static bool isActivity;
    int screenId;
    int s_width;
    int s_height;
    int s_x;
    int s_y;

    // captureWin 对应的screen
    QScreen* w_screen;

    // 当前桌面屏幕的矩形数据
    QRect desktopRect;

    // 屏幕暗色背景图
    QPixmap    grayBackgroundScreen;

    // 屏幕原画
    QPixmap    originBackgroundScreen;


//protected:
//        /**
//         * @brief : 隐藏窗口事件
//         */
//        virtual void hideEvent(QHideEvent *);
//        /**
//         * @brief : 关闭窗口事件
//         */
//        virtual void closeEvent(QCloseEvent *);
//        /**
//         * @brief : 双击事件
//         */
//        virtual void mouseDoubleClickEvent(QMouseEvent*);
//        /**
//         * @brief : 鼠标按下事件
//         */
//        virtual void mousePressEvent(QMouseEvent *);
//        /**
//         * @brief : 鼠标释放事件
//         */
//        virtual void mouseReleaseEvent(QMouseEvent *e);
//        /**
//         * @brief : 鼠标移动事件
//         */
//        virtual void mouseMoveEvent(QMouseEvent *e);

        /**
         * @brief : 按键按下事件
         */
        virtual void keyPressEvent(QKeyEvent*);

//        /**
//         * @brief : 自绘事件
//         */
//        virtual void paintEvent(QPaintEvent *);

private:

    // 获得屏幕的原画
    void initOriginBackgroundScreen();

    // 获得暗色处理的屏幕图
    void initGrayBackgroundScreen();

    // 获得当前屏幕的大小
    const QRect& getScreenRect();

    void closeCaptureWindows();
};
#endif // SCREENCAPTURE_H
