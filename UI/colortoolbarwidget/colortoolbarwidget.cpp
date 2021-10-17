#include "colortoolbarwidget.h"
#include "ui_colortoolbarwidget.h"

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
//    ScreenCapture::Instance()->setDrawSize(Small);
//    ScreenCapture::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonMiddle_clicked()
{
    uncheckAllSize();
    ui->pushButtonMiddle->setChecked(true);
//    ScreenCapture::Instance()->setDrawSize(Middle);
//    ScreenCapture::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonLarge_clicked()
{
    uncheckAllSize();
    ui->pushButtonLarge->setChecked(true);
//    ScreenCapture::Instance()->setDrawSize(Large);
//    ScreenCapture::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonBlue_clicked()
{
    uncheckAllColor();
    ui->pushButtonBlue->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(Blue);
//    ScreenCapture::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonGray_clicked()
{
    uncheckAllColor();
    ui->pushButtonGray->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(Gray);
//    ScreenCapture::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonGreen_clicked()
{
    uncheckAllColor();
    ui->pushButtonGreen->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(Green);
//    ScreenCapture::Instance()->clearShapes();
}

void ColorToolbarWidget::on_pushButtonRed_clicked()
{
    uncheckAllColor();
    ui->pushButtonRed->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(Red);
//    ScreenCapture::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonWhite_clicked()
{
    uncheckAllColor();
    ui->pushButtonWhite->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(White);
//    ScreenCapture::Instance()->clearShapes();
}


void ColorToolbarWidget::on_pushButtonYellow_clicked()
{
    uncheckAllColor();
    ui->pushButtonYellow->setChecked(true);
//    ScreenCapture::Instance()->setDrawColor(Yellow);
//    ScreenCapture::Instance()->clearShapes();
}

