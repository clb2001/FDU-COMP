#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N, M;
    cin >> N;
    cin >> M;
    int Ming[N];
    int Wu[M];
    vector<int> c;

    // ming's array
    for (int i = 0; i < N; i++){
        cin >> Ming[i];
    }

    // wu's array
    for (int i = 0; i < M; i++){
        cin >> Wu[i];
    }

    for (int i = 0; i < N; i++){
        int j = 0;
        int k = i;
        while(Ming[k] == Wu[j]){
            j++;
            k++;
            if (j == M){
                c.push_back(i+1);
                break;
            }
        }
    }

    if (c.size() > 0){
        cout << c[0] << endl;
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}