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

		using iterator = T*;		//枚举
	private:
		T* _items;					//内容，计数，最大值
		int _count;
		int _capacity;
	public:
		SequencedList(int max = DefaultCap)	//用大小来初始化
		{
			_items = new T[max];
			_count = 0;
			_capacity = max;
		}

		//template <typename IRT>
		SequencedList(int* first, int size)	//读取其他容器
		{
			_count = size;
			_capacity = _count + DefaultCap;
			_items = new T[_capacity];
			for (int i = 0; i < size; i++)
			{
				_items[i] = *(first + i);
			}
		}

		SequencedList(const SequencedList& s)	//用现有初始化
		{
			_count = s._count;
			_capacity = s._capacity;
			_items = new T[_capacity];
			for (int i = 0; i < s._count; i++)
			{
				_items[i] = s._items[i];
			}
		}

		SequencedList& operator = (const SequencedList s)	//等于号
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

		~SequencedList()			//把数组回收
		{
			delete[] _items;
		}

		int size() const			//三个属性
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

		void setCapacity(int newsize)		//设置容量，可能截断
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
				throw out_of_range("下标越界");
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
				throw out_of_range("下标越界");
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

		int index(const T& k) const	//获取对应元素的下标
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
		 
		void insert(int index, const T& k)	//插入到i的位置
		{
			if(full())
			{
				setCapacity(2 * _capacity);
			}
			if (index <0 || index > _count)
			{
				throw out_of_range("下标越界");
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

		void push_back(const T& k)	//添加到末尾
		{
			if (full())
			{
				setCapacity(2 * _capacity);
			}
			_items[_count] = k;
			_count++;
		}

		void remove(const T& k)		//去除一个元素
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
				throw out_of_range("元素不存在");
			}
		}
			
		friend ostream& operator<< (ostream& os, const SequencedList<T> s)	//两种文本化方式
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


		iterator begin() const	//迭代器需要的
		{
			return _items;
		}

		iterator end() const
		{
			return _items + _count;
		}

	};
}