#include <iostream>
#include <string>
#include <cstdio>
// #include <vector>
#include <iomanip> 

using namespace std;

struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(char x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *creatBinTree(char str1[], char str2[], int size){
    if (size == 0){
        return nullptr;
    }
    int index;
    for (int i = 0; i < size; i++){
        if (str2[i] == str1[0]){
            index = i;
            break;
        }
    }
    TreeNode *head = new TreeNode; //创建头节点
    head->val = str1[0];
    head->left = creatBinTree(str1 + 1, str2, index);   
    head->right = creatBinTree(str1 + index + 1, str2 + index + 1, size - 1 - index);   
}

void postOrder(TreeNode *tree){
    if (tree == nullptr){
        return;
    }
    else{
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->val;
    }
    // cout << endl;
}

int main(){
    string s1, s2;
    // vector<char> str1, str2;
    while (cin >> s1 >> s2){
        char str1[s1.size()];
        char str2[s2.size()];
        for (int i = 0; i < s1.size(); i++){
            // str1.push_back(s1[i]);
            str1[i] = s1[i];
        }
        for (int i = 0; i < s2.size(); i++){
            // str2.push_back(s2[i]);
            str2[i] = s2[i];
        }
        int size = s1.size();
        TreeNode *tree = creatBinTree(str1, str2, size);
        // postOrder(tree);
        cout << endl;
    }
    return 0;
}