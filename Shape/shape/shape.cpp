#include "shape.h"
#include <QDebug>

Shape::Shape()
{

}

void Shape::setSize(int s_width, int s_height)
{
    qDebug() << "--- init Shape ---";
    qDebug() << "widht = " << s_width << " height " << s_height;

    maxWidth = s_width;
    maxHeight = s_height;
}

void Shape::setStart(QPoint p)
{
    startPoint = p;
}
void Shape::setEnd(QPoint p)
{
    endPoint = p;
    topLeftPoint = startPoint;
    bottomRightPoint = endPoint;
    comparePoint(topLeftPoint, bottomRightPoint);
}
QPoint Shape::getStart()
{
    return startPoint;
}
QPoint Shape::getEnd()
{
    return endPoint;
}

QPoint Shape::getTopLeftPoint()
{
    return topLeftPoint;
}
QPoint Shape::getBottomRightPoint()
{
    return bottomRightPoint;
}
void Shape::setDrawSize(Draw_Size size)
{
    _size = size;
}

void Shape::setDrawColor(Draw_Color color)
{
    _color = color;
}
void Shape::setDrawShape(Draw_Shape shape)
{
    _shape = shape;
}
void Shape::comparePoint(QPoint &topLeftPoint, QPoint &BottomRightPoint)
{
    QPoint l = topLeftPoint;
    QPoint r = bottomRightPoint;

    //mouse move from left -> right
    if (l.x() <= r.x())
    {
       if (l.y() > r.y())
       {
           // bottom-left -> top-right
           topLeftPoint.setY(r.y()); // equal to top-left-point
           bottomRightPoint.setY(l.y()); // equal to bottom-right-point
       }
    }

     // right -> left
    if (l.x() > r.x())
    {
        if(l.y() > r.y())
        {
            QPoint tmp = topLeftPoint;
            topLeftPoint = r;
            bottomRightPoint = tmp;
        } else {
            topLeftPoint.setX(r.x());
            bottomRightPoint.setX(l.x());
        }
    }
}
void Shape::move(QPoint delta_p)
{
        int lx = topLeftPoint.x() + delta_p.x();
        int ly = topLeftPoint.y() + delta_p.y();
        int rx = bottomRightPoint.x() + delta_p.x();
        int ry = bottomRightPoint.y() + delta_p.y();

        // if lx, ly, rx, ry is not a legal value, revert.
        if (lx < 0) {
            lx = 0;
            rx -= delta_p.x();
        }

        if (ly < 0) {
            ly = 0;
            ry -= delta_p.y();
        }

        if (rx > maxWidth)  {
            rx = maxWidth;
            lx -= delta_p.x();
        }

        if (ry > maxHeight) {
            ry = maxHeight;
            ly -= delta_p.y();
        }

        topLeftPoint = QPoint(lx, ly);
        bottomRightPoint = QPoint(rx, ry);
        startPoint = topLeftPoint;
        endPoint = bottomRightPoint;
}
void Shape::resize(QPoint delta_p, int m_activeSide) {
    // todo
    m_activeSide = MouseType(m_activeSide);
    int lx = topLeftPoint.x();
    int ly = topLeftPoint.y();
    int rx = bottomRightPoint.x();
    int ry = bottomRightPoint.y();


    switch (m_activeSide) {
            case TOPLEFT_SIDE:
            lx += delta_p.x();
            ly += + delta_p.y();
                break;
            case TOP_SIDE:
            ly += + delta_p.y();
                break;
            case TOPRIGHT_SIDE:
            ly += + delta_p.y();
            rx += + delta_p.x();
                break;

            case LEFT_SIDE:
            lx += delta_p.x();
                break;
            case RIGHT_SIDE:
            rx += delta_p.x();
                break;

            case BOTTOMLEFT_SIDE:
            lx += delta_p.x();
            ry += + delta_p.y();
                break;
            case BOTTOM_SIDE:
            ry += delta_p.y();
                break;
            case BOTTOMRIGHT_SIDE:
            rx += delta_p.x();
            ry += delta_p.y();
                break;
            default:
                break;
        }


    topLeftPoint = QPoint(lx, ly);
    bottomRightPoint = QPoint(rx, ry);
    startPoint = topLeftPoint;
    endPoint = bottomRightPoint;
}
void Shape::clear()
{
    startPoint.setX(0);
    startPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);
    topLeftPoint = startPoint;
    bottomRightPoint = endPoint;
}
bool Shape::isInArea(QPoint p)
{
    if (p.x() > topLeftPoint.x() && p.x() < bottomRightPoint.x() && p.y() > topLeftPoint.y() && p.y() < bottomRightPoint.y()) {
            return true;
    }

   return false;
}

