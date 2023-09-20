#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../dsa/SrotAlgorithms.hpp"
#include "../ex8p1/SearchInArray.cpp"
using namespace dsaUtils;
using namespace std;

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



#define Size 20000
#define T string
int main()
{
    string* Arr = new string[Size];
    map<string, int> dic;
    vector<string> ToFindList;



    for (int i = 0; i < Size; i++)              //初始化寻找空间和寻找目标
    {
        Arr[i] = to_string(i);
        pair<string, int> p(to_string(i),i);    //新增KV
        dic.insert(p);
    }
    for (int i = 500; i <= 19500; i += 1000)
    {
        ToFindList.push_back(to_string(i));
    }




    TimeCount_Switch();
    for (int i = 500; i <= 19500; i += 1000)        //Map方法寻找
    {
        cout << dic[to_string(i)] << '\t';
        ToFindList.push_back(to_string(i));
    }
    TimeCount_Switch();     //输出计时









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
