template <class Type>
void List<Type>::Inverse()
{
    if (first == NULL)
        return;
    ListNode<Type> *p = first->link, *pr = NULL;
    while (p != NULL)
    {
        first->link = pr; //逆转 first 指针
        pr = first;
        first = p;
        p = p->link; //指针前移
    }
    first->link = pr;
}

template <class Type>
void List<Type>::Inverse()
{
    ListNode<Type> *p, *head = new ListNode<Type>(); //创建表头结点, 其 link 域默认为 NULL
    while (first != NULL)
    {
        p = first;
        first = first->link; //摘下 first 链头结点
        p->link = head->link;
        head->link = p; //插入 head 链前端
    }
    first = head->link;
    delete head; //重置 first, 删去表头结点
}