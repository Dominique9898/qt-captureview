#ifndef SHAPE_H
#include<QPoint>
#define SHAPE_H
typedef enum Size
{
    Small = 1,
    Middle = 3,
    Large = 5
}Draw_Size;

typedef enum Color
{
    Red,
    Yellow,
    Blue,
    Green,
    Gray,
    White
}Draw_Color;

typedef enum Paintings
{
    Rectangle,
    Round,
    Arrow,
    Line,
    Text,
    Mosaic
}Draw_Shape;

enum MouseType {
    TOPLEFT_SIDE, // SizeFDiagCursor
    TOP_SIDE, //  SizeVerCursor
    TOPRIGHT_SIDE, // SizeBDiagCursor

    LEFT_SIDE, // SizeHorCursor
    RIGHT_SIDE, // SizeHorCursor

    BOTTOMLEFT_SIDE, // SizeBDiagCursor
    BOTTOM_SIDE, // SizeVerCursor
    BOTTOMRIGHT_SIDE, // SizeFDiagCursor,
};

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
    void resize(QPoint delta_p, int m_activeSide);
    void move(QPoint delta_p);

    void setSize(int s_width, int s_height);
    void setDrawSize(Draw_Size size);
    void setDrawColor(Draw_Color color);
    void setDrawShape(Draw_Shape shape);
    void clear();

    /// 改变鼠标样式
    void updateCursor();

private:
    Draw_Size _size;
    Draw_Color _color;
    Draw_Shape _shape;
    int maxWidth;
    int maxHeight;
    QPoint startPoint;
    QPoint endPoint;
    QPoint topLeftPoint;
    QPoint bottomRightPoint;
    void comparePoint(QPoint &topLeftPoint, QPoint &BottomRightPoint);

};

#endif // SHAPE_H
