#ifndef TOOLBARWIDGET_H
#include <QDebug>
#include <QWidget>
#define TOOLBARWIDGET_H

class ScreenWidget;
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
    ScreenWidget* m_screenWidget;


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

    bool _show;
};

#endif // TOOLBARWIDGET_H
