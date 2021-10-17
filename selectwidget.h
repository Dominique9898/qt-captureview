#ifndef SELECTWIDGET_H
#include <QWidget>
#define SELECTWIDGET_H


class selectWidget : public QWidget
{
    Q_OBJECT
public:
    selectWidget();
    void setGeometryAnimated(const QRect& r);
    void setGeometry(const QRect& r);
    QRect geometry() const;

protected:
    bool eventFilter(QObject*, QEvent*) override;
    void parentMousePressEvent(QMouseEvent* e);
    void parentMouseReleaseEvent(QMouseEvent* e);
    void parentMouseMoveEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void moveEvent(QMoveEvent*);

    void showEvent(QShowEvent*) override;
    void hideEvent(QHideEvent*) override;
};

#endif // SELECTWIDGET_H
