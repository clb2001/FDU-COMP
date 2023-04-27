#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void att(int j, int i, int arr[], vector<vector<int>> &temp){
    if (i > 0){
        if (i % 2 == 0){
            temp[j].push_back(arr[i/2 - 1]);
            att(j, i/2 - 1, arr, temp);
        }
        else if (i % 2 == 1){
            temp[j].push_back(arr[(i - 1)/2]);
            att(j, (i-1)/2, arr, temp);
        }
    }
}

int main(){
    int m;
    cin >> m;
    int arr[m];
    vector<vector<int>> temp(m/2 + 1);

    // 输入二叉树
    for (int i = 0; i < m; i++){
        cin >> arr[i];
    }

    int sum;
    cin >> sum;

    for (int i = (m-1)/2; i < m; i++){
        int j = i - (m-1)/2;
        temp[j].push_back(arr[i]);
        att(j, i, arr, temp);
    }

    vector<vector<int>> tmp;

    for (int i = 0; i < temp.size(); i++){
        if (accumulate(temp[i].begin(), temp[i].end(), 0) == sum){
            tmp.push_back(temp[i]);
        }
    }

    for (int i = 0; i < tmp.size(); i++){
        if (tmp[i].size() == tmp[tmp.size()-1].size()){
            for (int j = tmp[i].size() - 1; j > 0; j--){
                cout << tmp[i][j] << ' ';
            }
            cout << tmp[i][0];
            cout << endl;
        }
    }

    for (int i = 0; i < tmp.size(); i++){
        if (tmp[i].size() != tmp[tmp.size()-1].size()){
            for (int j = tmp[i].size() - 1; j >= 0; j--){
                cout << tmp[i][j] << ' ';
            }
            cout << tmp[i][0];
            cout << endl;
        }
    }
    return 0;
}

// 空格坑了我很久