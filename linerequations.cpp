#include "linerequations.h"
#include "ui_linerequations.h"
#include "common.h"
#include "QDebug"

LinerEquations::LinerEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinerEquations)
{
    ui->setupUi(this);
    setWindowTitle("线性方程组求解器");
    ui->tableWidget_A->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_A->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_b->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_b->horizontalHeader()->setDefaultSectionSize(40);
    update();
}

LinerEquations::~LinerEquations()
{
    delete ui;
}

void LinerEquations::on_spinBox_y_valueChanged(int arg1)
{
    ui->tableWidget_A->setColumnCount(arg1);
    update();
    ui->textBrowser_2->clear();
}

void LinerEquations::on_spinBox_x_valueChanged(int arg1)
{
    ui->tableWidget_A->setRowCount(arg1);
    ui->tableWidget_b->setRowCount(arg1);
    update();
    ui->textBrowser_2->clear();
}

void LinerEquations::update()
{
    ui->textBrowser->clear();
    int x=ui->spinBox_x->value();
    int y=ui->spinBox_y->value();

    int flag=1; //是否输入合规可以计算的标志

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(j!=0){
                ui->textBrowser->setTextColor(Qt::black);
                ui->textBrowser->insertPlainText(" + ");
            }
            if(!ui->tableWidget_A->item(i,j)||isDigitStr(ui->tableWidget_A->item(i,j)->text())==false){
                ui->textBrowser->setTextColor(Qt::red);
                ui->textBrowser->insertPlainText("?");

                flag=0;
            }
            else{
                ui->textBrowser->setTextColor(Qt::blue);
                ui->textBrowser->insertPlainText(ui->tableWidget_A->item(i,j)->text());
            }
            ui->textBrowser->setTextColor(Qt::black);
            ui->textBrowser->insertPlainText(" * x");
            ui->textBrowser->insertPlainText(QString::number(j+1));
        }
        ui->textBrowser->setTextColor(Qt::black);
        ui->textBrowser->insertPlainText(" = ");

        if(!ui->tableWidget_b->item(i,0)||isDigitStr(ui->tableWidget_b->item(i,0)->text())==false){
            ui->textBrowser->setTextColor(Qt::red);
            ui->textBrowser->insertPlainText("?");

            flag=0;
        }
        else{
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->insertPlainText(ui->tableWidget_b->item(i,0)->text());
        }
        ui->textBrowser->append("");
    }


    if(flag==0){
        ui->pushButton_Go->setEnabled(false);
        ui->label_8->setText("将所有需要的信息（可在预览中查看）填充完毕才可以计算");
    }

    else{
        ui->pushButton_Go->setEnabled(true);
        ui->label_8->setText("点击计算来求解方程组");
    }
}

void LinerEquations::on_tableWidget_A_cellChanged()
{
    update();
    ui->textBrowser_2->clear();
}

void LinerEquations::on_tableWidget_b_cellChanged()
{
    update();
    ui->textBrowser_2->clear();
}

void LinerEquations::on_pushButton_ResetAll_clicked()
{
    ui->tableWidget_A->clear();
    ui->tableWidget_A->setRowCount(1);
    ui->tableWidget_A->setColumnCount(1);

    ui->tableWidget_b->clear();
    ui->tableWidget_b->setRowCount(1);
    ui->tableWidget_b->setColumnCount(1);

    ui->textBrowser->clear();
    ui->textBrowser_2->clear();

    ui->spinBox_x->setValue(1);
    ui->spinBox_y->setValue(1);
    update();
}

void LinerEquations::on_pushButton_Go_clicked()
{
    int x=ui->spinBox_x->value();
    int y=ui->spinBox_y->value();

    //初始化： A、b、A的增广Ab、空的空间tAb
    int **A=new int *[x];
    for(int i=0;i<x;i++){
        A[i]=new int [y];
        for(int j=0;j<y;j++){
            A[i][j]=ui->tableWidget_A->item(i,j)->text().toInt();
        }
    }
    int *b=new int[x];
    for(int i=0;i<x;i++){
        b[i]=ui->tableWidget_b->item(i,0)->text().toInt();
    }
    int **tAb=new int *[x];
    for(int i=0;i<x;i++){
        tAb[i]=new int [y+1];
    }
    int **Ab=new int *[x];
    for(int i=0;i<x;i++){
        Ab[i]=new int [y+1];
        for(int j=0;j<y;j++){
            Ab[i][j]=ui->tableWidget_A->item(i,j)->text().toInt();
        }
        Ab[i][y]=ui->tableWidget_b->item(i,0)->text().toInt();
    }
    //初始化完毕

    int r=rank(A,tAb,x,y);

    if(r!=rank(Ab,tAb,x,y+1)){    //有解的充要条件是系数矩阵和增广矩阵同秩
        ui->textBrowser_2->setTextColor(Qt::red);
        ui->textBrowser_2->setText("方程组无解");
    }
    else{
        if(r<y){   //有无穷多解
            ui->textBrowser_2->setTextColor(Qt::blue);
            ui->textBrowser_2->setText("方程组有无穷多解 --- 一个特解如下：");
        }
        else{
            ui->textBrowser_2->setTextColor(Qt::blue);
            ui->textBrowser_2->setText("方程组有唯一解:");
        }
        if(true){       //求具体解的方法过于繁琐，这里直接调库函数了
            MatrixXf m_A(x,y);
            MatrixXf m_b(x,1);
            for(int i=0;i<x;i++){
                m_b(i,0)=b[i];
                for(int j=0;j<y;j++){
                    m_A(i,j)=A[i][j];
                }
            }
            MatrixXf m_r(y,1);
            m_r=m_A.fullPivHouseholderQr().solve(m_b);
            for(int i=0;i<y;i++){
                ui->textBrowser_2->setTextColor(Qt::black);
                ui->textBrowser_2->append("x"+QString::number(i+1)+" = "+QString::number(m_r(i,0)));
            }
        }
    }

    for(int i=0;i<x;i++){
        delete A[i];
    }
    delete A;
    delete [] b;

    ui->label_8->setText("计算完毕");
}
