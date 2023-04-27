#include <iostream>

//定义一个交换函数，方便操作
void swap(int *a, int *b)
{
    int temp = 0;
    temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}
//递归逆置算法（针对顺序表）
//参数不多说，可以看之前写的逆置算法
void Reverse(int a[], int low, int high)
{
    if (low < high)
    {
        swap(&a[low], &a[high]);
        Reverse(a, low + 1, high - 1);
    }
}
//函数名：Reverse_Seg
//函数功能：整段交换两段子表
//函数参数：
void Reverse_Seg(int a[], int p, int len)
{
    if (p < 0 || p > len)
    {
        printf("输入错误，要求左移位数处于(0, %d)\n", len);
    }
    else
    {
        Reverse(a, 0, p - 1);
        Reverse(a, p, len - 1);
        Reverse(a, 0, len - 1);
    }
}

int main()
{
    int i = 0;
    int p = 0
        //其中1,2,3,4,5,6 为a线性表，7,8,9,10为b线性表
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (i = 0; i < 10; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\n");
    scanf("%d", &p);
    Reverse(A, 0, p - 1);
    Reverse(A, p, 9);
    Reverse(A, 0, 9);
    for (i = 0; i < 10; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\n");
    return 0;
}
