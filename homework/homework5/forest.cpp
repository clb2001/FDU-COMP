template <class Type>
class LchRsibNode
{ //左子女-右兄弟链表结点类的定义
protected:
    Type data;        //结点数据
    int llink, rlink; //结点的左子女、右兄弟指针
public:
    LchRsibNode() : llink(NULL), rlink(NULL) {}
    LchRsibNode(Type x) : llink(NULL), rlink(NULL), data(x) {}
} 


template <class Type>
class DoublyTagNode
{ //双标记表结点类的定义
protected:
    Type data;      //结点数据
    int ltag, rtag; //结点的左子女、右兄弟标记
public:
    DoublyTagNode() : ltag(0), rtag(0) {}
    DoublyTagNode(Type x) : ltag(0), rtag(0), data(x) {}
} 

template <class Type>
class staticlinkList //静态链表类定义
    : public LchRsibNode<Type>,
      public DoublyTagNode<Type>
{
private:
    LchRsibNode<Type> *V;     //存储左子女-右兄弟链表的向量
    DoublyTagNode<Type> *U;   //存储双标记表的向量
    int MaxSize, CurrentSize; //向量中最大元素个数和当前元素个数
public:
    dstaticlinkList(int Maxsz) : MaxSize(Maxsz), CurrentSize(0)
    {
        V = new LchRsibNode<Type>[Maxsz];
        U = new DoublyTagNode<Type>[Maxsz];
    }
} 

void staticlinkList<Type>::DtagF - LchRsibF()
{
    Stack<int> st;
    int k;
    for (int i = 0; i < CurrentSize; i++)
    {
        switch (U[i].ltag)
        {
        case 0:
            switch (U[i].rtag)
            {
            case 0:
                V[i].llink = V[i].rlink = -1;
                if (st.IsEmpty() == 0)
                {
                    k = st.GetTop();
                    st.Pop();
                    V[k].rlink = i + 1;
                }
                break;
            case 1:
                V[i].llink = -1;
                V[i].rlink = i + 1;
                break;
            }
            break;
        case 1:
            switch (U[i].rtag)
            {
            case 0:
                V[i].llink = i + 1;
                V[i].rlink = -1;
                break;
            case 1:
                V[i].llink = i + 1;
                st.Push(i);
            }
        }
    }
}