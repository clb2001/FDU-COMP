#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 构造树
TreeNode *creatBinTree(vector<vector<int>>vec, vector<vector<int>> &temp, vector<int> oneD, int r){
    TreeNode *head = new TreeNode; //创建头节点
    if (count (oneD.begin(), oneD.end(), r) == 1){
        head->val = r;
        head->left = nullptr;
        head->right = nullptr;
        return head;
    }
    for (int i = 0; i < vec.size(); i++){
        if (vec[i][0] == r && (find(temp[1].begin(), temp[1].end(), vec[i][1]) == temp[1].end())){
            head->val = r;
            temp[0].push_back(r);
            temp[1].push_back(vec[i][1]);
            head->left = creatBinTree(vec, temp, oneD, vec[i][1]);
        }
        else if (vec[i][1] == r && (find(temp[0].begin(), temp[0].end(), vec[i][0]) == temp[0].end())){
            head->val = r;
            temp[0].push_back(vec[i][0]);
            temp[1].push_back(r);
            head->right = creatBinTree(vec, temp, oneD, vec[i][0]);
        }
    }
}

void isCompleteBinTree(TreeNode *tree, string &outcome){
    queue<TreeNode*> q;
    q.push(tree);
    bool flag = false;
    while (!q.empty()){
        TreeNode *node = q.front();
        q.pop();
        if (node == nullptr){
            flag = true;
        }
        if (flag){
            outcome = "no";
            break;
        }
        q.push(node->left);
        q.push(node->right);
    } 
}

int main(){
    int n, r;
    cin >> n;
    cin >> r;
    int graph[n-1][2];
    vector<vector<int>> vec(n - 1, vector<int>(2));

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < 2; j++){
            cin >> graph[i][j];
        }
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < 2; j++){
            vec[i][j] = graph[i][j];
        }
    }

    vector<vector<int>> temp(2);
    
    vector<int> oneD;
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < 2; j++){
            oneD.push_back(graph[i][j]);
        }
    }    
    
    TreeNode *tree = creatBinTree(vec, temp, oneD, r);

    string outcome = "yes";
    
    isCompleteBinTree(tree, outcome);

    cout << outcome << endl;
    return 0;
}