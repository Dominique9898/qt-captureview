#include "colortoolbarwidget.h"
#include "ui_colortoolbarwidget.h"
#include <screenWidget.h>

ColorToolbarWidget::ColorToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorToolbarWidget)
{
    ui->setupUi(this);
    this->hide();
    ui->pushButtonSmall->setChecked(true);
    ui->pushButtonRed->setChecked(true);
}

ColorToolbarWidget::~ColorToolbarWidget()
{
    delete ui;
}

Ui::ColorToolbarWidget* ColorToolbarWidget::getUi()
{
    return ui;
}
void ColorToolbarWidget::setPosition(QPoint &bottomRight)
{
    int x = bottomRight.x() - 389;
    int y = bottomRight.y() + 58;
    this->setGeometry(x, y, 245, 38);
}
void ColorToolbarWidget::uncheckAllSize()
{
    ui->pushButtonSmall->setChecked(false);
    ui->pushButtonMiddle->setChecked(false);
    ui->pushButtonLarge->setChecked(false);
}
void ColorToolbarWidget::uncheckAllColor()
{
    ui->pushButtonRed->setChecked(false);
    ui->pushButtonBlue->setChecked(false);
    ui->pushButtonGreen->setChecked(false);
    ui->pushButtonGray->setChecked(false);
    ui->pushButtonWhite->setChecked(false);
    ui->pushButtonYellow->setChecked(false);
}
void ColorToolbarWidget::on_pushButtonSmall_clicked()
{
    uncheckAllSize();
    ui->pushButtonSmall->setChecked(true);
    ScreenWidget::Instance()->setDrawSize(Small);
//    ScreenWidget::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonMiddle_clicked()
{
    uncheckAllSize();
    ui->pushButtonMiddle->setChecked(true);
    ScreenWidget::Instance()->setDrawSize(Middle);
//    ScreenWidget::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonLarge_clicked()
{
    uncheckAllSize();
    ui->pushButtonLarge->setChecked(true);
    ScreenWidget::Instance()->setDrawSize(Large);
//    ScreenWidget::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonBlue_clicked()
{
    uncheckAllColor();
    ui->pushButtonBlue->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(Blue);
//    ScreenWidget::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonGray_clicked()
{
    uncheckAllColor();
    ui->pushButtonGray->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(Gray);
//    ScreenWidget::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonGreen_clicked()
{
    uncheckAllColor();
    ui->pushButtonGreen->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(Green);
//    ScreenWidget::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonRed_clicked()
{
    uncheckAllColor();
    ui->pushButtonRed->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(Red);
//    ScreenWidget::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonWhite_clicked()
{
    uncheckAllColor();
    ui->pushButtonWhite->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(White);
//    ScreenWidget::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonYellow_clicked()
{
    uncheckAllColor();
    ui->pushButtonYellow->setChecked(true);
    ScreenWidget::Instance()->setDrawColor(Yellow);
//    ScreenWidget::Instance()->clearShapes();
}

