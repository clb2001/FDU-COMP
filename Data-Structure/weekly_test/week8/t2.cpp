#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int> temp){
    for (int i = 0; i < temp.size(); i++){
        if (temp[i] == 0){
            return false;
        }
    }
    return true;
}

void search(int n, int m, int result, vector<vector<int>> &count){
    // 先合并所有结果
    vector<int> temp(n, 0);
    for (int i = 0; i < count.size(); i++){
        temp[count[i][1]-1]++;
        temp[count[i][2]-1]++;
        if (i >= n - 2 && compare(temp)){
            result = count[i][0];
            cout << result << endl;
            return;
        }
    }
    cout << result << endl; 
}

int main(){
    // n表示区域数量，m表示路的数量
    int n, m;
    cin >> n >> m;
    int arr[m][2];
    int time[m];
    vector<vector<int>> count(n, vector<int>(3,0));
    for (int i = 0; i < m; i++){
        cin >> arr[i][0] >> arr[i][1] >> time[i];
    }

    for (int i = 0; i < m; i++){
        count[i][0] = time[i];
        count[i][1] = arr[i][0];
        count[i][2] = arr[i][1];
    }
    sort(count.begin(), count.end());
    int result = -1;
    search(n, m, result, count);
    return 0;
}