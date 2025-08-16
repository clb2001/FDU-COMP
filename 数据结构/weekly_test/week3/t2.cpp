// 从这道题的学习中初步领略动态规划思想
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int i, m, n, w;
	
	cin >> n;
    cin >> w;
	int arr[n];
	int script[n];

    for (m = 0; m < n; m++){
		cin >> arr[m];
	}

    // 这里的head是指数组头节点的位置，tail是指
    // 定义一个script数组，记录
    // 
    int head = 0;
    int tail = -1;
	for (i = 0; i < n; i++){
        if (head <= tail && script[head] < i-w+1){
            head++;
        }
        while (head <= tail && arr[script[tail]] <= arr[i]){
            tail--;
        }
        tail++;
        script[tail] = i; 
        if (i >= w-1){
            cout << arr[script[head]] << " ";
        }
    }
	
	return 0;
}