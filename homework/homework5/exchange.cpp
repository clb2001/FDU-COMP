void BinaryTree<Type>::exchange(BinTreeNode<Type> *ptr)
{
    BinTreeNode<Type> *temp;
    if (ptr->leftChild != NULL || ptr->rightChild != NULL)
    {
        temp = ptr->leftChild;
        ptr->leftChild = ptr->rightChild;
        ptr->rightChild = temp;
        exchange(ptr->leftChild);
        exchange(ptr->rightChild);
    }
}