#include "../dsa/SingleLinkedList.hpp"
#include <iostream>
#include <sstream>

using namespace dsaUtils;

template <typename T>
class LoopSingleLinkedList	//一个循环单链表，因为需要功能不是很多，就写了初始化和访问
{
public:
	SLNode<T>* _head;		//头和尾部
	SLNode<T>* _rear;
	int _count;

	//int _count = this->_count;
	//SLNode<T>* _head = this->_head;

	LoopSingleLinkedList(const T* first, int cnt) //利用数组初始化
	{	
		_count = cnt;			// 长度
		_head = new SLNode<T>();//头结点

		SLNode<T>* p = _head;
		SLNode<T>* q;

		for (int i = 0; i < _count; i++) {
			q = new SLNode<T>(first[i]);	//新建，连接，移动
			p->next = q;
			p = q;
		}
		_rear = p;					//标记尾巴，连接头部
		p->next = _head->next;
	}

	SLNode<T>* irtp = nullptr;		//一个迭代器
	T* irt()						//每次访问进行一个迭代操作
	{
		if (_count == 0) return new T();
		if (irtp == nullptr)
		{
			irtp = _head->next;
		}
		else
		{
			irtp = irtp->next;
		}
		return &(irtp->item);
	}

	~LoopSingleLinkedList()		//析构
	{
		SLNode<T>* p = _head;
		SLNode<T>* q;
		while (p != _rear)	//若p=rear,说明之前的已经全部删除
		{
			q = p->next;		//走一个删一个
			delete p;
			p = q;
		}
		delete _rear;			//把尾巴删了

	}

};