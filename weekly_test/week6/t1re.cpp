#include <iostream>
#include <cmath>
using namespace std;
 
int main(){
    int m;
    cin >> m;
    int arr[m];

    // 每一个位置的最大步数
    for (int i = 0; i < m; i++){
        cin >> arr[i];
    }

    int a = 0;
    int Max = 0;

    for (int i = 0; i < m - 1; i++){
        Max = max(Max, i + 1 + arr[i]);
        if (Max <= i + 1){
            cout << a << endl;
            return 0;
        }
        if (Max >= m){
            a = 1;
            cout << a << endl;
            return 0;
        }
    }
}

// 贪心算法，学习了学习了
// 过了半年，在leetcode上独立地用动态规划写了出来