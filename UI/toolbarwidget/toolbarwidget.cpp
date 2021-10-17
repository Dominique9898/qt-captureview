#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
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
//    std::cout<<"on_checkBtn_clicked"<<endl;
//    ScreenCapture::Instance()->capture();
}


void ToolbarWidget::on_cancelBtn_clicked()
{
//    ScreenCapture::Instance()->close();
}


void ToolbarWidget::on_saveBtn_clicked()
{
//    ScreenCapture::Instance()->saveCapture();
//    ScreenCapture::Instance()->close();
}


void ToolbarWidget::on_rectangleBtn_clicked()
{
    unCheckedAllButtons();
    ui->rectangleBtn->setChecked(true);
//    ScreenCapture::Instance()->setDrawShape(Rectangle);
//    ScreenCapture::Instance()->clearShapes();
}


void ToolbarWidget::on_drawRoundBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawRoundBtn->setChecked(true);
//    ScreenCapture::Instance()->setDrawShape(Round);
//    ScreenCapture::Instance()->clearShapes();
}


void ToolbarWidget::on_drawLineBtn_clicked()
{
    unCheckedAllButtons();
    ui->drawLineBtn->setChecked(true);
//    ScreenCapture::Instance()->setDrawShape(Line);
//    ScreenCapture::Instance()->clearShapes(); // 格式化mShape
}


void ToolbarWidget::on_arrowBtn_clicked()
{
    unCheckedAllButtons();
    ui->arrowBtn->setChecked(true);
//    ScreenCapture::Instance()->setDrawShape(Arrow);
//    ScreenCapture::Instance()->clearShapes();
}


void ToolbarWidget::on_textEditBtn_clicked()
{
    unCheckedAllButtons();
    ui->textEditBtn->setChecked(true);
//    ScreenCapture::Instance()->setDrawShape(Text);
//    ScreenCapture::Instance()->clearShapes();
}


void ToolbarWidget::on_returneditBtn_clicked()
{
//    ScreenCapture::Instance()->undo();

}

