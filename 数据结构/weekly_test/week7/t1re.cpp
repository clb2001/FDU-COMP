#include <iostream>
#include <string>
using namespace std;

void postorder(string preorder, string inorder)
{
    int len = preorder.length();
    if (len == 0)
        return;
    if (len == 1)
    {
        cout << preorder[0];
        return;
    }
    int pos = inorder.find(preorder[0]); // 查找根节点在中序序列中的位置，通过根节点划分左右子树
    postorder(preorder.substr(1, pos), inorder.substr(0, pos));
    postorder(preorder.substr(pos + 1, len - pos - 1), inorder.substr(pos + 1, len - pos - 1));
    cout << preorder[0];
}

int main()
{
    string s1, s2;
    while (cin >> s1 >> s2)
    {
        postorder(s1, s2);
        cout << endl;
    }
}