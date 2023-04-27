#include <stdlib.h>
template <class Type>
template <class Type>
BstNode<Type> *BST<Type>::leftReplace(BstNode<Type> *ptr)
{
    BstNode<Type> *temp = ptr->leftChild; //进到 ptr 的左子树
    while (temp->rightChild != NULL)
        temp = temp->rightChild; //搜寻中序下最后一个结点
    ptr->data = temp->data;      //用该结点数据代替根结点数据
    return temp;
}

template <class Type>
BstNode<Type> *BST<Type>::rightReplace(BstNode<Type> *ptr)
{
    BstNode<Type> *temp = ptr->rightChild; //进到 ptr 的右子树
    while (temp->leftChild != NULL)
        temp = temp->leftChild; //搜寻中序下最后一个结点
    ptr->data = temp->data;     //用该结点数据代替根结点数据
    return temp;
}

void BST<Type>::Remove(Type &x, BstNode<Type> *&ptr)
{
    //私有函数：在以 ptr 为根的二叉搜索树中删除含 x 的结点。若删除成功则新根通过 ptr 返回。在程序中用到一个
    //随机数发生器 rand( ), 产生 0-32767 之间的随机数, 将它除以 16384, 得到 0-2 之间的浮点数。若其大于 1, 用左
    //子树上具有最大关键码的结点顶替被删关键码; 若其小于或等于 1, 用右子树上具有最小关键码的结点顶替被删
    //关键码结点, 在调用它的程序中设定它的初始值为 0。
    BstNode<Type> *temp;
    if (ptr != NULL)
        if (x < ptr->data)
            Remove(x, ptr->leftChild); //在左子树中执行删除
        else if (x > ptr->data)
            Remove(x, ptr->rightChild); //在右子树中执行删除
        else if (ptr->leftChild != NULL && ptr->rightChild != NULL)
        {
            // ptr 指示关键码为 x 的结点，它有两个子女
            if ((float)(rand() / 16384) > 1)
            {
                temp = leftReplace(ptr);
                dir = 1; //在 ptr 的左子树中搜寻中序下最后一个结点顶替 x
            }
            else
            {
                temp = rightReplace(ptr);
                dir = 0; //在 ptr 的右子树中搜寻中序下第一个结点顶替 x
            }
            Remove(ptr->data, temp); //在 temp 为根的子树中删除该结点
        }
        else
        { // ptr 指示关键码为 x 的结点，它只有一个或零个子女
            temp = ptr;
            if (ptr->leftChild == NULL)
                ptr = ptr->rightChild; //只有右子女
            else if (ptr->rightChild == NULL)
                ptr = ptr->leftChild; //只有左子女
            delete temp;
        }
}