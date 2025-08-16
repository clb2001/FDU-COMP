// 其实最难的，还是推翻自己之前原来的所有想法，从头来过
// 我是真不知道自己错在什么地方

#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
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

void preOrder(TreeNode *node, int pathValue, vector<int> path, vector<vector<int>> &result, int targetSum)
{
    if (!node)
    {
        return;
    }
    pathValue += node->val;
    path.push_back(node->val);
    if (pathValue == targetSum && !node->left && !node->right)
    {
        result.push_back(path);
    }
    preOrder(node->left, pathValue, path, result, targetSum);
    preOrder(node->right, pathValue, path, result, targetSum);
    pathValue -= node->val;
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<vector<int>> result;
    vector<int> path;
    int pathValue = 0;
    preOrder(root, pathValue, path, result, targetSum);
    return result;
}

TreeNode *creatBinTree(vector<int> arr)
{
    queue<TreeNode *> q;

    //如果层序序列为空，返回空树
    if (arr.empty())
    {
        return nullptr;
    }
    TreeNode *head = new TreeNode; //创建头节点
    head->val = arr[0];            //存放数组首元素
    q.push(head);                  //入队

    TreeNode *bt;
    int i = 1;
    while (!q.empty())
    {
        bt = q.front(); //取出头节点，准备给它安排左右节点
        q.pop();        //头节点出队，每一次新的循环，都让头出队

        //先弄左节点
        // i只要不超过数组的有效长度，就有左节点
        if (i < arr.size())
        {
            bt->left = new TreeNode;
            bt->left->val = arr[i];
            q.push(bt->left); //左节点入队
            i++;              //数组后移
        }
        else
        {
            bt->left = nullptr;
        }

        //再弄右节点
        if (i < arr.size())
        {
            bt->right = new TreeNode;
            bt->right->val = arr[i];
            q.push(bt->right); //右节点入队
            i++;               //数组后移
        }
        else
        {
            bt->right = nullptr;
        }
    }
    return head; //最后队列为空就出while，返回头节点
}

int main()
{
    int m;
    cin >> m;
    int input[m];

    // 输入数组元素
    for (int i = 0; i < m; i++)
    {
        cin >> input[i];
    }

    int targetSum;
    cin >> targetSum;

    // 将数组转化为vector
    vector<int> arr[m];
    for (int i = 0; i < m; i++)
    {
        arr->push_back(input[i]);
    }

    // 将vector转化为二叉树
    TreeNode* root = creatBinTree(*arr);

    vector<vector<int>> temp = pathSum(root, targetSum);

    // 打印结果
    for (int i = 0; i < temp.size(); i++){
        for (int j = 0; j < temp[i].size(); j++){
            cout << temp[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}