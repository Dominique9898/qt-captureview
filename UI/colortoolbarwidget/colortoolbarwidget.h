#ifndef COLORTOOLBARWIDGET_H
#define COLORTOOLBARWIDGET_H

#include <QWidget>

namespace Ui {
class ColorToolbarWidget;
}

class ColorToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorToolbarWidget(QWidget *parent = nullptr);
    ~ColorToolbarWidget();

    Ui::ColorToolbarWidget* getUi();
    void setPosition(QPoint &bottomRight);
    void uncheckAllColor();
    void uncheckAllSize();

private slots:
    void on_pushButtonLarge_clicked();

    void on_pushButtonBlue_clicked();

    void on_pushButtonGray_clicked();

    void on_pushButtonGreen_clicked();

    void on_pushButtonMiddle_clicked();

    void on_pushButtonRed_clicked();

    void on_pushButtonSmall_clicked();

    void on_pushButtonWhite_clicked();

    void on_pushButtonYellow_clicked();

private:
    Ui::ColorToolbarWidget *ui;

};

#endif // COLORTOOLBARWIDGET_H
