#include "singlematrix.h"
#include "ui_singlematrix.h"
#include "common.h"

SingleMatrix::SingleMatrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleMatrix)
{
    ui->setupUi(this);
    ui->label_rowNum->setText(QString::number(ui->tableWidget->rowCount()));
    ui->label_columnNum->setText(QString::number(ui->tableWidget->columnCount()));

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(50);
    ui->lineEdit->setEnabled(false);
}

SingleMatrix::~SingleMatrix()
{
    delete ui;
}

void SingleMatrix::on_pushButton_RowAdd_clicked()
{
    int i=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(i+1);
    ui->label_rowNum->setText(QString::number(i+1));
}

void SingleMatrix::on_pushButton_RowSub_clicked()
{
    int i=ui->tableWidget->rowCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少行数#");
        return;
    }
    ui->tableWidget->setRowCount(i-1);
    ui->label_rowNum->setText(QString::number(i-1));
}

void SingleMatrix::on_pushButton_ColumnAdd_clicked()
{
    int i=ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(i+1);
    ui->label_columnNum->setText(QString::number(i+1));
}

void SingleMatrix::on_pushButton_ColumnSub_clicked()
{
    int i=ui->tableWidget->columnCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少列数#");
        return;
    }
    ui->tableWidget->setColumnCount(i-1);
    ui->label_columnNum->setText(QString::number(i-1));
}

void SingleMatrix::on_pushButton_Reset_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(2);
    ui->label_rowNum->setText(QString::number(ui->tableWidget->rowCount()));
    ui->label_columnNum->setText(QString::number(ui->tableWidget->columnCount()));
    ui->textBrowser->clear();
}

void SingleMatrix::on_pushButton_Go_clicked()
{
    ui->textBrowser->clear();

    if(isMatrixAvailable(ui->tableWidget)==false){
        ui->textBrowser->setText("#无法计算--矩阵信息缺失或无效#");
        return;
    }
    if(ui->checkBox_det->isChecked()==false && ui->checkBox_rank->isChecked()==false && ui->checkBox_inverse->isChecked()==false && ui->checkBox_power->isChecked()==false){
        ui->textBrowser->setText("#无法计算--没有勾选的计算选项#");
        return;
    }

    //下面计算通用的基本信息
    int x=ui->tableWidget->rowCount();
    int y=ui->tableWidget->columnCount();
    int **m=new int*[x];    //矩阵副本，二维数组，方便后面计算
    for(int i=0;i<x;i++){
        m[i]=new int[y];
        for(int j=0;j<y;j++){
            m[i][j]=ui->tableWidget->item(i,j)->text().toInt();
        }
    }
    //开始计算

    if(ui->checkBox_det->isChecked()){
        ui->textBrowser->setTextColor(Qt::blue);
        ui->textBrowser->append("#行列式---------------------------");
        ui->textBrowser->setTextColor(Qt::black);
        if(x!=y){
            ui->textBrowser->append("非方阵无法计算行列式");
        }
        else{
            ui->textBrowser->append(QString::number(det(m,x)));
        }
    }

    if(ui->checkBox_rank->isChecked()||ui->checkBox_stairs->isChecked()){   //求秩和求阶梯矩阵是相关的。。
        int ** stairs=new int *[x];
        for(int i=0;i<x;i++){
            stairs[i]=new int[y];
        }

        int r=rank(m,stairs,x,y);
        if(ui->checkBox_rank->isChecked()){
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->append("\n#秩--------------------------------");
            ui->textBrowser->setTextColor(Qt::black);
            ui->textBrowser->append(QString::number(r));
        }

        if(ui->checkBox_stairs->isChecked()){
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->append("\n#行最简形矩阵--------------------");
            ui->textBrowser->setTextColor(Qt::red);
            for(int i=0;i<x;i++){
                ui->textBrowser->append("");
                for(int j=0;j<y;j++){
                    ui->textBrowser->insertPlainText(QString::number(stairs[i][j])+"    ");
                }
            }
            ui->textBrowser->setTextColor(Qt::black);
        }

        for(int i=0;i<x;i++){
            delete[] stairs[i];
        }
        delete stairs;
    }

    if(ui->checkBox_inverse->isChecked()){
        ui->textBrowser->setTextColor(Qt::blue);
        ui->textBrowser->append("\n#逆---------------------------------");
        ui->textBrowser->setTextColor(Qt::black);
        if(x!=y){
            ui->textBrowser->append("无法计算逆矩阵--非方阵");
        }
        else if(det(m,x)==0){
            ui->textBrowser->append("无法计算逆矩阵--矩阵不可逆");
        }
        else{
            double ** r=new double *[x];
            for(int i=0;i<x;i++){
                r[i]=new double[y];
            }

            inverse(m,r,x);

            ui->textBrowser->setTextColor(Qt::red);
            for(int i=0;i<x;i++){
                ui->textBrowser->append("");
                for(int j=0;j<y;j++){
                    ui->textBrowser->insertPlainText(QString::number(r[i][j])+"    ");
                }
            }
            ui->textBrowser->setTextColor(Qt::black);

            for(int i=0;i<x;i++){
                delete[] r[i];
            }
            delete r;
        }
    }

    if(ui->checkBox_power->isChecked()){
        ui->textBrowser->setTextColor(Qt::blue);
        ui->textBrowser->append("\n#幂---------------------------------");
        ui->textBrowser->setTextColor(Qt::black);
        if(ui->lineEdit->text()==NULL||isDigitStr(ui->lineEdit->text())==false){
            ui->textBrowser->append("无法计算幂--幂次无效");
        }
        else if(x!=y){
            ui->textBrowser->append("无法计算幂--非方阵");
        }
        else{

            int p=ui->lineEdit->text().toInt();

            if(p<0&&det(m,x)==0){
                ui->textBrowser->append("无法计算幂--不可逆矩阵无法计算负数次幂");
            }
            else{
                double ** r=new double *[x];
                for(int i=0;i<x;i++){
                    r[i]=new double[y];
                }

                m_pow(m,r,p,x);
                ui->textBrowser->setTextColor(Qt::red);
                for(int i=0;i<x;i++){
                    ui->textBrowser->append("");
                    for(int j=0;j<y;j++){
                        ui->textBrowser->insertPlainText(QString::number(r[i][j])+"    ");
                    }
                }
                ui->textBrowser->setTextColor(Qt::black);

                for(int i=0;i<x;i++){
                    delete[] r[i];
                }
                delete r;
            }
        }
    }

    for(int i=0;i<x;i++){
        delete[] m[i];
    }
    delete m;
}

void SingleMatrix::on_checkBox_power_stateChanged()
{
    if(ui->checkBox_power->isChecked()){
        ui->lineEdit->setEnabled(true);
        ui->lineEdit->clear();
    }
    else{
        ui->lineEdit->setEnabled(false);
        ui->lineEdit->setText("在此输入幂次");
    }
}
