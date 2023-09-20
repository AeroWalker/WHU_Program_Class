#include <iostream>
#include <algorithm>
#include "../ex8p1/SearchInArray.cpp"
#define NormaLSize  50

using namespace std;
template <typename T>
class LinearSearchList
{
	T* List = nullptr;
	int Length;
	int Capacity;

public:
	LinearSearchList()					//���ֳ�ʼ��
	{
		List = new T[NormaLSize];
		Length = 0;
		Capacity = 50;
	}
	LinearSearchList(int setCapacity)		//ָ����С��ʼ��
	{
		List = new T[setCapacity];
		Length = 0;
		Capacity = setCapacity;
	}

	LinearSearchList(T* InputArr, int ArrSize)	//�������ʼ��
	{
		List = new T[ArrSize];
		for (int i = 0; i < ArrSize; i++)
		{
			List[i] = InputArr[i];
		}
		Length = ArrSize;
		Capacity = ArrSize;
	}

	void extend(int NewCapacity)			//����
	{
		T* NewList = new T[NewCapacity];
		for (int i = 0; i < NewCapacity && i < Length; i++)
		{
			NewList[i] = List[i];
		}
		delete[] List;
		List = NewList;
		Capacity = NewCapacity;
	}

	void push_back(T intput)		//add����
	{
		if (Length + 1 > Capacity)	//������������
		{
			extend( 2 * Capacity);
		}
		List[Length] = intput;
		Length++;
	}

	void Insert(int index,T intput)	//��������
	{
		if (index > Length)	//Խ��
		{
			return;
		}
		if (Length + 1 > Capacity)//������������
		{
			extend(2 * Capacity);
		}
		for (int i = Length; i > index; i++)	//Ų����
		{
			List[Length] = List[Length - 1];
		}
		List[index] = intput;
	}

	int indexOf(T ToFind)					//˳�����
	{
		for (int i = 0; i < Length; i++)
		{
			if (List[i] == ToFind) return i;
		}
		return -1;
	}

	int BinarySearch(T ToFind)			//���ֲ���
	{
		if (Length == 0) return -1;
		sort(List, List + Length - 1);
		int i = SearchInArray<T>::BinarySearch(List, Length, ToFind);
		return i;
	}

	T& operator[](int index)	//ȡ����
	{
		if (index >= Length)
		{
			throw("Out of Range");
		}
		return List[index];
	}

	void show()			//���
	{
		for (int i = 0; i < Length; i++)
			cout << List[i] << " ";
	}

	~LinearSearchList()
	{
		delete[] List;
	}


};