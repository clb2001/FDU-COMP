// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cmath>
// using namespace std;

// typedef struct node{
//     int parent;
//     int length;
// }UFS;

// int find(int x, UFS t[]){
//     if (t[x].parent == x){
//         return t[x].parent;
//     }     
//     t[x].parent = find(t[x].parent, t);    //压缩路径
//     return t[x].parent;
// }

// void merge(int i, int j, UFS t[]){
//     int idx1, idx2;
//     idx1 = find(i, t);
//     idx2 = find(j, t);
//     if (idx1 != idx2){
//         t[idx2].parent = idx1;
//     }
// }

// void search(vector<vector<int>> Count, UFS t[], int m, int n){
//     for (int i = 0; i < m; i++){
//         merge(Count[i][1], Count[i][2], t);
//         for (int j = 1; j < n + 1; j++){
//             int idx = find(j, t);
//             t[idx].length++;
//             if (t[idx].length == n){
//                 cout << Count[i][0];
//                 return;
//             }
//         }
//     }
//     cout << -1;
// }

// int main(){
//     // n表示区域数量，m表示路的数量
//     int n, m;
//     cin >> n >> m;
//     int arr[m][2];
//     int time[m];
//     vector<vector<int>> Count(m, vector<int>(3,0));
//     for (int i = 0; i < m; i++){
//         cin >> arr[i][0] >> arr[i][1] >> time[i];
//     }

//     for (int i = 0; i < m; i++){
//         Count[i][0] = time[i];
//         Count[i][1] = arr[i][0];
//         Count[i][2] = arr[i][1];
//     }
//     sort(Count.begin(), Count.end());

//     UFS t[n + 1];
//     // 先将节点设为它自己
//     for (int i = 1; i < n + 1; i++){
//         t[i].parent = i;
//         t[i].length = 0;
//     }
    
//     search(Count, t, m, n);

//     return 0;
// }

// 不要从网上抄代码，自己写的不是一下子就通过了吗？