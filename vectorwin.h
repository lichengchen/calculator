#ifndef VECTORWIN_H
#define VECTORWIN_H

#include <QWidget>

namespace Ui {
class VectorWin;
}

class VectorWin : public QWidget
{
    Q_OBJECT

public:
    explicit VectorWin(QWidget *parent = 0);
    ~VectorWin();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_Go_clicked();

private:
    Ui::VectorWin *ui;
};

#endif // VECTORWIN_H
