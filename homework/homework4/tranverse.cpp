#include <iostream>
#include <cctype>
#include <stack>
const int maxSubListNum = 20; //最大子表个数
GenList ::GenList(char &value)
{
    Stack<GenListNode *> st(maxSubListNum);       //用于建表时记忆回退地址
    SeqList<char> Name(maxSubListNum);            //记忆建立过的表名
    SeqList<GenListNode *> Pointr(maxSubListNum); //记忆对应表头指针
    GenListNode *p, q, r;
    Type ch;
    int m = 0, ad, br; // m 为已建表计数, br 用于对消括号
    cout << "广义表停止输入标志数据 value : ";
    cin >> value;
    cout << "开始输入广义表数据, 如 A(C(E(x, y), a), D(E(x, y), e))" cin >> ch;
    first = q = new GenListNode(0, ch); //建立整个表的表头结点
    if (ch != value)
    {
        Name.Insert(ch, m);
        Pointr.Insert(q, m);
        m++;
    } //记录刚建立的表头结点
    else
        return 1; //否则建立空表, 返回 1
    cin >> ch;
    if (ch == "(")
        st.Push(q); //接着应是„(‟, 进栈
    cin >> ch;
    while (ch != value)
    { //逐个结点加入
        switch (ch)
        {
        case "(":
            p = new GenListNode<Type>(q); //建立子表结点, p->hlink = q
            r = st.GetTop();
            st.Pop();
            r->tlink = p; //子表结点插在前一结点 r 之后
            st.Push(p);
            st.Push(q); //子表结点及下一表头结点进栈
            break;
        case ")":
            q->tlink = NULL;
            st.pop(); //子表建成, 封闭链, 退到上层
            if (st.IsEmpty() == 0)
                q = st.GetTop(); //栈不空, 取上层链子表结点
            else
                return 0; //栈空, 无上层链, 算法结束
            break;
        case ",":
            break;
        default:
            ad = Name.Find(ch); //查找是否已建立, 返回找到位置
            if (ad == -1)
            { //查不到, 建新结点
                p = q;
                if (isupper(ch))
                { //大写字母, 建表头结点
                    q = new GenListNode(0, ch);
                    Name.Insert(ch, m);
                    Pointr.Insert(q, m);
                    m++;
                }
                else
                    q = new GenListNode(1, ch); //非大写字母, 建原子结点
                p->tlink = q;                   //链接
            }
            else
            { //查到, 已加入此表
                q = Pointr.Get(ad);
                p = new GenListNode(q); //建立子表结点, p->hlink = q
                r = st.GetTop();
                st.Pop();
                r->tlink = p;
                st.Push(p);
                q = p;
                br = 0; //准备对消括号
                cin >> ch;
                if (ch == "(")
                    br++; //若有左括号, br 加 1
                while (br == 0)
                { // br 为 0 表示括号对消完, 出循环
                    cin >> ch;
                    if (ch == "(")
                        br++;
                    else if (ch == ")")
                        br--;
                }
            }
        }
        cin >> ch;
    }