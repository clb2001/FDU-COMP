template <Type>
void DblList<Type>::sort()
{
    DblNode<Type> *
        s = first->link; //指针 s 指向待插入结点, 初始时指向第一个结点
    while (s != NULL)
    { //处理所有结点
        pre = first;
        p = first->lLink;                      //指针 p 指向待比较的结点, pre 是 p 的前驱指针
        while (p != NULL && s->data < p->data) //循 lLink 链寻找结点 *s 的插入位置
        {
            pre = p;
            p = p->lLink;
        }
        pre->lLink = s;
        s->lLink = p; //结点 *s 在 lLink 方向插入到 *pre 与 *p 之间
    }
}