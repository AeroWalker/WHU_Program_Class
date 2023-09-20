#include "../ex8p3/LinearSearchList.cpp"
#include <iostream>
#include "../dsa/SrotAlgorithms.hpp"
#include <vector>

#define T int
#define Size 1000
int main()
{
    T* Arr = new T[Size];
    dsaUtils::MySort<T>::RandArr(Arr, Size, 0, 200);

    LinearSearchList<T> LST(Arr, Size);
    LST.push_back(66);
    LST.show();
    cout << endl;
    vector<T> ToFindList = { 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175, 185, 195 };


    for (int i = 0; i < ToFindList.size(); i++)                     //顺序查找
    {
        int pos = LST.indexOf(ToFindList[i]);
        cout << pos << '\t';
    }
    cout << endl;
    for (int i = 0; i < ToFindList.size(); i++)                     //二分
    {
        int pos = LST.BinarySearch(ToFindList[i]);
        cout << pos << '\t';
    }
}
