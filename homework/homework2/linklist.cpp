template <class Type>
void List<Type>::
    siftToRight(ListNode<Type> *&p, ListNode<Type> *&pr, int k)
{
    if (p == NULL && pr != first)
    { //已经在链的最右端
        cout << "已经在链的最右端，不能再右移。" << endl;
        return;
    }
    int i;
    ListNode<Type> *q;
    if (p == NULL) //从链头开始
    {
        i = 1;
        pr = NULL;
        p = first;
    } //重置 p 到链头也算一次右移
    else
        i = 0;
    while (p != NULL && i < k)
    { //右移 k 个结点
        q = p->link;
        p->link = pr; //链指针 p→link 逆转指向 pr
        pr = p;
        p = q;
        i++; //指针 pr, p 右移
    }
    cout << "右移了" << i << "个结点。" << endl;
}

template <class Type>
void List<Type>::
    siftToLeft(ListNode<Type> *&p, ListNode<Type> *&pr, int k)
{
    if (p == NULL && pr == first)
    { //已经在链的最左端
        cout << "已经在链的最左端，不能再左移。" << endl;
        return;
    }
    int i = 0;
    ListNode<Type> *q;
    while (pr != NULL && i < k)
    { //左移 k 个结点
        q = pr->link;
        pr->link = p; //链指针 pr->link 逆转指向 p
        p = pr;
        pr = q;
        i++; //指针 pr, p 左移
    }
    cout << "左移了" << i << "个结点。" << endl;
    if (i < k)
    {
        pr = p;
        p = NULL;
    } //指针 p 移出表外，重置 p, pr
}