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
    void setPosition(int x, int y, int width, int height);

private:

    static SelectWidget* self;

    // 拉取后的选区位置
    QRect rect;
    QGraphicsScene scene;
    QGraphicsView view;

protected:
    virtual void paintEvent(QPaintEvent *);


};

#endif // SELECTWIDGET_H
