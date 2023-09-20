#include <iostream>
#include <time.h>
#include <stdlib.h>

template <typename T>
class SearchInArray
{
public:
	static int SequentialSearch(T* Arr, int Size, T ToFind)		//顺序查找
	/*
		查找成功ASL: N/2
		查找失败ASL: N
	
	*/
	{
		for (int i = 0; i < Size; i++)
		{
			if (*(Arr + i) == ToFind)
			{
				return i;						//找到返回位置
			}
		}
		return -1;				//没找到
	}

	static int BinarySearch(T* Arr, int Size, T ToFind)
	/*
		成功：((n+1) / n) * log2(n+1) - 1   ~~~ 或者画图计算
		失败：ceil(log2n)
		
	*/
	{
		int Start = 0;					//区段头，尾部，中间
		int End = Size - 1;
		int Mid;

		while (End >= Start)
		{
			Mid = (Start + End) / 2;
			if (*(Arr + Mid) == ToFind)
			{
				return Mid;							//刚好是中间
			}
			else if (*(Arr + Mid) > ToFind)			//二分法，确定头尾
			{
				End = Mid - 1;
			}
			else if (*(Arr + Mid) < ToFind)
			{
				Start = Mid + 1;
			}
		}
		if (*(Arr + Mid) < ToFind)
		{
			Mid++;
		}
		return ~Mid;									//没有
	}
	

};