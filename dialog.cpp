#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QKeyEvent>
#include "glarea.h"

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


void Dialog::setInfo(GLArea *gl, float radius, float Near, float  Far, float DistCam, float Angle){
    glA = gl;
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



void Dialog::on_pushButton_clicked()
{
    emit StartSignal();
}

void Dialog::on_pushButton_2_clicked()
{
     emit StopSignal();
}


void Dialog::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();

    switch(ev->key()) {

        case Qt::Key_G :
            if (glA->m_timer->isActive()){
                glA->m_timer->stop();
            }
            else{
                glA->m_timer->start();
            }
            break;
        case Qt::Key_R :
            if (ev->text() == "r")
                 glA->setRadius(glA->m_radius-0.05f);
            else glA->setRadius(glA->m_radius+0.05f);
            break;
        case Qt::Key_Z :
            if (ev->text() == "z"){
                glA->m_z+=0.1f;
                glA->update();
            }
            else{
                glA->m_z-=0.1f;
                glA->update();
            }
            break;

        case Qt::Key_N :
            if (ev->text() == "n"){
                glA->nearValue+=1;
                glA->update();
            }
            else{
                glA->nearValue-=1;
                glA->update();
            }
            break;

        case Qt::Key_F :
            if (ev->text() == "f"){
                glA->farvalue+=1;
                glA->update();
            }
            else{
                glA->farvalue-=1;
                glA->update();
            }
            break;

        case Qt::Key_A :
            if (ev->text() == "a"){
                glA->m_angle += 1;
                if (glA->m_angle >= 360) glA->m_angle -= 360;
                glA->update();
            }
            else{
                glA->m_angle -= 1;
                if (glA->m_angle <= -1) glA->m_angle += 360;
                glA->update();
            }
            break;

    }
    qDebug() << "NEAR : " << glA->getNear();
    setInfo(glA, glA->getRadius(), glA->getNear(), glA->getFar(), glA->get_mz(), glA->get_mAngle());
    qDebug() << "NEAR2 : " << glA->getNear();
}
