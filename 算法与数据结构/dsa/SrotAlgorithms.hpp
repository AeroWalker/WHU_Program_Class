#pragma once
#include <stdlib.h>
#include<time.h>
#include <iostream>

#include <windows.h>
namespace dsaUtils
{
	using namespace std;

	template <typename T>
	class MySort
	{
	public:
		static void RandArr(T* items, int size, int min = -99, int max = 99)	//���������
		{
			srand(rand());
			for (T* i = items; i < items + size; i++)
			{
				*i = rand() % (max - min + 1) + min;
			}
		}

		static void ShowArr(T* items, int size)									//���
		{
			for (T* i = items; i < items + size; i++)
			{
				cout << *i << "  ";
			}
			cout << endl;
		}

		static int GetRand(int max, int min = 0)
		{
			srand(time(0));
			return (rand() % (max - min + 1) + min);
		}


		static void InsertSort(T* items, int size)
			/*
			* ֱ�Ӳ�������
			* ʱ�临�Ӷ�O��N^2��i-ѭ��n��j-ÿ��ƽ���Ƚ�n/2���ƶ�n/2��
			* �ռ临�Ӷ�O��1��	ֻ��Ҫһ��Temp
			* �ȶ������������������һ����ֵ��嵽���棨��=����ڣ�
			*/
		{
			T temp;
			for (T* i = items + 1; i < items + size; i++)
			{
				temp = *i; //��֪��0��i���Ǵ�С��������ã��轫��*i����
				for (T* j = items; j < i; j++) //
				{
					if (temp < *j)//����0-i��ֱ���ҵ�λ��ʹ��temp<*i,��ζ��Ҫ��������
					{
						for (T* k = i - 1; k >= j; k--)//��i-1����ʼ��j������λ�ã����Ųһ��
						{
							*(k + 1) = *k;
						}
						*j = temp;//����
						break;
					}
				}
			}
		}

		static int BinarySearch(T& target, T* items, int size)	//���ֲ���
		{
			int left = 0;
			int right = size - 1;
			int mid = 0;

			while (left <= right) //Ѱ���������ͷû�н���
			{
				mid = (left + right) / 2;	//�ҵ��м�ֵ
				if (items[mid] == target) //�ոպ�
				{
					return mid;
				}
				if (items[mid] < target) //target���м�֮�����ƶ���߽�
				{
					left = mid + 1;
				}
				else //target��֮ǰ�����ƶ��ұ߽�
				{
					right = mid - 1;
				}
			}

			return -1; //û�ҵ�
		}

		static void Swap(T* a, T* b)
		{
			T temp;
			temp = *a;
			*a = *b;
			*b = temp;
		}

		static void ShellSort(T* items, int size)
			/*ϣ������
			* ʱ�临�Ӷ�O��n��log2n��^2����O��n^3/2��:����˵��
			* �ռ临�Ӷ�O��1��������temp��swap��
			* ���ȶ����򣺿���jump�պ�����ȥ��
			*/
		{
			int jump = size / 2;//��һ�뿪ʼ��

			while (jump > 0) //���һ����Ծ��1��֮�����
			{
				for (T* i = items + jump; i < items + size; i++) //��jump��ʼ������i����i-jump�Ƚ�
				{
					T* j = i;
					//Ϊʲô���˸�j�����*i < *i-jump��Ҫ���佻��
					//Ȼ���ٱȽ�i - jump��i-2jump��ֱ����������λ�ô��*i
					while (j - jump >= items)
					{
						//�ⲿ�־���һֱ��ǰ�Ƚϣ�ֱ������������λ��
						//֮ǰ������(i - jump)�Ѿ���С����źã�����ֻҪ���ϾͿ����˳���
						if (*(j - jump) > *j)
						{
							Swap(j - jump, j);
							j -= jump;
						}
						else
						{
							break;
						}
					}
				}
				jump /= 2; //���ú�jump��׼����һ�ֱȽ�
			}
		}

