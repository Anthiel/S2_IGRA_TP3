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
    glarea->radiusChanged(value/20.0);
}

void Princ::onSliderNear(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit PRINC SliderNear()";
    glarea->setNear(value/10.0);
    update();
}

void Princ::onSliderFar(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit PRINC SliderFar()";
    glarea->setFar(value/10.0);
    update();
}

void Princ::onSliderZ(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit PRINC SliderZ()";
    glarea->set_mz(value/10.0);
    update();
}

void Princ::onSliderAngle(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit PRINC SliderAngle()";
    glarea->set_mAngle(value);
    update();
}

void Princ::on_pushButton_clicked()
{
    Dialog dia;
    connect(&dia, SIGNAL(SliderRadiusChanged(int)),this, SLOT(onSliderRadius(int)));
    connect(&dia, SIGNAL(SliderNearChanged(int)),this, SLOT(onSliderNear(int)));
    connect(&dia, SIGNAL(SliderFarChanged(int)),this, SLOT(onSliderFar(int)));
    connect(&dia, SIGNAL(SliderZChanged(int)),this, SLOT(onSliderZ(int)));
    connect(&dia, SIGNAL(SliderAngleChanged(int)),this, SLOT(onSliderAngle(int)));
    dia.setInfo(glarea->getRadius(), glarea->getNear(), glarea->getFar(), glarea->get_mz(), glarea->get_mAngle());

    if(dia.exec()){
    }

}
