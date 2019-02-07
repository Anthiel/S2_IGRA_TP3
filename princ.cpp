// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "princ.h"
#include "dialog.h"
#include <QDebug>

Princ::Princ(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    connect (glarea, SIGNAL(radiusChanged(double)), this, SLOT(setSliderRadius(double)));
    connect (sli_radius, SIGNAL(valueChanged(int)), this, SLOT(onSliderRadius(int)));
}


void Princ::setSliderRadius(double radius)
{
    qDebug() << __FUNCTION__ << radius << sender();
    int value = radius*20;
    if (sli_radius->value() != value) {
        qDebug() << "  sli_radius->setvalue()";
        sli_radius->setValue(value);
    }
}

void Princ::onSliderRadius(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit radiusChanged()";
    emit glarea->radiusChanged(value/20.0);
}

void Princ::onSliderNear(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit PRINC SliderNear()";
    emit onSliderNear(value);
}


void Princ::on_pushButton_clicked()
{
    Dialog dia;
    if(dia.exec()){
        connect(&dia, SIGNAL(onSliderNear(int)),this, SLOT(onSliderNear(int)));
    }
}
