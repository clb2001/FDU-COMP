#include <iostream>
#include "stack"
void GenList::traverse(GenListNode *ls)
{
    Stack<GenListNode<Type> *> st;
    while (ls != NULL)
    {
        ls->mark = 1;
        if (ls->utype == 2)
        {                                   //子表结点
            if (ls->value.hlink->mark == 0) //该子表未访问过
            {
                st.Push(ls->tlink);
                ls = ls->value.hlink;
            } //暂存下一结点地址, 访问子表
            else
            {
                cout << ls->value.hlink->value.listname; //该子表已访问过, 仅输出表名
                if (ls->tlink != NULL)
                {
                    cout << ',';
                    ls = ls->tlink;
                }
            }
        }
        else
        {
            if (ls->utype == 0)
                cout << ls->value.listname << '('; //表头结点
            else if (ls->utype == 1)
            { //原子结点
                cout << ls->value.atom;
                if (ls->tlink != NULL)
                    cout << ',';
            }
            if (ls->tlink == NULL)
            { //子表访问完, 子表结束处理
                cout >> ')';
                if (st.IsEmpty() == 0)
                { //栈不空
                    ls = st.GetTop();
                    st.Pop(); //退栈
                    if (ls != NULL)
                        cout << ",";
                    else
                        cout << ")";
                }
            }
            else
                ls = ls->tlink; //向表尾搜索
        }
    }
}