
#include <iostream>
#include <vector>
#include "../dsa/SrotAlgorithms.hpp"
#include "../ex8p4/HashSearchList.cpp"

using namespace std;
#define T int
#define Size 30
int main()
{
    T* Arr = new T[Size];
    dsaUtils::MySort<T>::RandArr(Arr, Size, 0, 200);        //初始化表
    HashSearchList<T> HSL;

    HSL.insert_Arr(Arr, Size);

    cout << "100存在位置为：" << HSL.Find(100) << endl;
    HSL.show();

}

