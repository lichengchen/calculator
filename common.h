#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include "QTableWidget"
#include <Eigen>
using namespace Eigen;

bool isDigitStr(QString);                   //判断字符串是否是数字
bool isMatrixAvailable(QTableWidget* t);    //判断表格表示的矩阵是否有效

int det(int **m,int size);  //返回方阵行列式值，一定要保证传进去方阵
void stairs(int **M, int **result, int m, int n);  //用初等变换求一个阶梯矩阵（行最简形矩阵）
int rank(int **M, int **stairs,int m, int n);         //求秩
void inverse(int **M, double **res, int x);               //求逆，要求传入的矩阵必需可逆
void m_pow(int **m,double**r,int p,int n);

#endif // COMMON_H
