#pragma once
#include <iostream>
#include <sstream>
#include <ostream>


namespace dsaUtils
{
	using namespace std;

	template <typename T>
	class SLNode
	{
	public:
		T item;				//储存元素
		SLNode<T>* next;	//向后指针

		SLNode(const T& k)
		{
			item = k;
			next = nullptr;
		}

		// 缺省
		SLNode()
		{
			item;
			next = nullptr;
		}


		//析构
		~SLNode()
		{

		}
	private:

	};

	template <typename T>
	class SLinkedListNH	//没有头的单向链表
	{
	public:
		SLNode<T>* _start = nullptr;	//直接指向第一个
		int _count;			//数目 

		SLinkedListNH()				//三种初始化
		{
			_count = 0;
		}

		SLinkedListNH(int size)
		{
			_count = size;
			SLNode<T>* p = nullptr;


			for (int i = 0; i < _count; i++) {
				SLNode<T>* q = new SLNode<T>();	//新建，连接，移动
				if (i == 0)
				{
					_start = q;		//因为没有头结点，需要单独判断是不是第一个
				}
				else
				{
					p->next = q;
				}
				p = q;
			}
		}

		SLinkedListNH(const T* first, int size) 
		{		
			_count = size;
			SLNode<T>* p = nullptr;
			for (int i = 0; i < _count; i++) {
				SLNode<T>* q = new SLNode<T>();	//新建，连接，移动
				if (i == 0)
				{
					_start = q;		//因为没有头结点，需要单独判断是不是第一个
				}
				else
				{
					p->next = q;
				}
				q->item = first[i];
				p = q;
			}
		}

		int count() const		//两个属性
		{
			return _count;
		}

		int size() const		//计数，这个正常工作
		{
			int n = 0;
			SLNode<T>* p = _start;
			while (p != nullptr)
			{
				n++;
				p = p->next;
			}
			return n;
		}

		bool empty() const	//判断为空
		{
			return((_start == nullptr) && (_count == 0));
		}

		~SLinkedListNH()	//析构函数
		{
			SLNode<T>* p = _start;
			SLNode<T>* q;
			while (p != nullptr)	//若p=null,说明之前的已经全部删除
			{
				q = p->next;		//走一个删一个
				delete p;
				p = q;
			}

		}

		SLNode<T>* findNode(int i) const	//找对应节点
		{	
			/*if (i == -1)				//没法直接返回head了，修改第一个过程内自行判断
			{
				SLNode<T> temp;
				temp.next = _start;
				return &temp;
			}*/

			if (i < 0 || i > _count)
			{
				return nullptr;
			}
			if (_start != nullptr)
			{
				int n = 0;						//下标从零开始
				SLNode<T>* p = _start;		//head.next 是第一个[0]

				while (n < i)
				{
					n++;
					p = p->next;
				}
				return p;
			}
			else
			{
				return nullptr;
			}

		}

		const T& operator [](int i) const	//方括弧引用
		{
			SLNode<T>* p = findNode(i);
			if (p == nullptr)
			{
				throw out_of_range("下标越界");
			}

			return p->item;
		}

		T& operator [] (int i)
		{
			SLNode<T>* p = findNode(i);
			if (p == nullptr)
			{
				throw out_of_range("下标越界");
			}

			return p->item;
		}

		friend ostream& operator<< (ostream& os, const SLinkedListNH& s)	
		{
			SLNode<T>* q = s._start;
			while (q != nullptr) {
				os << q->item << " -> ";
				q = q->next;
			}
			os << "|" << endl;
			return os;
		}

		void insert(int i, const T& item)	//插入
		{
			if (i == 0)	//如果插入的是第一个，需要修改_start，单独判断
			{
				SLNode<T>* t = new SLNode<T>(item);

				t->next = _start;
				_start = t;
				_count++;
				return;
			}

			SLNode<T>* before = findNode(i - 1);
			if (before == nullptr)
			{
				throw out_of_range("下标越界");
				exit(1);
			}

			SLNode<T>* t = new SLNode<T>(item);

			t->next = before->next;
			before->next = t;


			_count++;
		}

		void push_back(const T& item)
		{
			if (_count == 0)//如果插入的是第一个，需要修改_start，单独判断
			{
				SLNode<T>* t = new SLNode<T>(item);

				t->next = _start;
				_start = t;
				_count++;
				return;
			}
			SLNode<T>* rear = findNode(_count - 1);	

			SLNode<T>* t = new SLNode<T>(item);		//插入连接
			rear->next = t;
			t->next = nullptr;

			_count++;
		}

		void removeAt(int i)
		{
			if (i == 0)//如果插入的是第一个，需要修改_start，单独判断
			{
				if (_start == nullptr) throw out_of_range("越界");
				SLNode<T>* t = _start->next;
				delete _start;
				_start = t;

				_count--;
				return;
			}

			SLNode<T>* before = findNode(i - 1);	
			if (before == nullptr || before->next == nullptr)
			{
				throw out_of_range("下标越界");
			}

			SLNode<T>* pos = before->next;		//前后相接
			SLNode<T>* after = pos->next;
			before->next = after;


			delete pos;

			_count--;

		}
	};
};

