#include <iostream>

using namespace std;

// exceed time limit
void step(int i, int arr[], int sum, int m, int &a){
    if (arr[i] != 0){
        for (int j = 1; j <= arr[i]; j++){
            int k = i + j;
            sum += j;
            step(k, arr, sum, m, a);
            if (sum >= m){
                a = 1;
                break;
            }
        }
    }
    else if (arr[i] == 0){
        a = 0;
    }   
}

int main(){
    int m;
    cin >> m;
    int arr[m];

    // 每一个位置的最大步数
    for (int i = 0; i < m; i++){
        cin >> arr[i];
    }

    int sum = 0;
    int a = 0;
    step(0, arr, sum, m, a);

    cout << a << endl;
    return a;
}