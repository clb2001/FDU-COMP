#ifndef CIRSQUEUE_H_
#define CIRSQUEUE_H_
#include <iostream>

using namespace std;

template <class T>
class CirsQueue
{
private:
    int front;
    int rear;
    T *elements;
    int maxSize;

public:
    CirsQueue(int sz = 10);
    ~CirsQueue();
    void EnQueue(const T &x);
    bool DeQueue(T &x);
    void initiaQueue(int n);
};

template <class T>
CirsQueue<T>::CirsQueue(int sz)
{
    maxSize = sz;
    elements = new T[maxSize];
    front = rear = 0;
}

template <class T>
CirsQueue<T>::~CirsQueue()
{
    delete[] elements;
}

template <class T>
void CirsQueue<T>::EnQueue(const T &x)
{
    if (rear % maxSize == front)
    {
        cout << "队列已满，进行扩容！" << endl;
        T *temp = new T[maxSize * 2];
        for (int i = 0; i < maxSize; i++)
        {
            temp[i] = elements[i];
        }
        delete[] elements;
        elements = temp;
        rear = (rear + 1) % (maxSize * 2);
        elements[rear] = x;
        cout << "新的队列已建好！" << endl;
    }
    else
    {
        elements[rear] = x;
        rear = (rear + 1) % maxSize;
    }
}

template <class T>
bool CirsQueue<T>::DeQueue(T &x)
{
    if (front == rear)
    {
        cout << "队列为空！缩小队列空间为原来的1/2！" << endl;
        T *temp = new T[maxSize / 2];
        delete[] elements;
        elements = temp;
        cout << "队列已缩短为原来的1/2！" << endl;
        return false;
    }
    else
    {
        x = elements[rear];
        front = (front + 1) % maxSize;
        if ((rear - front) < (maxSize / 4))
        {
            cout << "把原来的队列缩短为原来的1/2" << endl;
            T *tem = new T[maxSize / 2];
            for (int i = 0; i <= rear; i++)
            {
                tem[i] = elements[i];
            }
            delete[] elements;
            elements = tem;
            return true;
        }
        return true;
    }
}

template <class T>
void CirsQueue<T>::initiaQueue(int n)
{
    T value;
    if (n > maxSize)
    {
        cout << "初始化时请勿超出容量" << endl;
    }
    else if (n == 0)
    {
        cout << "输入队列数不能为0" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << "请输入第" << i + 1 << "个值： ";
            cin >> value;
            elements[i] = value;
            rear = (rear + 1) % maxSize;
        }

        cout << "队列初始化成功！共含有" << n << "个值在队列中！" << endl;
    }
}
#endif