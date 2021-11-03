#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include <screenWidget.h>

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{

    qDebug() << " parent "<< parent;
    // 坑爹的bug, 工具栏对应的ScreenWidget::Instance的指针与parent指向的不是同一个Widget
    // 导致 grab的x,y,w,h都为0
    m_screenWidget = dynamic_cast<ScreenWidget*>(parent);

    ui->setupUi(this);
    this->hide();
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
    m_screenWidget->closeCaptureWindows();
}


void ToolbarWidget::on_saveBtn_clicked()
{
    m_screenWidget->saveCapture();
}


void ToolbarWidget::on_rectangleBtn_clicked()
{
    unCheckedAllButtons();
    ui->rectangleBtn->setChecked(true);
    m_screenWidget->setDrawShape(Rectangle);
    m_screenWidget->clearShapes();
}


void ToolbarWidget::on_drawRoundBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawRoundBtn->setChecked(true);
    m_screenWidget->setDrawShape(Round);
    m_screenWidget->clearShapes();
}


void ToolbarWidget::on_drawLineBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawLineBtn->setChecked(true);
    m_screenWidget->setDrawShape(Line);
    m_screenWidget->clearShapes(); // 格式化mShape
}


void ToolbarWidget::on_arrowBtn_clicked()
{
    unCheckedAllButtons();
    ui->arrowBtn->setChecked(true);
    m_screenWidget->setDrawShape(Arrow);
    m_screenWidget->clearShapes();
}


void ToolbarWidget::on_textEditBtn_clicked()
{
    unCheckedAllButtons();
    ui->textEditBtn->setChecked(true);
    m_screenWidget->setDrawShape(Text);
    m_screenWidget->clearShapes();
}


void ToolbarWidget::on_returneditBtn_clicked()
{
//    m_screenWidget->undo();
}

