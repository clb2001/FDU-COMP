#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/// @brief clb
/// @return 19300740005

int main(){
    int N;
    cin >> N;
    long long arr[N];
    vector<long long> tmp;
    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }

    for (int i = 0; i < N; i++){
        tmp.push_back(arr[i]);
    }

    long long sum = 0;
    for (int i = 0; i < N; i++){
        sum += arr[i];
    }

    sort(tmp.begin(), tmp.end());

    long long M = 0;
    long long W = 0;

    if (sum % 2 == 0){
        // ming first
        int i = N - 1;
        while (i >= 0){
            if ((N - 1 - i) % 2 == 0){
                M += tmp[i];
            }
            else if ((N - 1 - i) % 2 == 1){
                W += tmp[i];
            }
            i--;
        }
    }

    else if (sum % 2 == 1){
        // wu first
        int i = N - 1;
        while (i >= 0){
            if ((N - 1 - i) % 2 == 0){
                W += tmp[i];
            }
            else if ((N - 1 - i) % 2 == 1){
                M += tmp[i];
            }
            i--;
        }
    }

    cout << M << " " << W << endl; 

    return 0;
}