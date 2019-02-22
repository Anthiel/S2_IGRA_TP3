#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);    
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setInfo(float radius, float Near, float  Far, float DistCam, float Angle){
    ui->SliderRadius->setValue(radius*20);
    ui->SliderNear->setValue(Near*10);
    ui->SliderFar->setValue(Far*10);
    ui->SliderDistCam->setValue(DistCam*10);
    ui->SliderAngle->setValue(Angle);
}

void Dialog::on_SliderRadius_valueChanged(int value)
{
    emit SliderRadiusChanged(value);
}

void Dialog::on_SliderNear_valueChanged(int value)
{
    emit SliderNearChanged(value);
}

void Dialog::on_SliderFar_valueChanged(int value)
{
    emit SliderFarChanged(value);
}

void Dialog::on_SliderDistCam_valueChanged(int value)
{
    qDebug() << "DistCam" << value/10.0;
    emit SliderZChanged(value);
}

void Dialog::on_SliderAngle_valueChanged(int value)
{
    qDebug() << "Angle" << value;
    emit SliderAngleChanged(value);
}
