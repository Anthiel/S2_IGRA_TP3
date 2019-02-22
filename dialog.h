#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setInfo(float radius, float Near, float Far, float DistCam, float Angle);
    ~Dialog();

signals:
    void SliderRadiusChanged(int value);
    void SliderNearChanged(int value);
    void SliderFarChanged(int value);
    void SliderZChanged(int value);
    void SliderAngleChanged(int value);


private slots:
    void on_SliderRadius_valueChanged(int value);
    void on_SliderNear_valueChanged(int value);

    void on_SliderFar_valueChanged(int value);

    void on_SliderDistCam_valueChanged(int value);

    void on_SliderAngle_valueChanged(int value);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
