// void GenList :: traverse ( ) { //共有函数
//  traverse ( first );
// }
#include <iostream>
void GenList ::traverse(GenListNode *ls)
{ // 广义表的遍历算法
    if (ls != NULL)
    {
        ls->mark = 1;
        if (ls->utype == 0)
            cout << ls->value.listname << '('; //表头结点
        else if (ls->utype == 1)
        { //原子结点
            cout << ls->value.atom;
            if (ls->tlink != NULL)
                cout << ',';
        }
        else if (ls->utype == 2)
        { //子表结点
            if (ls->value.hlink->mark == 0)
                traverse(ls->value.hlink); //向表头搜索
            else
                cout << ls->value.hlink->value.listname;
            if (ls->tlink != NULL)
                cout << ',';
        }
        traverse(ls->tlink); //向表尾搜索
    }
    else
        cout << ')';
}