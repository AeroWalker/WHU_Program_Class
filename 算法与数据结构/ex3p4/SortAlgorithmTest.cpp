#include <stdio.h>
#include "../dsa/SrotAlgorithms.hpp"

using namespace std;
using namespace dsaUtils;

int main()
{
	srand(time(0));
	int Arr[20];
	cout << endl << "插入排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::InsertSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);

	cout << endl << "希尔排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::ShellSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);

	cout << endl << "冒泡排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::BubbleSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);


	cout << endl << "快速排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::QuickSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);
	

	cout << endl << "选择排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::SelectSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);
	
	cout << endl << "归并排序" << endl;
	MySort<int>::RandArr(Arr, 20);
	MySort<int>::MergeSort(Arr, 20);
	MySort<int>::ShowArr(Arr, 20);
	return 0;
}