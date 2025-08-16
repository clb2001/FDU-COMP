#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct TNode
{
    int data;
    TNode *left;
    TNode *right;
    TNode(int x) : data(x), left(NULL), right(NULL) {}
    TNode() : data(0), left(NULL), right(NULL) {}
};

TNode *createBinTree(vector<int> arr, int N)
{
    queue<TNode *> temp;
    if (arr.empty())
    {
        return NULL;
    }
    TNode *root = new TNode;
    root->data = arr[0];
    temp.push(root);
    TNode *bt;
    int i = 1;
    while (!temp.empty())
    {
        bt = temp.front();
        temp.pop();
        if (i < arr.size())
        {
            bt->left = new TNode;
            bt->left->data = arr[i];
            temp.push(bt->left);
            i++;
        }
        else
        {
            bt->left = nullptr;
        }
        if (i < arr.size())
        {
            bt->right = new TNode;
            bt->right->data = arr[i];
            temp.push(bt->right);
            i++;
        }
        else
        {
            bt->right = nullptr;
        }
    }
    return root;
}

void preOrder(TNode *node, vector<int> path, vector<vector<int>> &W)
{
    if (!node)
    {
        return;
    }
    path.push_back(node->data);
    if (!node->left && !node->right)
    {
        W.push_back(path);
    }
    preOrder(node->left, path, W);
    preOrder(node->right, path, W);
    path.pop_back();
}

int sum(vector<int> res){
    int sum = 0;
    for (int i = 0; i < res.size(); i++){
        sum += res[i] * pow(10, res.size()- i - 1);
    }
    return sum;
}

void compare(vector<vector<int>> W)
{
    int i = 0;
    int XW = 0;
    int XM = 0;
    while (i < W.size())
    {
        if (i % 2 == 0){
            XW += sum(W[i]);
            i++;
        }
        else if (i % 2 == 1){
            XM += sum(W[i]);
            i++;
        }
    }
    if (XW > XM){
        cout << 0 << endl;
    }
    else if (XW < XM){
        cout << 1 << endl;
    }
}

int main()
{
    int N;
    cin >> N;
    int array[N];
    vector<int> arr;
    for (int i = 0; i < N; i++)
    {
        cin >> array[i];
    }

    for (int i = 0; i < N; i++)
    {
        arr.push_back(array[i]);
    }

    TNode *tree = createBinTree(arr, N);
    vector<vector<int>> W;
    vector<int> path;
    // 把前序遍历结果存到W里面
    preOrder(tree, path, W);

    // 比较
    compare(W);
    return 0;
}