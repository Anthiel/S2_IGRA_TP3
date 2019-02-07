#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect (ui->SliderNear, SIGNAL(valueChanged(int)), this, SLOT(onSliderNear(int)));
    //connect (ui->SliderFar, SIGNAL(valueChanged(int)), this, SLOT(onSliderRadius(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onSliderNear(int value)
{
    qDebug() << __FUNCTION__ << value << sender();
    qDebug() << "  emit Dialog onSliderNear()";
    emit value;
}
