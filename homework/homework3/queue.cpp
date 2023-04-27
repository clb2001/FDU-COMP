#include <assert.h>
template <class Type>
class Queue
{ //循环队列的类定义
public:
    Queue(int = 10);
    ~Queue() { delete[] elements; }
    void EnQueue(Type &item);
    Type DeQueue();
    Type GetFront();
    void MakeEmpty() { length = 0; }                 //置空队列
    int IsEmpty() const { return length == 0; }      //判队列空否
    int IsFull() const { return length == maxSize; } //判队列满否
private:
    int rear, length; //队尾指针和队列长度
    Type *elements;   //存放队列元素的数组
    int maxSize;      //队列最大可容纳元素个数
}
//构造函数
template <class Type>
Queue<Type>::Queue(int sz) : rear(maxSize - 1), length(0), maxSize(sz)
{
    //建立一个最大具有 maxSize 个元素的空队列。
    elements = new Type[maxSize]; //创建队列空间
    assert(elements != 0);        //断言: 动态存储分配成功与否
}
//插入函数
template <class Type>
void Queue<Type>::EnQueue(Type &item)
{
    assert(!IsFull());           //判队列是否不满，满则出错处理
    length++;                    //长度加 1
    rear = (rear + 1) % maxSize; //队尾位置进 1
    elements[rear] = item;       //进队列
}
//删除函数
template <class Type>
Type Queue<Type>::DeQueue()
{
    assert(!IsEmpty());                                   //判断队列是否不空，空则出错处理
    length--;                                             //队列长度减 1
    return elements[(rear - length + maxSize) % maxSize]; //返回原队头元素值
}
//读取队头元素值函数
template <class Type>
Type Queue<Type>::GetFront()
{
    assert(!IsEmpty());
    return elements[(rear - length + 1 + maxSize) % maxSize]; //返回队头元素值
}
