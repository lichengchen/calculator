#ifndef SINGLEMATRIX_H
#define SINGLEMATRIX_H

#include <QWidget>

namespace Ui {
class SingleMatrix;
}

class SingleMatrix : public QWidget
{
    Q_OBJECT

public:
    explicit SingleMatrix(QWidget *parent = 0);
    ~SingleMatrix();

private slots:
    void on_pushButton_RowAdd_clicked();

    void on_pushButton_ColumnAdd_clicked();

    void on_pushButton_RowSub_clicked();

    void on_pushButton_ColumnSub_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_Go_clicked();

    void on_checkBox_power_stateChanged();

private:
    Ui::SingleMatrix *ui;
};

#endif // SINGLEMATRIX_H
