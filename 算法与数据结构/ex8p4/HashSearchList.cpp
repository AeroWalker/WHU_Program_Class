#include <iostream>
#include <stdlib.h>
#include "../dsa/SingleLinkedList.hpp"
using namespace std;
using namespace dsaUtils;

#define Seperate 10

template <typename T>
class HashSearchList
{
public:
	SLinkedList<T>** BaseList;
	int Length;

	HashSearchList(int SetLength = Seperate)			//根据大小创建Hash表
	{
		Length = SetLength;
		BaseList = new SLinkedList<T>*[Length];			//主表
		for (int i = 0; i < Length; i++)
		{
			BaseList[i] = new SLinkedList<T>();			//链表
		}
		
	}

	int Hash(T input)									//计算hash
	{
		return input % Length;

	}

	void insert(T input)								//插入
	{
		BaseList[Hash(input)]->insert(0, input);
	}

	void insert_Arr(T* input, int cnt)					//连续插入
	{
		for (int i = 0; i < cnt; i++)
		{
			BaseList[Hash(input[i])]->insert(0, input[i]);
		}
		
	}

	SLNode<T>* Find(T input)							//寻找，没有null
	{
		return BaseList[Hash(input)]->Find(input);
	}

	bool contains(T input)
	{
		if (Find(input) != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	void show()											//输出
	{
		for (int i = 0; i < Length; i++)
		{
			cout << "Hash:" << i << "->";
			
			cout << *BaseList[i];
			cout << endl;
		}
	}
	
	~HashSearchList()
	{
		
		for (int i = 0; i < Length; i++)
		{
			delete BaseList[i];
		}
		delete[] BaseList;
	}

};