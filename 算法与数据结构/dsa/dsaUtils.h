#pragma once
#include<vector>
#include <iostream>

namespace dsaUtils
{
	using namespace std;
	//template<typename T>
	class ArrTools
	{
	public:
		//full fill arr with rand num
		static void rand_arr(int*, int, int, int);
		//full fill vector with rand num
		static void rand_vec(vector<int>& arr, int size = -1, int mi = -99, int max = 99);
		//show an arr
		static void show_arr(int*, int);
		//show a vector
		static void show_vec(vector<int>& arr);
	};
	template <typename T>
	class ArrTool2
	{
	public:
		//show an arr
		static void show_arr(T* p, int size)
		{
			for (T* i = p; i < p + size; i++)
			{
				cout << *i ;
			}
			cout << endl;
		}

		//show a vector
		static void show_vec(vector<T>& arr)
		{
			for (auto i : arr)
			{
				cout << i << " ";
			}
			cout << endl;
		}
	};
}

