#include "pch.h"
#include "framework.h"
#include "dsaUtils.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

namespace dsaUtils
{
	using namespace std;

	// full fill an arr[0-size] with random number in [min-max]
	void ArrTools::rand_arr(int* arr, int size, int min = -99, int max = 99)
	{
		srand(time(0));
		//random
		for (int* i = arr; i < arr + size; i++)
		{
			*i = rand() % (max - min + 1) + min;
		}
	}

	// full fill a vector[0-size] with random number in [min-max]
	void ArrTools::rand_vec(vector<int>& arr, int size, int min, int max)
	{
		srand(time(NULL));
		if (size == -1) size = arr.size();
		//random
		vector<int>::iterator i = arr.begin();
		for (vector<int>::iterator i = arr.begin(); i < arr.begin() + size; i++)
		{
			*i = rand() % (max - min + 1) + min;
		}
	}

	//list all items in arr
	void ArrTools::show_arr(int * p, int size)
	{
		for (int *i = p; i < p + size; i++)
		{
			cout << *i << " ";
		}
		cout << endl;
	}
	

	//list all items in vector
	void ArrTools::show_vec(vector<int>& arr)
	{
		for (auto i : arr)
		{
			cout << i << " ";
		}
		cout << endl;
	}
}