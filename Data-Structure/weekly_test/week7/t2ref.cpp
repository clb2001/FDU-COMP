#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 构造树
void search(int &flag, int x, int y, int max, int arr[], int *p){
    for (int i = 1; i <= max; i++){
        // 是左节点
        if (arr[i] == x){
            *p = i;
            flag = 1;
        }
        // 是右节点
        if (arr[i] == y){
            *p = i;
            flag = 0;
        }
    }
}

int isCompleteBinTree(int arr[], int max){
    for (int i = 1; i <= max; i++){
        if (arr[i] == 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n, r;
    cin >> n >> r;

    int arr[1024] = {0};
    arr[1] = r;
    int x, y;
    int p = 0;
    int max = 1;

    // 读入数据
    int temp[n-1][2];
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < 2; j++){
            cin >> temp[i][j];
        }
    }

    // 重新处理数组
    vector<vector<int>> tmp(n - 1, vector<int>(2));
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < 2; j++){
            tmp[i][j] = temp[i][j]; 
        }
    }

    vector<vector<int>> res;
    vector<int> s;
    s.push_back(r);
    for (int j = 0; j < n - 1; j++){
        for (int i = 0; i < tmp.size(); i++){
            if (find(s.begin(), s.end(), tmp[i][1]) == s.end() && find(s.begin(), s.end(), tmp[i][0]) != s.end()){
                res.push_back(tmp[i]);
                s.push_back(tmp[i][1]);
                tmp.erase(tmp.begin()+i);
            }
            else if (find(s.begin(), s.end(), tmp[i][0]) == s.end() && find(s.begin(), s.end(), tmp[i][1]) != s.end()){
                res.push_back(tmp[i]);
                s.push_back(tmp[i][0]);
                tmp.erase(tmp.begin()+i);
            }
        }
    }

    // 先找根节点存放的数组，再找根节点的子节点作为根节点存放的数组
    for (int j = 0; j < n - 1; j++){
        int flag = -1;
        x = res[j][0];
        y = res[j][1];
        search(flag, x, y, max, arr, &p);
        if (flag == 1){
            // 按层序遍历存储左节点
            arr[2 * p] = y;
            if (2 * p > max){
                max = 2 * p;
            }
        }
        else if (flag == 0) {
            // 按层序遍历存储右节点
            arr[2 * p + 1] = x;
            if (2 * p + 1 > max){
                max = 2 * p + 1;
            }            
        }
    }

    int outcome = isCompleteBinTree(arr, max);
    if (outcome == 0){
        cout << "no" << endl;
    } 
    else if (outcome == 1){
        cout << "yes" << endl;
    }         
    return 0;
}