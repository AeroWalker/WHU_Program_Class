#pragma once
#include <iostream>
#include "pch.h"
#include <sstream>
#include <ostream>


namespace dsaUtils
{
	using namespace std;

	template <typename T>
	class SLNode			//һ���ڵ�
	{
	public:
		T item;				//����Ԫ��
		SLNode<T>* next;	//���ָ��

		SLNode(const T& k)
		{
			item = k;
			next = nullptr;
		}

		// ȱʡ
		SLNode()
		{
			item;
			next = nullptr;
		}


		//����
		~SLNode()
		{

		}
	private:

	};

	template <typename T>
	class SLinkedList
	{
	public:
		SLNode<T>* _head;	//ͷ���
		int _count;			//��Ŀ 

		SLinkedList()
		{
			_count = 0;
			_head = new SLNode<T>(); //����ʼ��ͷ���
		}

		SLinkedList(int size)
		{
			_count = size;
			_head = new SLNode<T>(); //����ʼ��ͷ���
			SLNode<T>* p = _head;
			for (int i = 0; i < _count; i++) 
			{
				SLNode<T>* q = new SLNode<T>();	//�½������ӣ��ƶ�
				p->next = q;
				p = q;
			}
		}

		SLinkedList(const T* first, int cnt)	//����������г�ʼ��
		{	
			_count = cnt;			// ����
			_head = new SLNode<T>();//ͷ���

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(first[i]);	//�½������ӣ��ƶ�
				p->next = q;
				p = q;
			}
		}

		SLinkedList(const SLinkedList& s)			//����
		{
			_count = s._count;			// ����
			_head = new SLNode<T>();//ͷ���

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(s[i]);	//�½������ӣ��ƶ�
				p->next = q;
				p = q;
			}
		}

		SLinkedList& operator=(const SLinkedList& s)//�ȺŸ���
		{
			_count = s._count;			// ����
			_head = new SLNode<T>();//ͷ���

			SLNode<T>* p = _head;
			SLNode<T>* q;

			for (int i = 0; i < _count; i++) 
			{
				q = new SLNode<T>(s[i]);	//�½������ӣ��ƶ�
				p->next = q;
				p = q;
			}
		}

		int count() const		//���ش�С
		{
			return _count;
		}

		int size() const	//��ͷ����һ�飬�����С
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

		bool empty() const  //�ж��Ƿ�Ϊ��
		{
			return((_head->next == nullptr) && (_count == 0));
		}

		~SLinkedList()
		{
			SLNode<T>* p = _head;
			SLNode<T>* q;
			while (p != nullptr)	//��p=null,˵��֮ǰ���Ѿ�ȫ��ɾ��
			{
				q = p->next;		//��һ��ɾһ��
				delete p;
				p = q;
			}

		}

		SLNode<T>* findNode(int i) const	//�ҵ��±�i������
		{
			if (i == -1) return _head;		//�Ż�һ�£�[0]�����±���head��ֱ�ӷ��ʼ���

			if (i < 0 || i > _count)
			{
				return nullptr;
			}
			int n = 0;						//�±���㿪ʼ
			SLNode<T>* p = _head->next;		//head.next �ǵ�һ��[0]

			while (n < i)
			{
				n++;
				p = p->next;
			}
			return p;
		}

		SLNode<T>* Find(T input) 	//�ҵ��±�i������
		{
			SLNode<T>* p = _head->next;		//head.next �ǵ�һ��[0]

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

		const T& operator [](int i) const	//����������
		{
			SLNode<T>* p = findNode(i);
			if (p == nullptr)
			{
				throw out_of_range("�±�Խ��");
			}

			return p->item;
		}

		T& operator [] (int i)
		{
			SLNode<T>* p = findNode(i);
			if (p == nullptr)
			{
				throw out_of_range("�±�Խ��");
			}

			return p->item;
		}

		void show(bool showTypeName = false)	//ת�ı�
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

		void insert(int i, const T& item)	//����
		{
			SLNode<T>* before = findNode(i - 1);	//�����Ż�һ��findNode��ʹ�� -1 => _head���ɼ��ҵ�ǰһ���Ĳ���
			if (before == nullptr)					//Խ���̫��ǰ
			{
				throw out_of_range("�±�Խ��");
			}

			SLNode<T>* t = new SLNode<T>(item);		//�½�

			t->next = before->next;					//ǰ��ָ��t��tָ���һ��
			before->next = t;


			_count++;
		}

		void push_back(const T& item)				//����ĩβ
		{
			SLNode<T>* rear = findNode(_count - 1);	//�ҵ����һ��,ֱ�Ӹ��õ��� -1 => _head

			SLNode<T>* t = new SLNode<T>(item);		//��������
			rear->next = t;
			t->next = nullptr;

			_count++;
		}

		void removeAt(int i)						//�Ƴ�һ��
		{
			SLNode<T>* before = findNode(i - 1);	//�ҵ����һ��,ֱ�Ӹ��õ��� -1 => _head
			if (before == nullptr || before->next == nullptr)
			{
				throw out_of_range("�±�Խ��");
			}

			SLNode<T>* pos = before->next;		//ǰ�����
			SLNode<T>* after = pos->next;
			before->next = after;


			delete pos;

			_count--;

		}

		void reverse()				//��ת
		{
			SLNode<T>* i = nullptr;	//ǰ�к������ڵ�
			SLNode<T>* j = _head->next;
			SLNode<T>* k = nullptr;

			while (j != nullptr)
			{
				k = j->next;	//k����һ����һ��
				j->next = i;	//��jָ��ǰһ��
				i = j;			//��ǰ�ƶ�һ��
				j = k;
			}

			_head->next = i;	//����ͷ
		}


	};

};

