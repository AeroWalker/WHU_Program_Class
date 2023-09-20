#include <iostream>
#include <time.h>
#include <stdlib.h>

template <typename T>
class SearchInArray
{
public:
	static int SequentialSearch(T* Arr, int Size, T ToFind)		//˳�����
	/*
		���ҳɹ�ASL: N/2
		����ʧ��ASL: N
	
	*/
	{
		for (int i = 0; i < Size; i++)
		{
			if (*(Arr + i) == ToFind)
			{
				return i;						//�ҵ�����λ��
			}
		}
		return -1;				//û�ҵ�
	}

	static int BinarySearch(T* Arr, int Size, T ToFind)
	/*
		�ɹ���((n+1) / n) * log2(n+1) - 1   ~~~ ���߻�ͼ����
		ʧ�ܣ�ceil(log2n)
		
	*/
	{
		int Start = 0;					//����ͷ��β�����м�
		int End = Size - 1;
		int Mid;

		while (End >= Start)
		{
			Mid = (Start + End) / 2;
			if (*(Arr + Mid) == ToFind)
			{
				return Mid;							//�պ����м�
			}
			else if (*(Arr + Mid) > ToFind)			//���ַ���ȷ��ͷβ
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
		return ~Mid;									//û��
	}
	

};