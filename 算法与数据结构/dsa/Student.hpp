#pragma once
#include<vector>
#include <string>
#include <ostream>
/*
有一个小问题：
1.在创建静态库文件时，template<typename T>的作用范围只有紧邻的class。
这意味在头文件（.h）中声明的 typename T 无法在 .cpp 中继续使用。
2.经过百度后，貌似直接在.hpp中编写template是没有问题的。
但是这样的话，以后调用静态库直接 include"xxx.hpp" 即可，那还有必要再引入lib文件么？

*/

namespace dsaUtils
{
	using namespace std;

	class Student
	{
	public:
		int id = 0;						//学生id，姓名，年龄，三科成绩 
		string name = "None";
		float age = 0;
		double score;

		//两个构造函数
		Student(int id, string name, float age, double score)
		{
			this->id = id;
			this->name = name;
			this->age = age;
			this->score = score;
		}

		Student(int id, char* name, float age, double score)
		{
			this->id = id;
			this->name = string(name);
			this->age = age;
			this->score = score;
		}
		
		//比较操作
		bool operator<(Student& s) 
		{ 
			return this->id < s.id; 
		}
		bool operator>(Student& s)
		{
			return this->id > s.id;
		}

		//输出为文本
		friend ostream& operator<<(ostream& os, const Student& s) {
			os << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.score;
			return os;
		}


	};
}

