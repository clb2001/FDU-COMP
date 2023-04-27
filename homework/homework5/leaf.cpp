int BinaryTree<Type>::leaf(BinTreeNode<Type> *ptr)
{
    if (ptr == NULL)
        return 0;
    else if (ptr->leftChild == NULL && ptr->rightChild == NULL)
        return 1;
    else
        return leaf(ptr->leftChild) + leaf(ptr->rightChild);
}