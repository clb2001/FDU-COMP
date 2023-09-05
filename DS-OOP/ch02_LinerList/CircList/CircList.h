#ifndef CIRCLIST_H
#define CIRCLIST_H
#include <iostream>
#include <cassert>
#ifndef INSMOD_INF_INR
#define INSMOD_INF_INR
enum InsMod {INF, INR};//��ǰ�����������
#endif
using namespace std;

template <typename T>class CircLinkNode{
public:
	T data;
	CircLinkNode<T> *link;
	CircLinkNode(CircLinkNode<T> *ptr = NULL){//�����ս��
		link = ptr;
	}
	CircLinkNode(const T &item, CircLinkNode<T> *ptr = NULL){//�����ǿս��
		data = item;
		link = ptr;
	}
};

template <typename T>class CircList{
public:
	CircList(){//�����и���ͷ���Ŀջ�����
		last = first = new CircLinkNode<T>;
		first->link = first;
	}
	CircList(const T &x){//ͷ����пɷ�������Ϣ
		last = first = new CircLinkNode<T>(x);
		first->link = first;
	}
	CircList(CircList<T> &L);//����һ��������
	~CircList()	{//��
		makeEmpty();
		delete first;//�ͷŸ���ͷ���
	}
	void makeEmpty();
	int Length()const;
	CircLinkNode<T> *getHead()const{//���������ƻ���װ��
		return first;
	}
	CircLinkNode<T> *Search(T x);
	CircLinkNode<T> *Locate(int i);
	bool getData(int i,T&x)const;
	void setData(int i, T &x);
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool IsEmpty()const{
		return (first->link == first)?true:false;
	}
	bool IsFull()const{//����������������Ϊ����˳���һ�£�����������
		return false;
	}
	void Sort();
	void Inverse();//��Ҫ����
	void input(T endTag, InsMod im = INR);
	void output();
	CircList<T> &operator = (CircList<T> &L);
	friend ostream& operator << (ostream &out, CircList<T> &L){
		CircLinkNode<T> *current = L.first->link;
		while (current != L.first){
			out << current->data <<'\t';
			current = current->link;
		}
		out<<endl;
		return out;
	}
	friend istream& operator >> (istream &in, CircList<T> &L){//�����������ݣ��������
		T val;
		L.makeEmpty();//�����
		while (!in.eof()){
			in >> val;
			L.last->link = new CircLinkNode<T>(val);
			assert(L.last->link);
			L.last = L.last->link;
		}
		L.last->link = L.first;
		in.clear(0);//����ctrl_Z���������رգ��������´�
		return in;
	}
protected:
	CircLinkNode<T> *first, *last;
	void inputFront(T endTag);
	void inputRear(T endTag);
};