		static void BubbleSort(T* items, int size)
			/*
			* ð������
			* ʱ�临�Ӷ�O(n^2)��i-��ǰ����ÿһλn��j-��ǰ��Ƚ�n-i�Σ�
			* �ռ临�Ӷ�O(1)
			* �ȶ������������ֵ��ȣ���ǰ�����ð�ݻῨ��ǰ��
			*/
		{
			for (T* i = items + size - 1; i > items; i--)//��ǰ����ð��
			{
				bool exchanged = false; //�����0����i-1��֮�仹��û�н���
				for (T* j = items; j < i; j++) //�������
				{
					if (*j > *(j + 1)) //ð��
					{
						Swap(j, j + 1);
						//cout << *j << *(j + 1) << endl;
						exchanged = true; //����н���
					}
				}
				if (!exchanged) break; //���û�н�����˵��i-1֮ǰ�Ѿ��ź�����
			}
		}

		static void QuickSort(T* items, int size)
			/*
			* ��������
			* ʱ�临�Ӷ�O(n^2) �� O(nLog2n)��ԭ���鰴�Ӵ�С˳�����У���Ҫ�ݹ�i=(n-1)�㣬ÿһ����Ҫ˫�����(n-i)���õ�O(n^2)
			*								��������£�ֱ�Ӷ��֣��ݹ�i=��log2n���㣬ÿһ�㣨���������ͬ��һ������n����
			* �ռ临�Ӷ�O(log2n)����������£������log2(n+1)��ݹ�(���ֳ���Ϊ0ʱ��)��ÿһ���ݹ鶼��Ҫһ����������
			* ���ȶ������������ֵ��ȣ�����ͬʱ������spliter��һ�࣬�ᱻ����
			*/
		{
			if (size > 0)	//û����ֱ�ӷ��أ�������
			{
				T* splitP = Spliter(items,size);	//���÷ֶη������õ��ֶε�ָ��
				T* leftP = items;					//һ����ͷһ��ĩβ
				T* rightP = items + size - 1;		
				QuickSort(leftP, splitP - leftP);		//���������У���һ����[Start,splitP - 1]������ΪsplitP-leftP
				QuickSort(splitP + 1, rightP - splitP);	//�ڶ�����[splitP+1��leftP]��������rightP - splitP
			}

		}

		static T* Spliter(T* items, int size)
		{
			if (size > 0)	//���ȴ���0���ָܷ�
			{
				T refP = *(items);			//��׼ֱֵ�ӵ�һ��
				T* leftP = items + 1;
				T* rightP = items + size - 1;		//�����ָ��,��������һ��ֵ����׼�ˣ�ʹ�õڶ���

				while (leftP <= rightP)								//ֻҪ����ָ���ཻ�棺�Ѿ�ȫ�������������ˣ��˴���Ҫ�Ⱥţ��������ֲ�һ��û���������
				{
					for (; leftP <= rightP && *leftP < refP; leftP++);		//˫����ң�ֱ��left�ҵ���ref��ģ�right�ҵ���refС��
					for (; leftP <= rightP && *rightP > refP; rightP--);	//�˴�����Ҫ�Ⱥţ����ܱ�֤ȫ������
					if (leftP <= rightP)		//�����߻�δ����ʱ��ʱ���Խ����ģ����ϵ��ں�:������� 1 0 1 ���У�left����ڶ���1��rightҲ�ڵڶ���1��*rightP = refP�����������Ӧ������
					{
						Swap(leftP, rightP);
						leftP++;
						rightP--;
					}
				}
				Swap(items, rightP);//��right����
				/*
				����ѭ�����������
				��for (; leftP <= rightP && *leftP < refP; leftP++);������
					��ʱ��rightPָ��һ��С��ref�����֣�leftP����rightP��ָ��һ�´���ref������
					����Ӧ�ð�right��������һ��
				��for (; leftP <= rightP && *rightP > refP; rightP--);
					��ʱ��leftPָ��һ������ref�����֣�rightP��LeftP֮ǰ��ָ��һ��С��ref������
				��if (leftP < rightP){Swap}֮��
					������right��ǰ�����ڽ�����rightָ��Сֵ
				*/
				return rightP;
			}
			return nullptr;
		}

