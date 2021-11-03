#ifndef SELECTWIDGET_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainterPath>
#include <QGraphicsPixmapItem>
#include <QDebug>
#define SELECTWIDGET_H


class SelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectWidget(QWidget *parent = nullptr);

    static SelectWidget* Instance();
    bool isShow();
    void Show(int sx, int sy, int w, int h);
    void Hide();

private:

    static SelectWidget* self;
    bool _show;

    // 拉取后的选区位置
    QRect rect;
    QGraphicsScene scene;
    QGraphicsView view;
    QPainterPath path;

protected:
    virtual void paintEvent(QPaintEvent *);


};

#endif // SELECTWIDGET_H
