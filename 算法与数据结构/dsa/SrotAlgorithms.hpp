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
		static void RandArr(T* items, int size, int min = -99, int max = 99)	//生成随机数
		{
			srand(rand());
			for (T* i = items; i < items + size; i++)
			{
				*i = rand() % (max - min + 1) + min;
			}
		}

		static void ShowArr(T* items, int size)									//输出
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
			* 直接插入排序
			* 时间复杂度O（N^2）i-循环n（j-每次平均比较n/2，移动n/2）
			* 空间复杂度O（1）	只需要一个Temp
			* 稳定的排序：往后遍历出现一样数值会插到后面（先=后大于）
			*/
		{
			T temp;
			for (T* i = items + 1; i < items + size; i++)
			{
				temp = *i; //已知从0到i都是从小到大排序好，需将将*i插入
				for (T* j = items; j < i; j++) //
				{
					if (temp < *j)//遍历0-i，直到找到位置使得temp<*i,意味着要插入这里
					{
						for (T* k = i - 1; k >= j; k--)//从i-1个开始到j（插入位置）向后挪一个
						{
							*(k + 1) = *k;
						}
						*j = temp;//插入
						break;
					}
				}
			}
		}

		static int BinarySearch(T& target, T* items, int size)	//二分查找
		{
			int left = 0;
			int right = size - 1;
			int mid = 0;

			while (left <= right) //寻找区域的两头没有交叉
			{
				mid = (left + right) / 2;	//找到中间值
				if (items[mid] == target) //刚刚好
				{
					return mid;
				}
				if (items[mid] < target) //target在中间之后，则移动左边界
				{
					left = mid + 1;
				}
				else //target在之前，则移动右边界
				{
					right = mid - 1;
				}
			}

			return -1; //没找到
		}

		static void Swap(T* a, T* b)
		{
			T temp;
			temp = *a;
			*a = *b;
			*b = temp;
		}

		static void ShellSort(T* items, int size)
			/*希尔排序
			* 时间复杂度O（n（log2n）^2）或O（n^3/2）:不好说了
			* 空间复杂度O（1）：就是temp（swap）
			* 不稳定排序：可能jump刚好跳过去了
			*/
		{
			int jump = size / 2;//从一半开始跳

			while (jump > 0) //最后一次跳跃是1，之后结束
			{
				for (T* i = items + jump; i < items + size; i++) //从jump开始，将第i个与i-jump比较
				{
					T* j = i;
					//为什么设了个j：如果*i < *i-jump需要将其交换
					//然后再比较i - jump和i-2jump，直到交换合适位置存放*i
					while (j - jump >= items)
					{
						//这部分就是一直向前比较，直到交换到合适位置
						//之前的序列(i - jump)已经从小大大排好，所以只要符合就可以退出了
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
				jump /= 2; //设置好jump，准备下一轮比较
			}
		}

		static void BubbleSort(T* items, int size)
			/*
			* 冒泡排序
			* 时间复杂度O(n^2)：i-从前往后每一位n（j-跟前面比较n-i次）
			* 空间复杂度O(1)
			* 稳定排序：如果两个值相等，从前往后的冒泡会卡在前面
			*/
		{
			for (T* i = items + size - 1; i > items; i--)//从前往后冒泡
			{
				bool exchanged = false; //标记在0到（i-1）之间还有没有交换
				for (T* j = items; j < i; j++) //逐个遍历
				{
					if (*j > *(j + 1)) //冒泡
					{
						Swap(j, j + 1);
						//cout << *j << *(j + 1) << endl;
						exchanged = true; //标记有交换
					}
				}
				if (!exchanged) break; //如果没有交换，说明i-1之前已经排好序了
			}
		}

		static void QuickSort(T* items, int size)
			/*
			* 快速排序
			* 时间复杂度O(n^2) 到 O(nLog2n)：原数组按从大到小顺序排列，需要递归i=(n-1)层，每一层需要双向查找(n-i)，得到O(n^2)
			*								理想情况下，直接二分，递归i=（log2n）层，每一层（所有深度相同）一共遍历n个数
			* 空间复杂度O(log2n)，理想情况下，会出现log2(n+1)层递归(出现长度为0时候)，每一个递归都需要一个交换缓存
			* 不稳定排序：如果两个值相等，并且同时出现在spliter的一侧，会被倒序
			*/
		{
			if (size > 0)	//没长度直接返回，不排序
			{
				T* splitP = Spliter(items,size);	//调用分段方法，得到分段的指针
				T* leftP = items;					//一个开头一个末尾
				T* rightP = items + size - 1;		
				QuickSort(leftP, splitP - leftP);		//排序子序列，第一个是[Start,splitP - 1]，长度为splitP-leftP
				QuickSort(splitP + 1, rightP - splitP);	//第二个是[splitP+1，leftP]，长度是rightP - splitP
			}

		}

		static T* Spliter(T* items, int size)
		{
			if (size > 0)	//长度大于0才能分割
			{
				T refP = *(items);			//基准值直接第一个
				T* leftP = items + 1;
				T* rightP = items + size - 1;		//两侧的指针,由于左侧第一个值当基准了，使用第二个

				while (leftP <= rightP)								//只要两个指针相交叉：已经全部交换完两边了，此处需要等号：否则会出现差一个没交换的情况
				{
					for (; leftP <= rightP && *leftP < refP; leftP++);		//双向查找，直到left找到比ref大的，right找到比ref小的
					for (; leftP <= rightP && *rightP > refP; rightP--);	//此处均需要等号，才能保证全部交换
					if (leftP <= rightP)		//当两者还未交叉时，时可以交换的：加上等于号:如果出现 1 0 1 子列，left到达第二个1，right也在第二个1（*rightP = refP），这种情况应该跳出
					{
						Swap(leftP, rightP);
						leftP++;
						rightP--;
					}
				}
				Swap(items, rightP);//和right交换
				/*
				结束循环有三种情况
				①for (; leftP <= rightP && *leftP < refP; leftP++);处结束
					此时，rightP指向一个小于ref的数字，leftP超过rightP，指向一下大于ref的数字
					所以应该把right交换到第一个
				②for (; leftP <= rightP && *rightP > refP; rightP--);
					此时，leftP指向一个大于ref的数字，rightP在LeftP之前，指向一个小于ref的数字
				③if (leftP < rightP){Swap}之后
					交换完right靠前，由于交换，right指向小值
				*/
				return rightP;
			}
			return nullptr;
		}

		static void SelectSort(T* items, int size)
			/*
			直接选择排序
			时间复杂度O(n^2):主循环i循环n次（自循环j循环n-i次），一共n(n-1)/2
			空间复杂度O(1):只需要一个temp交换空间
			不稳定排序：出现两个相同值，交换标记会被后一个刷新，交换后顺序改变
			*/
		{
			T* exchange = nullptr;	//标记循环中出现的最小值

			for (T* i = items; i < items + size; i++)	//第一重循环，确定选择后交换的位置
			{
				exchange = i;
				for (T* j = i; j < items + size; j++)	//第二轮循环，确定待选择队列中的最小值
				{
					if (*j < *exchange)			//发现更小的，就刷新标记
					{
						exchange = j;
					}
				}
				Swap(i, exchange);				//交换
			}
		}

		static void MergeSort(T* items, int size)
			/*
			归并排序
			时间复杂度O(nlog2n):len指数上升，故需要i = log2n次的Mergepass，j-每次mergepass循环全部字符串=n
			空间复杂度O(n):temp
			稳定排序：出现两个相同值，不同属性有两种情况1.分到一个子队列，显然不改变相对顺序。2.分到两个子序列，当他们在某一次相遇时，
			*/
		{
			int len = 1;
			T* temp = new T[size];

			do
			{
				MergePass(items, temp, size, len);	//从items归并到temp
				len *= 2;
				MergePass(temp, items, size, len);	//再归并回来
				len *= 2;							//每一次长度都加倍

			} while (len < size);

				delete[] temp;						//GC

		}

		static void MergePass(T* items, T* temp, int size, int len)	//确定len之后，进行归并
		{
			int i = 0;					//每次第一个队列的头，i+len,第二个队列的头
			while (i < size - 2 * len)
			{
				Merge(items, temp, size, i, i + len, len);	//对两个子序列归并
				i += 2  *len;
			}

			//处理剩下不够两个的序列
			if (i + len < size) 
			{
				Merge(items, temp, size, i, i + len, len);	//对于够一个序列，但不够两个的
			}
			else
			{
				for (int j = i; j < size; j++)			//一个都不够
				{
					temp[j] = items[j];
				}
			}
			//如果Merge循环加一个判断 i < size ，我觉得可以不用判断直接循环了
			//while (i < size )
			//{
			//	Merge(items, temp, size, i, i + len, len);	//对两个子序列归并
			//	i += 2 * len;
			//}
		}

		static void Merge(T* items, T* temp, int size, int start1, int start2, int len) //一个简单的归并排序
		{
			int i = start1, j = start2 , k = start1;
			while (i < start1 + len && j < start2 + len && i < size && j < size)	//从i，j两个中挑一个小的填充
			{
				if (items[i] <= items[j])	//如果等于的话，应该先写入items[i]吧?
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
			while (i < start1 + len && i < size)	//没填充完给他填充完
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