		static void SelectSort(T* items, int size)
			/*
			ֱ��ѡ������
			ʱ�临�Ӷ�O(n^2):��ѭ��iѭ��n�Σ���ѭ��jѭ��n-i�Σ���һ��n(n-1)/2
			�ռ临�Ӷ�O(1):ֻ��Ҫһ��temp�����ռ�
			���ȶ����򣺳���������ֵͬ��������ǻᱻ��һ��ˢ�£�������˳��ı�
			*/
		{
			T* exchange = nullptr;	//���ѭ���г��ֵ���Сֵ

			for (T* i = items; i < items + size; i++)	//��һ��ѭ����ȷ��ѡ��󽻻���λ��
			{
				exchange = i;
				for (T* j = i; j < items + size; j++)	//�ڶ���ѭ����ȷ����ѡ������е���Сֵ
				{
					if (*j < *exchange)			//���ָ�С�ģ���ˢ�±��
					{
						exchange = j;
					}
				}
				Swap(i, exchange);				//����
			}
		}

		static void MergeSort(T* items, int size)
			/*
			�鲢����
			ʱ�临�Ӷ�O(nlog2n):lenָ������������Ҫi = log2n�ε�Mergepass��j-ÿ��mergepassѭ��ȫ���ַ���=n
			�ռ临�Ӷ�O(n):temp
			�ȶ����򣺳���������ֵͬ����ͬ�������������1.�ֵ�һ���Ӷ��У���Ȼ���ı����˳��2.�ֵ����������У���������ĳһ������ʱ��
			*/
		{
			int len = 1;
			T* temp = new T[size];

			do
			{
				MergePass(items, temp, size, len);	//��items�鲢��temp
				len *= 2;
				MergePass(temp, items, size, len);	//�ٹ鲢����
				len *= 2;							//ÿһ�γ��ȶ��ӱ�

			} while (len < size);

				delete[] temp;						//GC

		}

		static void MergePass(T* items, T* temp, int size, int len)	//ȷ��len֮�󣬽��й鲢
		{
			int i = 0;					//ÿ�ε�һ�����е�ͷ��i+len,�ڶ������е�ͷ
			while (i < size - 2 * len)
			{
				Merge(items, temp, size, i, i + len, len);	//�����������й鲢
				i += 2  *len;
			}

			//����ʣ�²�������������
			if (i + len < size) 
			{
				Merge(items, temp, size, i, i + len, len);	//���ڹ�һ�����У�������������
			}
			else
			{
				for (int j = i; j < size; j++)			//һ��������
				{
					temp[j] = items[j];
				}
			}
			//���Mergeѭ����һ���ж� i < size ���Ҿ��ÿ��Բ����ж�ֱ��ѭ����
			//while (i < size )
			//{
			//	Merge(items, temp, size, i, i + len, len);	//�����������й鲢
			//	i += 2 * len;
			//}
		}

		static void Merge(T* items, T* temp, int size, int start1, int start2, int len) //һ���򵥵Ĺ鲢����
		{
			int i = start1, j = start2 , k = start1;
			while (i < start1 + len && j < start2 + len && i < size && j < size)	//��i��j��������һ��С�����
			{
				if (items[i] <= items[j])	//������ڵĻ���Ӧ����д��items[i]��?
				{
					temp[k] = items[i];
					i++;
				}
				else
				{
					temp[k] = items[j];
					j++;
				}
				k++;
			}
			while (i < start1 + len && i < size)	//û�������������
			{
				temp[k] = items[i];
				i++;
				k++;
			}
			while (j < start2 + len && j < size)
			{
				temp[k] = items[j];
				j++;
				k++;
			}
		}
	};
}