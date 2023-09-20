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
	class SLinkedListNH	//û��ͷ�ĵ�������
	{
	public:
		SLNode<T>* _start = nullptr;	//ֱ��ָ���һ��
		int _count;			//��Ŀ 

		SLinkedListNH()				//���ֳ�ʼ��
		{
			_count = 0;
		}

		SLinkedListNH(int size)
		{
			_count = size;
			SLNode<T>* p = nullptr;


			for (int i = 0; i < _count; i++) {
				SLNode<T>* q = new SLNode<T>();	//�½������ӣ��ƶ�
				if (i == 0)
				{
					_start = q;		//��Ϊû��ͷ��㣬��Ҫ�����ж��ǲ��ǵ�һ��
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
				SLNode<T>* q = new SLNode<T>();	//�½������ӣ��ƶ�
				if (i == 0)
				{
					_start = q;		//��Ϊû��ͷ��㣬��Ҫ�����ж��ǲ��ǵ�һ��
				}
				else
				{
					p->next = q;
				}
				q->item = first[i];
				p = q;
			}
		}

		int count() const		//��������
		{
			return _count;
		}

		int size() const		//�����������������
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

		bool empty() const	//�ж�Ϊ��
		{
			return((_start == nullptr) && (_count == 0));
		}

		~SLinkedListNH()	//��������
		{
			SLNode<T>* p = _start;
			SLNode<T>* q;
			while (p != nullptr)	//��p=null,˵��֮ǰ���Ѿ�ȫ��ɾ��
			{
				q = p->next;		//��һ��ɾһ��
				delete p;
				p = q;
			}

		}

		SLNode<T>* findNode(int i) const	//�Ҷ�Ӧ�ڵ�
		{	
			/*if (i == -1)				//û��ֱ�ӷ���head�ˣ��޸ĵ�һ�������������ж�
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
				int n = 0;						//�±���㿪ʼ
				SLNode<T>* p = _start;		//head.next �ǵ�һ��[0]

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

		void insert(int i, const T& item)	//����
		{
			if (i == 0)	//���������ǵ�һ������Ҫ�޸�_start�������ж�
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
				throw out_of_range("�±�Խ��");
				exit(1);
			}

			SLNode<T>* t = new SLNode<T>(item);

			t->next = before->next;
			before->next = t;


			_count++;
		}

		void push_back(const T& item)
		{
			if (_count == 0)//���������ǵ�һ������Ҫ�޸�_start�������ж�
			{
				SLNode<T>* t = new SLNode<T>(item);

				t->next = _start;
				_start = t;
				_count++;
				return;
			}
			SLNode<T>* rear = findNode(_count - 1);	

			SLNode<T>* t = new SLNode<T>(item);		//��������
			rear->next = t;
			t->next = nullptr;

			_count++;
		}

		void removeAt(int i)
		{
			if (i == 0)//���������ǵ�һ������Ҫ�޸�_start�������ж�
			{
				if (_start == nullptr) throw out_of_range("Խ��");
				SLNode<T>* t = _start->next;
				delete _start;
				_start = t;

				_count--;
				return;
			}

			SLNode<T>* before = findNode(i - 1);	
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
	};
};

