

#include <iostream>
#include <vector>
#include "../dsa/SrotAlgorithms.hpp"
#include "../ex8p1/SearchInArray.cpp"
#include <algorithm>
#define T int               //类型
#define Size 800000        //大小

using namespace std;
using namespace dsaUtils;

void TimeCount_Switch()     //计时器
{
    static bool IsCounting = false; //标记是否正在及时
    static long StartTime;

    if (IsCounting)
    {
        //若正在计时，则结束计时，并输出所用时间
        cout << endl << "用时(ms):" << GetTickCount64() - StartTime << endl;
    }
    else
    {
        //未计时则开始计时，记录开始时间
        StartTime = GetTickCount64();
    }

    //反转状态
    IsCounting = !IsCounting;
}


int main()
{
    T* Arr = new T[Size];       //查找空间
    vector<T> ToFindList = { 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175, 185, 195 };
    MySort<T>::RandArr(Arr, Size, 0, 9999);
    T i;

    for (int i = 0; i < ToFindList.size(); i++)     //输出需要查找的内容
    {
        cout << ToFindList[i] << '\t';
    }
    cout << endl;


    TimeCount_Switch();
    for (int i = 0; i < ToFindList.size(); i++)                     //顺序查找
    {
        int pos = SearchInArray<T>::SequentialSearch(Arr, Size, ToFindList[i]);
        cout << pos << '\t';
    }
    TimeCount_Switch();     //输出计时


    MySort<T>::QuickSort(Arr, Size);    //排序


    TimeCount_Switch();
    for (int i = 0; i < ToFindList.size(); i++) //二分查找
    {
        int pos = SearchInArray<T>::BinarySearch(Arr, Size, ToFindList[i]);
        cout << pos << '\t';
    }
    TimeCount_Switch();

}

