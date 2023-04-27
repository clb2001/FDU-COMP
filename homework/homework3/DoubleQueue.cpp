//循环队列类定义
#include <assert.h>
template <class Type>
class DoubleQueue
{ //循环队列的类定义
public:
    DoubleQueue(int = 10);
    ~DoubleQueue() { delete[] V; }
    void EnQueue(Type &item, const int end);
    Type DeQueue(const int end);
    Type GetFront(const int end);
    void MakeEmpty() { end1 = end2 = 0; }                 //置空队列
    int IsEmpty() const { return end1 == end2; }          //判两队列空否
    int IsFull() const { return (end1 + 1) % m == end2; } //判两队列满否
private:
    int end1, end2; //队列两端的指针
    Type *V;        //存放队列元素的数组
    int m;          //队列最大可容纳元素个数
}
//构造函数
template <class Type>
DoubleQueue<Type>::DoubleQueue(int sz) : end1(0), end2(0), m(sz)
{
    //建立一个最大具有 m 个元素的空队列。
    V = new Type[m]; //创建队列空间
    assert(V != 0);  //断言: 动态存储分配成功与否
}
//插入函数
template <class Type>
void DoubleQueue<Type>::EnQueue(Type &item, const int end)
{
    assert(!IsFull());
    if (end == 1)
    {
        end1 = (end1 + 1) % m; // end1 端指针先进 1, 再按指针进栈
        V[end1] = item;        // end1 指向实际队头位置
    }
    else
    {
        V[end2] = item;            // end2 端先进队列, 指针再进 1
        end2 = (end2 - 1 + m) % m; // end2 指向实际队头的下一位置
    }
}
//删除函数
template <class Type>
Type DoubleQueue<Type>::DeQueue(const int end)
{
    assert(!IsEmpty());
    Type &temp;
    if (end == 1)
    {
        temp = V[end1]; //先保存原队头元素的值, end1 端指针退 1
        end1 = (end1 + m - 1) % m;
    }
    else
    {
        end2 = (end2 + 1) % m;
        temp = V[end2]; // end2 端指针先退 1。再保存原队头元素的值
    }
    return temp;
}
//读取队头元素的值
template <class Type>
Type DoubleQueue<Type>::GetFront(const int end)
{
    assert(!IsEmpty());
    Type &temp;
    if (end == 1)
        return V[end1]; //返回队头元素的值
    else
        return V[(end2 + 1) % m];
}