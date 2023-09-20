#pragma once
#include <iostream>
#define DefaultCap 10
#include "pch.h"
#include <sstream>

using namespace std;

namespace dsaUtils
{


	template <typename T>
	class SequencedList
	{

		using iterator = T*;		//ö��
	private:
		T* _items;					//���ݣ����������ֵ
		int _count;
		int _capacity;
	public:
		SequencedList(int max = DefaultCap)	//�ô�С����ʼ��
		{
			_items = new T[max];
			_count = 0;
			_capacity = max;
		}

		//template <typename IRT>
		SequencedList(int* first, int size)	//��ȡ��������
		{
			_count = size;
			_capacity = _count + DefaultCap;
			_items = new T[_capacity];
			for (int i = 0; i < size; i++)
			{
				_items[i] = *(first + i);
			}
		}

		SequencedList(const SequencedList& s)	//�����г�ʼ��
		{
			_count = s._count;
			_capacity = s._capacity;
			_items = new T[_capacity];
			for (int i = 0; i < s._count; i++)
			{
				_items[i] = s._items[i];
			}
		}

		SequencedList& operator = (const SequencedList s)	//���ں�
		{
			if (this != &s)
			{
				delete[] _items;
				_count = s._count;
				_capacity = s._capacity;
				_items = new T[_capacity];

				for (int i = 0; i < size; i++)
				{
					_items[i] = s._items[i];
				}
			}
		}

		~SequencedList()			//���������
		{
			delete[] _items;
		}

		int size() const			//��������
		{
			return _count;
		}

		bool empty() const
		{
			return _count == 0;
		}

		bool full(int cnt = 0) const
		{
			return _count + cnt >= _capacity;
		}

		void setCapacity(int newsize)		//�������������ܽض�
		{
			T* newspace = new T[newsize];
			if (_count > newsize)
			{
				_count = newsize;
			}

			for (int i = 0; i < _count; i++)
			{
				newspace[i] = _items[i];
			}
			delete[] _items;
			_items = newspace;
			_capacity = newsize;
		}

		const T& operator[](int i) const
		{
			if (i >= 0 && i < _count)
			{
				return _items[i];
			}
			else
			{
				throw out_of_range("�±�Խ��");
			}
		}

		T& operator[](int i)
		{
			if (i >= 0 && i < _count)
			{
				return _items[i];
			}
			else
			{
				throw out_of_range("�±�Խ��");
			}
		}

		bool contains(const T& k) const
		{
			int j = index(k);
			if (j != -1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		int index(const T& k) const	//��ȡ��ӦԪ�ص��±�
		{
			int j = 0;
			while (j < _count && _items[j] != k)
			{
				j++;
			}
			if (j == _count)
			{
				return -1;
			}
			else
			{
				return j;
			}
		}
		 
		void insert(int index, const T& k)	//���뵽i��λ��
		{
			if(full())
			{
				setCapacity(2 * _capacity);
			}
			if (index <0 || index > _count)
			{
				throw out_of_range("�±�Խ��");
			}
			else
			{
				for (int j = _count - 1; j >= index; j--)
				{
					_items[j + 1] = _items[j];
				}
			}
			_items[index] = k;
			_count++;
		}

		void push_back(const T& k)	//��ӵ�ĩβ
		{
			if (full())
			{
				setCapacity(2 * _capacity);
			}
			_items[_count] = k;
			_count++;
		}

		void remove(const T& k)		//ȥ��һ��Ԫ��
		{
			int i = index(k);
			if (k != -1)
			{
				for (int j = i + 1; j < _count; j++)
				{
					_items[j - 1] = _items[j];
				}
				_count--;
			}
			else
			{
				throw out_of_range("Ԫ�ز�����");
			}
		}
			
		friend ostream& operator<< (ostream& os, const SequencedList<T> s)	//�����ı�����ʽ
		{
			if (!s.empty())
			{
				for (int i = 0; i < s._count; i++)
				{
					os << s[i] << " ";
				}
			}
			return os;
		}

		string str(bool ShowType = false) const
		{
			ostringstream oss;
			if (ShowType)
			{
				oss << "SequencedList:";
			}
			for (int i = 0; i < _count; i++)
			{
				oss << _items[i] << " ";
			}
			return oss.str();
		}


		iterator begin() const	//��������Ҫ��
		{
			return _items;
		}

		iterator end() const
		{
			return _items + _count;
		}

	};
}