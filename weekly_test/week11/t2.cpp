#include <iostream>
#include <cmath>
using namespace std;

int x[10001];
int y[10001];
int s[10001];

int check(int n, double mid, int x[], int y[], int s[]){
    double start;
    double begin = s[0] / mid;
    if (begin > y[0]){
        return 0;
    }
    else if (begin <= x[0]){
        start = x[0];
    }
    else if(begin > x[0]){
        start = begin;
    }

    for (int i = 1; i < n; i++){
        if ((start + s[i]/mid) > y[i]){
            return 0;
        }
        else if ((start + s[i]/mid) <= x[i]){
            start = x[i];
            continue;
        }
        else if ((start + s[i]/mid) > x[i]){
            start = (start + s[i]/mid);
            continue;
        }
    }
    return 1;
}

// 二分查找
int main(){
    // 房间数目n
    int n;

    double min = 0.0;
    double max = 0.0;
    double sum = 0.0;
    cin >> n;
    // x_i 最早出发时刻
    // y_i 最晚出发时刻
    // s_i 出发地到第一个地方的距离
    for (int i = 0; i < n; i++){
        cin >> x[i] >> y[i] >> s[i];
        sum += s[i];
        // if (i != 0){
        //     if (s[i]/(x[i+1]-x[i]) > max){
        //         max = s[i]/(x[i+1]-x[i]);
        //     }
        // }
        // else if (i == 0){
        //     max = (double)s[0]/x[0];
        // }
    }
    // 算max哪需要搞得这么复杂，不开10000见祖宗
    max = 1000.00;
    // min = (sum/y[n-1]);
    min = 0.0;


    while (max > min + (1e-3)){
        double mid = (min + max) / 2;
        if (check(n, mid, x, y, s)){
            max = mid;
        }
        else{
            min = mid;
        }
    }
    printf("%.2lf\n", max);
    return 0;
}