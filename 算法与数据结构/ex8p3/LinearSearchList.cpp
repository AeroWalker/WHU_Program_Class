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
	LinearSearchList()					//两种初始化
	{
		List = new T[NormaLSize];
		Length = 0;
		Capacity = 50;
	}
	LinearSearchList(int setCapacity)		//指定大小初始化
	{
		List = new T[setCapacity];
		Length = 0;
		Capacity = setCapacity;
	}

	LinearSearchList(T* InputArr, int ArrSize)	//从数组初始化
	{
		List = new T[ArrSize];
		for (int i = 0; i < ArrSize; i++)
		{
			List[i] = InputArr[i];
		}
		Length = ArrSize;
		Capacity = ArrSize;
	}

	void extend(int NewCapacity)			//扩容
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

	void push_back(T intput)		//add数据
	{
		if (Length + 1 > Capacity)	//不够先扩个容
		{
			extend( 2 * Capacity);
		}
		List[Length] = intput;
		Length++;
	}

	void Insert(int index,T intput)	//插入数据
	{
		if (index > Length)	//越界
		{
			return;
		}
		if (Length + 1 > Capacity)//不够先扩个容
		{
			extend(2 * Capacity);
		}
		for (int i = Length; i > index; i++)	//挪数据
		{
			List[Length] = List[Length - 1];
		}
		List[index] = intput;
	}

	int indexOf(T ToFind)					//顺序查找
	{
		for (int i = 0; i < Length; i++)
		{
			if (List[i] == ToFind) return i;
		}
		return -1;
	}

	int BinarySearch(T ToFind)			//二分查找
	{
		if (Length == 0) return -1;
		sort(List, List + Length - 1);
		int i = SearchInArray<T>::BinarySearch(List, Length, ToFind);
		return i;
	}

	T& operator[](int index)	//取数据
	{
		if (index >= Length)
		{
			throw("Out of Range");
		}
		return List[index];
	}

	void show()			//输出
	{
		for (int i = 0; i < Length; i++)
			cout << List[i] << " ";
	}

	~LinearSearchList()
	{
		delete[] List;
	}


};