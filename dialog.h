#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "glarea.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setInfo(GLArea *gl, float radius, float Near, float Far, float DistCam, float Angle);
    void keyPressEvent(QKeyEvent *ev);
    ~Dialog();

signals:
    void SliderRadiusChanged(int value);
    void SliderNearChanged(int value);
    void SliderFarChanged(int value);
    void SliderZChanged(int value);
    void SliderAngleChanged(int value);
    void StartSignal();
    void StopSignal();


private slots:
    void on_SliderRadius_valueChanged(int value);
    void on_SliderNear_valueChanged(int value);
    void on_SliderFar_valueChanged(int value);
    void on_SliderDistCam_valueChanged(int value);
    void on_SliderAngle_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    GLArea *glA;
};

#endif // DIALOG_H
