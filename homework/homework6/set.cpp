#include <ostream>
#include <istream>

template <class Type>
class Set
{
    //对象: 零个或多个成员的聚集。其中所有成员的类型是一致的, 但没有一个成员是相同的。
    int Contains(const Type x);       //判元素 x 是否集合 this 的成员
    int SubSet(Set<Type> &right);     //判集合 this 是否集合 right 的子集
    int operator==(Set<Type> &right); //判集合 this 与集合 right 是否相等
    int Elemtype();                   //返回集合元素的类型
    Type GetData();                   //返回集合原子元素的值
    char GetName();                   //返回集合 this 的集合名
    Set<Type> *GetSubSet();           //返回集合 this 的子集合地址
    Set<Type> *GetNext();             //返回集合 this 的直接后继集合元素
    int IsEmpty();                    //判断集合 this 是否空。空则返回 1, 否则返回 0
    // friend ostream &operator<<(ostream &out, Set<Type> t);
};

template <class Type>
ostream &operator<<(ostream &out, Set<Type> t)
{
    //友元函数, 将集合 t 输出到输出流对象 out。
    t.traverse(out, t);
    return out;
};

template <class Type>
void traverse(ostream &out, Set<Type> s)
{
    //友元函数, 集合的遍历算法
    if (s.IsEmpty() == 0)
    { //集合元素不空
        if (s.Elemtype() == 0)
            out << s.GetName() << '{'; //输出集合名及花括号
        else if (s.Elemtype() == 1)
        {                       //集合原子元素
            out << s.GetData(); //输出原子元素的值
            if (s.GetNext() != NULL)
                out << ',';
        }
        else
        {                            //子集合
            traverse(s.GetSubSet()); //输出子集合
            if (s.GetNext() != NULL)
                out << ',';
        }
        traverse(s.GetNext()); //向同一集合下一元素搜索
    }
    else
        out << '}';
};