template <typename T>CircList<T>::CircList(CircList<T> &L){
	T value;
	CircLinkNode<T> *srcptr = L.first;
	CircLinkNode<T> *destptr = first = new CircLinkNode<T>;
	while (srcptr->link != L.first)
	{
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	last = destptr;
	last->link = first;
}

template <typename T>void CircList<T>::makeEmpty(){//��
	CircLinkNode<T> *q;
	while (first->link != first){//���฽��ͷ���
		q = first->link;
		first->link = q->link;
		delete q;
	}
	last=first; //βָ�봦�������٣���������
}

template <typename T>int CircList<T>::Length()const{
	CircLinkNode<T> *p = first->link;
	int count = 0;
	while (p != first)
	{
		p = p->link;
		count++;
	}
	return count;
}

template <typename T>CircLinkNode<T> *CircList<T>::Search(T x){//��
	CircLinkNode<T> *current = first->link;
	while (current != first && current->data != x){
		current = current->link;
	}
	if(current==first) current=NULL;//δ�ҵ�����NULL�����ָ�����һ��
	return current;
}

template <typename T>CircLinkNode<T> *CircList<T>::Locate(int i){
	if (i < 0){
		return NULL;
	}
	if (i == 0){
		return first;
	}
	CircLinkNode<T> *current = first->link;
	int k = 1;
	while (current != first && k < i){
		current = current->link;
		k++;
	}
	return (k == i)?current:NULL;
}

template <typename T>bool CircList<T>::getData(int i,T&x)const{//�ģ���̲Ŀ���һ��
	if (i <= 0){
		return false;
	}
	CircLinkNode<T> *current = Locate(i);
	if (current == first || !current){
		return false;
	}
	else{
		x=current->data;
		return true;
	}
}

template <typename T>void CircList<T>::setData(int i, T &x){//�޸�ָ���������
	if (i <= 0)	return;
	CircLinkNode<T> *current = Locate(i);
	if (current == first || !current) return;
	else current->data = x;
}

template <typename T>bool CircList<T>::Insert(int i, T &x){//��������x�����Ľ������ڵ�i�Ž��֮��
	CircLinkNode<T> *current = Locate(i);
	if (current == NULL){
		return false;
	}
	CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
	if (!newNode)	{
		cerr << "Memory allocating error!" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	if (last->link != first){//�½������β����βָ��Ҫ�ƶ�
		last = last->link;
	}
	return true;
}

template <typename T>bool CircList<T>::Remove(int i, T &x){//ɾ����㣬����ȡ����
	CircLinkNode<T> *current = Locate(i-1);//��λ�ڴ�ɾ������ǰһ���
	if (!current || current->link == first)	return false;
	CircLinkNode<T> *del = current->link;
	if (del == last) last = current;//��ɾ���Ϊβ��㣬����βָ��
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template <typename T>void CircList<T>::output(){//���Դ�֮�Ե������ص�<<�����
	CircLinkNode<T> *current = first->link;
	while (current != first){
		cout << current->data << endl;
		current = current->link;
	}
}

template <typename T>CircList<T> &CircList<T>::operator = (CircList<T> &L){//�ģ�ԭ��������Ϊԭ����ֻ��һ��ͷָ��
	T value;
	CircLinkNode<T> *srcptr = L.first;
	makeEmpty();//Ӧ�����������������ͷ��㣬��ֵ����
	CircLinkNode<T> *destptr = first;
	while (srcptr->link != L.first)	{
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	last=destptr;//����βָ��
	destptr->link = first;
	return *this;
}

template <typename T>void CircList<T>::input(T endTag, InsMod im){
	if (im == INF){
		inputFront(endTag);
	}
	else{
		inputRear(endTag);
	}
}

template <typename T>void CircList<T>::inputFront(T endTag){//��ǰ����
	CircLinkNode<T> *newNode;
	T val;
	cin >> val;//��Ϊ�������󸽼�ͷ����Ѵ��ڣ�����Ϊ����ԭ�������������������
	while ( val != endTag){//endTag������ʶ
		newNode = new CircLinkNode<T>(val);
		if (!newNode){
			cerr << "Memory allocation error!" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		if (last== first)	last = last->link;//����ԭ�ǿ�������һ��Ҫ�޸�βָ��
		cin >> val;
	}
}

template <typename T>void CircList<T>::inputRear(T endTag){//������ɣ��Ѹ�
	T val;	
	cin >> val;
	rear = first;
	while (val != endTag){
		last->link = new CircLinkNode<T>(val);
		if (!newNode)		{
			cerr << "Memory allocating error!" << endl;
			exit(1);
		}
		last = newNode;
		cin >> val;
	}
	last->link = first;
}

template <typename T>void CircList<T>::Sort()
{
}

template <typename T>void CircList<T>::Inverse(){//��ת�����������뷵��
	CircLinkNode<T> *h, *p, *pr;
	h = first;//��תӦ����������ͷ��㣬����������
	p = first->link;
	last = p;
	while (p != first){
		pr = h;
		h = p;
		p = h->link;
		h->link = pr;
	}
	first->link = h;
}
#endif
