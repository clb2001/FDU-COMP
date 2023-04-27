#include <iostream>
#include <string> 
using namespace std;
void frequency(String &s, char &A[], int &C[], int &k)
{
    // s 是输入字符串，数组 A[ ]中记录字符串中有多少种不同的字符，C[ ]中记录每
    //一种字符的出现次数。这两个数组都应在调用程序中定义。k 返回不同字符数。
    int i, j, len = s.length();
    if (!len)
    {
        cout << "The string is empty. " << endl;
        k = 0;
        return;
    }
    else
    {
        A[0] = s[0];
        C[0] = 1;
        k = 1; /*语句 s[i]是串的重载操作*/
        for (i = 1; i < len; i++)
            C[i] = 0; /*初始化*/
        for (i = 1; i < len; i++)
        { /*检测串中所有字符*/
            j = 0;
            while (j < k && A[j] != s[i])
                j++; /*检查 s[i]是否已在 A[ ]中*/
            if (j == k)
            {
                A[k] = s[i];
                C[k]++;
                k++
            } /*s[i]从未检测过*/
            else
                C[j]++; /*s[i]已经检测过*/
        }
    }
}
