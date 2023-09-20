#pragma once
#include <iostream>
#include "pch.h"
#include <sstream>
#include <ostream>


namespace dsaUtils
{
	using namespace std;

	template <typename T>
	class SLNode			//一个节点
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
	class SLinkedList
	{
	public:
		SLNode<T>* _head;	//头结点
		int _count;			//数目 

		SLinkedList()
		{
			_count = 0;
			_head = new SLNode<T>(); //仅初始化头结点
		}

		SLinkedList(int size)
		{
			_count = size;
			_head = new SLNode<T>(); //仅初始化头结点
			SLNode<T>* p = _head;
			for (int i = 0; i < _count; i++) 
			{
				SLNode<T>* q = new SLNode<T>();	//新建，连接，移动
				p->next = q;
				p = q;
			}
		}

		SLinkedList(const T* first, int cnt)	//利用数组进行初始化
		{	
			_count = cnt;			// 长度
			_head = new SLNode<T>();//头结点

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(first[i]);	//新建，连接，移动
				p->next = q;
				p = q;
			}
		}

		SLinkedList(const SLinkedList& s)			//复制
		{
			_count = s._count;			// 长度
			_head = new SLNode<T>();//头结点

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(s[i]);	//新建，连接，移动
				p->next = q;
				p = q;
			}
		}

		SLinkedList& operator=(const SLinkedList& s)//等号复制
		{
			_count = s._count;			// 长度
			_head = new SLNode<T>();//头结点

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(s[i]);	//新建，连接，移动
				p->next = q;
				p = q;
			}
		}

		int count() const		//返回大小
		{
			return _count;
		}

		int size() const	//从头遍历一遍，计算大小
		{		
			int n = 0;
			SLNode<T>* p = _head->next;
			while (p != nullptr)
			{
				n++;
				p = p->next;
			}
			return n;
		}

		bool empty() const  //判断是否为空
		{
			return((_head->next == nullptr) && (_count == 0));
		}

		~SLinkedList()
		{
			SLNode<T>* p = _head;
			SLNode<T>* q;
			while (p != nullptr)	//若p=null,说明之前的已经全部删除
			{
				q = p->next;		//走一个删一个
				delete p;
				p = q;
			}

		}

		SLNode<T>* findNode(int i) const	//找到下标i的数字
		{
			if (i == -1) return _head;		//优化一下，[0]个的下标是head，直接访问即可

			if (i < 0 || i > _count)
			{
				return nullptr;
			}
			int n = 0;						//下标从零开始
			SLNode<T>* p = _head->next;		//head.next 是第一个[0]

			while (n < i)
			{
				n++;
				p = p->next;
			}
			return p;
		}

		SLNode<T>* Find(T input) 	//找到下标i的数字
		{
			SLNode<T>* p = _head->next;		//head.next 是第一个[0]

			while (p != nullptr)
			{
				if (p->item == input)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
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

		void show(bool showTypeName = false)	//转文本
		{
			if (showTypeName)cout << "SLinkedList:  ";

			SLNode<T>* q = _head->next;
			while (q != nullptr) {
				cout << q->item << " -> ";
				q = q->next;
			}
			cout << "|" << endl;
		}


		friend ostream& operator<< (ostream& os, const SLinkedList& s)
		{
			SLNode<T>* q = s._head->next;
			while (q != nullptr) {
				os << q->item << " -> ";
				q = q->next;
			}
			os << "|" << endl;
			return os;
		}

		void insert(int i, const T& item)	//插入
		{
			SLNode<T>* before = findNode(i - 1);	//可以优化一个findNode，使其 -1 => _head即可简化找到前一个的操作
			if (before == nullptr)					//越界或太靠前
			{
				throw out_of_range("下标越界");
			}

			SLNode<T>* t = new SLNode<T>(item);		//新建

			t->next = before->next;					//前面指向t，t指向后一个
			before->next = t;


			_count++;
		}

		void push_back(const T& item)				//插入末尾
		{
			SLNode<T>* rear = findNode(_count - 1);	//找到最后一个,直接复用得了 -1 => _head

			SLNode<T>* t = new SLNode<T>(item);		//插入连接
			rear->next = t;
			t->next = nullptr;

			_count++;
		}

		void removeAt(int i)						//移除一个
		{
			SLNode<T>* before = findNode(i - 1);	//找到最后一个,直接复用得了 -1 => _head
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

		void reverse()				//翻转
		{
			SLNode<T>* i = nullptr;	//前中后三个节点
			SLNode<T>* j = _head->next;
			SLNode<T>* k = nullptr;

			while (j != nullptr)
			{
				k = j->next;	//k保存一下下一个
				j->next = i;	//把j指向前一个
				i = j;			//向前移动一个
				j = k;
			}

			_head->next = i;	//连接头
		}


	};

};

