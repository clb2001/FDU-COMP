#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int N, T;
    int num = 0;
    cin >> N;
    cin >> T;
    int A[N];
    int B[N];
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    // 思路全错了，不应该采用类似贪心匹配的算法
    // 正确的思路应该是：先只玩一个游戏，再慢慢调整，使得num单调不减
    // 错了！应该是先求出类似概率分布函数的数组
    // 想了我两个半小时啊
    // 其实求解这个题就体现了自己在生活中看问题角度的不同
    int AA[N+1] = {0};
    int BB[N+1] = {0};

    for (int i = 1; i < N + 1; i++){
        AA[i] = AA[i-1] + A[i-1];
    }

    for (int i = 1; i < N + 1; i++){
        BB[i] = BB[i-1] + B[i-1];
    }

    for (int i = 0; i < N + 1; i++){
        for (int j = 0; j < N + 1; j++){
            if ((i + j > num) && (AA[i] + BB[j] <= T)){
                num = i + j; 
            }
        }
    }

    cout << num << endl;
    return 0;
}