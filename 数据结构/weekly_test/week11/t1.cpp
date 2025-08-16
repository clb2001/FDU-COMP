#include <iostream>
#include <cmath>
using namespace std;

int arr[10001];

int check(int k, int m, int h){
    int cnt = 0;
    for (int i = 0; i < m; i++){
        cnt += arr[i]/k;
        if (arr[i] % k != 0){
            cnt++;
        }
    }
    return cnt <= h;
}

// 二分查找
int main(){
    int m, h;
    cin >> m >> h;
    int max = 0;
    for (int i = 0; i < m; i++){
        cin >> arr[i];
        if (arr[i] > max){
            max = arr[i];
        }
    }
    int ans = 1;
    // left close, right open
    int l, r;
    while (l < r - 1){
        int mid = (l + r) / 2;
        if (check(l, h)){
            r = mid + 1;
        }
        else {
            l = mid + 1;
        }
        cout << l;
    }
    return 0;
}