#ifndef DOUBLEMATRIX_H
#define DOUBLEMATRIX_H

#include <QWidget>

namespace Ui {
class DoubleMatrix;
}

class DoubleMatrix : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleMatrix(QWidget *parent = 0);
    ~DoubleMatrix();

private slots:
    void on_toolButton_1rowadd_clicked();

    void on_toolButton_1rowsubb_clicked();

    void on_toolButton_1coladd_clicked();

    void on_toolButton_1colsub_clicked();

    void on_toolButton_2rowadd_clicked();

    void on_toolButton_2rowsubb_clicked();

    void on_toolButton_2coladd_clicked();

    void on_toolButton_2colsub_clicked();

    void on_pushButton_Go_clicked();

    void on_pushButton_Reset1_clicked();

    void on_pushButton_Reset2_clicked();

    void on_pushButton_ResetAll_clicked();

private:
    Ui::DoubleMatrix *ui;
};

#endif // DOUBLEMATRIX_H
