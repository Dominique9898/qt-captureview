#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include <screenWidget.h>

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
    qDebug() << "--- ToolbarWidget Init ---";

    qDebug() << " parent "<< parent;
    // 坑爹的bug, 工具栏对应的ScreenWidget::Instance的指针与parent指向的不是同一个Widget
    // 导致 grab的x,y,w,h都为0
    m_screenWidget = dynamic_cast<ScreenWidget*>(parent);

    qDebug() << " m_screenWidget "<< m_screenWidget;

    ui->setupUi(this);
    this->hide();
    qDebug() << "--- ToolbarWidget end ---";
}


ToolbarWidget::~ToolbarWidget()
{
    delete ui;
}

Ui::ToolbarWidget* ToolbarWidget::getUi()
{
    return ui;
}

void ToolbarWidget::setPosition(QPoint &bottomRight)
{
    int x = bottomRight.x() - 389;
    int y = bottomRight.y() + 10;
    this->setGeometry(x, y, 389, 38);
}
void ToolbarWidget::unCheckedAllButtons()
{
    ui->rectangleBtn->setChecked(false);
    ui->arrowBtn->setChecked(false);
    ui->drawLineBtn->setCheckable(false);
    ui->drawRoundBtn->setCheckable(false);
    ui->textEditBtn->setCheckable(false);
}
void ToolbarWidget::on_checkBtn_clicked()
{
    m_screenWidget->capture();
}


void ToolbarWidget::on_cancelBtn_clicked()
{
//    ScreenWidget::Instance()->closeCaptureWindows();
}


void ToolbarWidget::on_saveBtn_clicked()
{
//    ScreenWidget::Instance()->saveCapture();
}


void ToolbarWidget::on_rectangleBtn_clicked()
{
    unCheckedAllButtons();
    ui->rectangleBtn->setChecked(true);
//    ScreenWidget::Instance()->setDrawShape(Rectangle);
//    ScreenWidget::Instance()->clearShapes();
}


void ToolbarWidget::on_drawRoundBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawRoundBtn->setChecked(true);
//    ScreenWidget::Instance()->setDrawShape(Round);
//    ScreenWidget::Instance()->clearShapes();
}


void ToolbarWidget::on_drawLineBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawLineBtn->setChecked(true);
//    ScreenWidget::Instance()->setDrawShape(Line);
//    ScreenWidget::Instance()->clearShapes(); // 格式化mShape
}


void ToolbarWidget::on_arrowBtn_clicked()
{
    unCheckedAllButtons();
    ui->arrowBtn->setChecked(true);
//    ScreenWidget::Instance()->setDrawShape(Arrow);
//    ScreenWidget::Instance()->clearShapes();
}


void ToolbarWidget::on_textEditBtn_clicked()
{
    unCheckedAllButtons();
    ui->textEditBtn->setChecked(true);
//    ScreenWidget::Instance()->setDrawShape(Text);
//    ScreenWidget::Instance()->clearShapes();
}


void ToolbarWidget::on_returneditBtn_clicked()
{
//    ScreenWidget::Instance()->undo();

}

