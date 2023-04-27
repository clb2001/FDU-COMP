#include <iostream>
using namespace std;
int minmax(int A[][], const int m, const int n)
{
    //在二维数组 A[m][n]中求所有鞍点, 它们满足在行中最小同时在列中最大
    int *row = new int[m];
    int *col = new int[n];
    int i, j;
    for (i = 0; i < m; i++)
    { //在各行中选最小数组元素, 存于 row[i]
        row[i] = A[i][0];
        for (j = 1; j < n; j++)
            if (A[i][j] < row[i])
                row[i] = A[i][j];
    }
    for (j = 0; j < n; j++)
    { //在各列中选最大数组元素, 存于 col[j]
        col[i] = A[0][j];
        for (i = 1; i < m; i++)
            if (A[i][j] > col[j])
                col[j] = A[i][j];
    }
    for (i = 0; i < m; i++)
    { //检测矩阵，寻找鞍点并输出其位置
        for (j = 0; j < n; j++)
            if (row[i] == col[j])
                cout << "The saddle point is : (" << i << ", " << j << ")" << endl;
        delete[] row;
        delete[] col;
    }