#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "singlematrix.h"
#include "doublematrix.h"
#include "vectorwin.h"
#include "linerequations.h"
#include <QButtonGroup>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("线性代数助手");
    ui->textBrowser->setEnabled(false);
    ui->textBrowser->setText("鼠标放到按钮上来查看说明");
    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_3->installEventFilter(this);
    ui->pushButton_4->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->centralWidget=new SingleMatrix;
    ui->centralWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->centralWidget=new DoubleMatrix;
    ui->centralWidget->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->centralWidget=new VectorWin;
    ui->centralWidget->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->centralWidget=new LinerEquations;
    ui->centralWidget->show();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->pushButton == watched || ui->pushButton_2 == watched|| ui->pushButton_3 == watched|| ui->pushButton_4 == watched) {
        if(QEvent::Enter == event->type()) {            //鼠标进入
            if(ui->pushButton == watched){
                ui->textBrowser->setText("计算一个矩阵的：");
                ui->textBrowser->append("行列式");
                ui->textBrowser->append("秩");
                ui->textBrowser->append("行最简形矩阵（上三角）");
                ui->textBrowser->append("逆矩阵");
                ui->textBrowser->append("整数次幂");
            }
            else if(ui->pushButton_2 == watched){
                ui->textBrowser->setText("计算两个矩阵的：");
                ui->textBrowser->append("积");
                ui->textBrowser->append("和");
                ui->textBrowser->append("差");
            }
            else if(ui->pushButton_3 == watched){
                ui->textBrowser->setText("计算向量的：");
                ui->textBrowser->append("模");
                ui->textBrowser->append("数量积(内积)");
            }

            else if(ui->pushButton_4 == watched){
                ui->textBrowser->setText("解形如：");
                ui->textBrowser->append("Ax=b");
                ui->textBrowser->append("的线性方程组");
            }
        }
        else if (QEvent::Leave == event->type()) { //鼠标离开
            ui->textBrowser->setText("鼠标放到按钮上来查看说明");
        }
    }
    return QWidget::eventFilter(watched, event);
}
