#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int find(int x, vector<int> &arr){
    if (arr[x] == x){
        return x;
    }
    else {
        arr[x] = find(arr[x], arr);
        return arr[x];
    }
}

void merge(int i, int j, vector<int> &arr){
    if (i < j){
        arr[find(j, arr)] = find(i, arr);
    }
    else if (i > j){
        arr[find(i, arr)] = find(j, arr);
    }
}

void search(int n, int m, vector<vector<int>> &Count){
    vector<int> arr(n + 1, 0);
    // 先将节点设为它自己
    for (int i = 1; i < n + 1; i++){
        arr[i] = i;
    }
    // 改变父节点
    for (int i = 0; i < m; i++){
        merge(Count[i][1], Count[i][2], arr);
        // 查询
        for (int j = 1; j < n + 1; j++){
            int k = arr[j];
            while (arr[k] != k){
                k = arr[k];
                arr[j] = k;
            }
        }
        for (int j = 1; j < n + 1; j++){
            if (count(arr.begin(), arr.end(), j) == n){
                cout << Count[i][0] << endl;
                return;    
            }
        }
    }
    cout << -1 << endl;
}

int main(){
    // n表示区域数量，m表示路的数量
    int n, m;
    cin >> n >> m;
    int arr[m][2];
    int time[m];
    vector<vector<int>> Count(m, vector<int>(3,0));
    for (int i = 0; i < m; i++){
        cin >> arr[i][0] >> arr[i][1] >> time[i];
    }

    for (int i = 0; i < m; i++){
        Count[i][0] = time[i];
        Count[i][1] = arr[i][0];
        Count[i][2] = arr[i][1];
    }
    sort(Count.begin(), Count.end());
    
    search(n, m, Count);
    return 0;
}

// 条件其实很松，还是要自己钻研