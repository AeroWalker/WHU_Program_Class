#include "../dsa/SingleLinkedList.hpp"
#include <iostream>
#include <sstream>

using namespace dsaUtils;

template <typename T>
class LoopSingleLinkedList	//һ��ѭ����������Ϊ��Ҫ���ܲ��Ǻܶ࣬��д�˳�ʼ���ͷ���
{
public:
	SLNode<T>* _head;		//ͷ��β��
	SLNode<T>* _rear;
	int _count;

	//int _count = this->_count;
	//SLNode<T>* _head = this->_head;

	LoopSingleLinkedList(const T* first, int cnt) //���������ʼ��
	{	
		_count = cnt;			// ����
		_head = new SLNode<T>();//ͷ���

		SLNode<T>* p = _head;
		SLNode<T>* q;

		for (int i = 0; i < _count; i++) {
			q = new SLNode<T>(first[i]);	//�½������ӣ��ƶ�
			p->next = q;
			p = q;
		}
		_rear = p;					//���β�ͣ�����ͷ��
		p->next = _head->next;
	}

	SLNode<T>* irtp = nullptr;		//һ��������
	T* irt()						//ÿ�η��ʽ���һ����������
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

	~LoopSingleLinkedList()		//����
	{
		SLNode<T>* p = _head;
		SLNode<T>* q;
		while (p != _rear)	//��p=rear,˵��֮ǰ���Ѿ�ȫ��ɾ��
		{
			q = p->next;		//��һ��ɾһ��
			delete p;
			p = q;
		}
		delete _rear;			//��β��ɾ��

	}

};