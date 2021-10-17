#ifndef SHAPE_H
#include<QPoint>
#define SHAPE_H

class Shape
{
public:
    /// 屏幕的高宽
    Shape();

    void setStart(QPoint p);
    void setEnd(QPoint p);
    QPoint getStart();
    QPoint getEnd();

    QPoint getTopLeftPoint();
    QPoint getBottomRightPoint();
    bool isInArea(QPoint p);
    void move(QPoint delta_p);

    void setSize(int s_width, int s_height);

    /// 改变鼠标样式
    void updateCursor();

private:
    int maxWidth;
    int maxHeight;
    QPoint startPoint;
    QPoint endPoint;
    QPoint topLeftPoint;
    QPoint bottomRightPoint;
    void comparePoint(QPoint &topLeftPoint, QPoint &BottomRightPoint);


};

#endif // SHAPE_H
