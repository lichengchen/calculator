#include "vectorwin.h"
#include "ui_vectorwin.h"
#include "math.h"

VectorWin::VectorWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VectorWin)
{
    ui->setupUi(this);
    setWindowTitle("向量计算器");
    ui->lineEdit_2->setEnabled(false);
    ui->label_2->setEnabled(false);
/*
    QRegExp regExp("^(\\d{1,5},){2}\\d{1,5}$");
    QRegExpValidator *pRegExpValidator = new QRegExpValidator(regExp,this);
    ui->lineEdit->setValidator(pRegExpValidator);
*/
}

VectorWin::~VectorWin()
{
    delete ui;
}

void VectorWin::on_comboBox_currentIndexChanged(int index)
{
    if(index==0){
        ui->lineEdit_2->setEnabled(false);
        ui->label_2->setEnabled(false);
    }
    else{
        ui->lineEdit_2->setEnabled(true);
        ui->label_2->setEnabled(true);
    }
}

void VectorWin::on_pushButton_Go_clicked()
{
    QString str = ui->lineEdit->text();
    QStringList list = str.split(",", QString::SkipEmptyParts);
    int n=list.size();
    if(n==0){
        ui->textBrowser->setText("请先输入向量");
        return;
    }
    int *a=new int [n];
    for(int i=0;i<n;i++){
        a[i]=list.at(i).toInt();
    }

    if(ui->comboBox->currentIndex()==0){
        int s=0;
        for(int i=0;i<n;i++){
            s+=a[i]*a[i];
        }
        ui->textBrowser->setText(QString::number(sqrt(s)));
    }
    else{
        QString str2 = ui->lineEdit_2->text();
        QStringList list2 = str2.split(",", QString::SkipEmptyParts);
        int m=list2.size();
        if(m==0){
            ui->textBrowser->setText("请先输入向量");
            return;
        }
        if(m!=n){
            ui->textBrowser->setText("无法计算-向量维数不同");
            return;
        }
        int *b=new int [m];
        for(int i=0;i<m;i++){
            b[i]=list2.at(i).toInt();
        }

        if(ui->comboBox->currentIndex()==1){
            int s=0;
            for(int i=0;i<n;i++){
                s+=a[i]*b[i];
            }
            ui->textBrowser->setText(QString::number(s));
        }
    }
}
