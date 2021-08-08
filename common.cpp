#include "common.h"

bool isDigitStr(QString src)
{
    if(src=="")
        return false;
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();
    if(*s&&*s=='-'){    //支持负数
        s++;
    }
    while(*s && *s>='0' && *s<='9')
        s++;
    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}

bool isMatrixAvailable(QTableWidget* t){
    int x=t->rowCount();
    int y=t->columnCount();
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(t->item(i,j)==NULL || t->item(i,j)==NULL || isDigitStr((t->item(i,j)->text()))==false){
                return false;
            }
        }
    }
    return true;
}

//递归计算，来源：https://blog.csdn.net/stary_yan/article/details/51126617
int det(int **m, int size) {
    if(size==1) return m[0][0];
    if (size == 2) return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    int temp = 0;
    for (int i = 0; i < size; i++) {
        int **m0 = new int*[size-1];
        for (int v = 0; v < size-1; v++)
            m0[v] = new int[size-1];
        for (int p = 0; p < size-1; p++) {
            for (int q = 0; q < size-1; q++)
                if (q < i) m0[p][q] = m[p+1][q];
                else m0[p][q] = m[p+1][q+1];
        }
        // positive for even position and negative for odd position.
        if (i%2 == 0) temp += m[0][i]*det(m0, size-1);
        else if (i%2 == 1) temp -= m[0][i]*det(m0, size-1);
        // delete the int** we new before.
        for (int v = 0; v < size-1; v++) delete [] m0[v];
        delete [] m0;
    }
    return temp;
}

//线性变换函数。。用于求秩和求逆
void exchang_row(int *a,int *b,int n);
void mul_row(int *a,int k,int n);
void add_row(int *a1,int *a2,int k,int n);

//求秩，第二个参数是线性变换后的阶梯矩阵。参考：https://zhidao.baidu.com/question/356551061.html
int rank(int **M, int **res, int m, int n)
{
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            res[i][j]=M[i][j];
        }
    }

    int i,t;
    int ri,ci;  //行标记与列标记
    int f_z;    //某列是否全为0的标志，为1表示全为0
    for(ri=ci=0;ci<n;ci++)
    {
        f_z=1;
        for(i=ri;i<m;i++)
            if(res[i][ci]!=0){
                if(i!=ri){
                    if(f_z)
                        exchang_row(&(res[ri][ci]),&(res[i][ci]),n-ci);
                    else{
                        t=res[i][ci];
                        mul_row(&(res[i][ci]),res[ri][ci],n-ci);
                        add_row(&(res[i][ci]),&(res[ri][ci]),-t,n-ci);
                    }
                }
                f_z=0;
            }
        if(!f_z)
            ri++;
    }
    return ri;
}

//***************************************************

void exchang_row(int *a,int *b,int n)
{ int i,t;
    for(i=0;i<n;i++)
    { t=a[i];
        a[i]=b[i];
        b[i]=t;
    }
}
void mul_row(int *a,int k,int n)
{ int i;
    for(i=0;i<n;i++)
        a[i]*=k;
}
void add_row(int *a1,int *a2,int k,int n)
{ int i;
    for(i=0;i<n;i++)
        a1[i]+=a2[i]*k;
}

//******************************************************
//这个逆问题太多。。决定偷懒用eigen的库函数算了。。
void inverse(int **M, double **res, int x)
{
    MatrixXf tm(x,x);
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            tm(i,j)=M[i][j];
        }
    }
    MatrixXf tm2=tm.inverse();
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            res[i][j]=tm2(i,j);
        }
    }
}

void m_pow(int **m,double**r,int p,int x){

    if(p==0){
        for(int i=0;i<x;i++){
            for(int j=0;j<x;j++){
                r[i][j]=0;
                if(i==j){
                    r[i][j]=1;
                }
            }
        }
        return;
    }

    MatrixXf tm(x,x);
    MatrixXf rm(x,x);

    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            tm(i,j)=m[i][j];
            rm(i,j)=m[i][j];
        }
    }
    if(p<0){
        tm=tm.inverse();
        rm=rm.inverse();
        p=-p;
    }
    //p>0
    for(int i=1;i<p;i++){
        rm=rm*tm;
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            r[i][j]=rm(i,j);
        }
    }
    return;
}
