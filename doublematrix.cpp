#include "doublematrix.h"
#include "ui_doublematrix.h"
#include "common.h"

DoubleMatrix::DoubleMatrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleMatrix)
{
    ui->setupUi(this);
    this->setWindowTitle("双矩阵计算器");
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_3->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_3->horizontalHeader()->setDefaultSectionSize(40);
}

DoubleMatrix::~DoubleMatrix()
{
    delete ui;
}

void DoubleMatrix::on_toolButton_1rowadd_clicked()
{
    int i=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(i+1);
}

void DoubleMatrix::on_toolButton_1rowsubb_clicked()
{
    int i=ui->tableWidget->rowCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少行数#");
        return;
    }
    ui->tableWidget->setRowCount(i-1);
}

void DoubleMatrix::on_toolButton_1coladd_clicked()
{
    int i=ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(i+1);
}

void DoubleMatrix::on_toolButton_1colsub_clicked()
{
    int i=ui->tableWidget->columnCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少列数#");
        return;
    }
    ui->tableWidget->setColumnCount(i-1);
}
//88888

void DoubleMatrix::on_toolButton_2rowadd_clicked()
{
    int i=ui->tableWidget_2->rowCount();
    ui->tableWidget_2->setRowCount(i+1);
}

void DoubleMatrix::on_toolButton_2rowsubb_clicked()
{
    int i=ui->tableWidget_2->rowCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少行数#");
        return;
    }
    ui->tableWidget_2->setRowCount(i-1);
}

void DoubleMatrix::on_toolButton_2coladd_clicked()
{
    int i=ui->tableWidget_2->columnCount();
    ui->tableWidget_2->setColumnCount(i+1);
}

void DoubleMatrix::on_toolButton_2colsub_clicked()
{
    int i=ui->tableWidget_2->columnCount();
    if(i==1){
        ui->textBrowser->setText("#无法继续减少列数#");
        return;
    }
    ui->tableWidget_2->setColumnCount(i-1);
}

void DoubleMatrix::on_pushButton_Go_clicked()
{
    ui->textBrowser->clear();

    int flag=1;

    if(isMatrixAvailable(ui->tableWidget)==false){
        ui->textBrowser->append("# 矩阵1信息缺失或无效 #");
        flag=0;
    }
    if(isMatrixAvailable(ui->tableWidget_2)==false){
        ui->textBrowser->append("# 矩阵2信息缺失或无效 #");
        flag=0;
    }
    if(flag==0){
        ui->textBrowser->append("# --无法计算-- #");
        return;
    }


    int x=ui->tableWidget->rowCount();
    int y=ui->tableWidget->columnCount();
    int y1=ui->tableWidget_2->rowCount();
    int z=ui->tableWidget_2->columnCount();

    if(ui->comboBox->currentText()=="*"){
        if(y!=y1){
            ui->textBrowser->setText("# --无法相乘-- #");
            ui->textBrowser->append("#矩阵1的列数与矩阵2的行数不等#");
        }
        else{   //开始相乘
            ui->tableWidget_3->setRowCount(x);
            ui->tableWidget_3->setColumnCount(z);
            for(int i=0;i<x;i++){
                for(int j=0;j<z;j++){
                    int num=0;
                    for(int k=0;k<y;k++){
                        num+=ui->tableWidget->item(i,k)->text().toInt()*ui->tableWidget_2->item(k,j)->text().toInt();
                    }
                    ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(QString::number(num)));
                }
            }
            ui->textBrowser->setText("A * B =");
        }
    }
    else{   //加减
        int f=1;
        if(x!=y1){
            f=0;
            ui->textBrowser->setText("# 两矩阵行数不等 #");
        }
        if(y!=z){
            f=0;
            ui->textBrowser->append("# 两矩阵列数不等 #");
        }
        if(f==0){
            ui->textBrowser->append("# --无法加减-- #");
            return;
        }

        //开始加减
        ui->tableWidget_3->setRowCount(x);
        ui->tableWidget_3->setColumnCount(y);

        if(ui->comboBox->currentText()=="+"){
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    int num=ui->tableWidget->item(i,j)->text().toInt()+ui->tableWidget_2->item(i,j)->text().toInt();
                    ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(QString::number(num)));
                }
            }
            ui->textBrowser->append("A + B =");
        }

        else if(ui->comboBox->currentText()=="-"){
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    int num=ui->tableWidget->item(i,j)->text().toInt()-ui->tableWidget_2->item(i,j)->text().toInt();
                    ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(QString::number(num)));
                }
            }
            ui->textBrowser->append("A - B =");
        }
    }
}

void DoubleMatrix::on_pushButton_Reset1_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(2);
}

void DoubleMatrix::on_pushButton_Reset2_clicked()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(2);
    ui->tableWidget_2->setColumnCount(2);
}

void DoubleMatrix::on_pushButton_ResetAll_clicked()
{
    on_pushButton_Reset1_clicked();
    on_pushButton_Reset2_clicked();
    ui->textBrowser->clear();
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setColumnCount(0);
}
