#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
class ScreenCapture;

namespace Ui {
class ToolbarWidget;
}

class ToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent = nullptr);
    ~ToolbarWidget();

    void setPosition(QPoint &bottomRight);
    void unCheckedAllButtons();
    Ui::ToolbarWidget* getUi();

private slots:


    void on_checkBtn_clicked();

    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

    void on_rectangleBtn_clicked();

    void on_drawRoundBtn_clicked();

    void on_drawLineBtn_clicked();

    void on_arrowBtn_clicked();

    void on_textEditBtn_clicked();

    void on_returneditBtn_clicked();

private:
    Ui::ToolbarWidget *ui;
};

#endif // TOOLBARWIDGET_H
