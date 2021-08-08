#ifndef LINEREQUATIONS_H
#define LINEREQUATIONS_H

#include <QWidget>

namespace Ui {
class LinerEquations;
}

class LinerEquations : public QWidget
{
    Q_OBJECT

public:
    explicit LinerEquations(QWidget *parent = 0);
    ~LinerEquations();

private slots:
    void on_spinBox_y_valueChanged(int arg1);

    void on_spinBox_x_valueChanged(int arg1);

    void on_tableWidget_A_cellChanged();

    void on_tableWidget_b_cellChanged();

    void on_pushButton_ResetAll_clicked();

    void on_pushButton_Go_clicked();

private:
    Ui::LinerEquations *ui;

    void update();
};

#endif // LINEREQUATIONS_H
