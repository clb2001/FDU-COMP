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
TreeNode *creatBinTree(int max, int r, vector<vector<int>> &vec){
    if (r == max + 1){
        return nullptr;
    }
    int count = 0;
    for (int i = 0; i < vec.size(); i++){
        if (find(vec[i].begin(), vec[i].end(), r) != vec[i].end()){
            count++;
        }
    }
    if (count == 0){
        TreeNode *tree = new TreeNode(r);
        return tree;
    }

    int index_l = max + 1; 
    int index_r = max + 1;
    for (int i = 0; i < vec.size(); i++){
        if (r == vec[i][0]){
            index_l = vec[i][1];
            vec.erase(vec.begin()+i);
        }
    }

    for (int i = 0; i < vec.size(); i++){
        if (r == vec[i][1]){
            index_r = vec[i][0];
            vec.erase(vec.begin()+i);
        }
    }

    TreeNode *tree = new TreeNode;
    tree->val = r;
    tree->left = creatBinTree(max, index_l, vec);
    tree->right = creatBinTree(max, index_r, vec);
}

void isCompleteBinTree(TreeNode *tree, string &outcome){
    queue<TreeNode*> q;
    q.push(tree);
    bool flag = false;
    while (!q.empty()){
        TreeNode *node = q.front();
        q.pop();
        int count = 0;
        while (node == nullptr){
            q.pop();
            if (q.empty()){
                count = 1;
                break;
            }
            else if (q.front() != nullptr){
                count = 1;
                flag = true;
                break;
            }
        }
        if (flag){
            outcome = "no";
            break;
        }
        if (count == 1){
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

    int max = n;
    TreeNode *tree = creatBinTree(max, r, vec);

    string outcome = "yes";
    
    isCompleteBinTree(tree, outcome);

    cout << outcome << endl;
    return 0;
}