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

	HashSearchList(int SetLength = Seperate)			//���ݴ�С����Hash��
	{
		Length = SetLength;
		BaseList = new SLinkedList<T>*[Length];			//����
		for (int i = 0; i < Length; i++)
		{
			BaseList[i] = new SLinkedList<T>();			//����
		}
		
	}

	int Hash(T input)									//����hash
	{
		return input % Length;

	}

	void insert(T input)								//����
	{
		BaseList[Hash(input)]->insert(0, input);
	}

	void insert_Arr(T* input, int cnt)					//��������
	{
		for (int i = 0; i < cnt; i++)
		{
			BaseList[Hash(input[i])]->insert(0, input[i]);
		}
		
	}

	SLNode<T>* Find(T input)							//Ѱ�ң�û��null
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


	void show()											//���
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