#pragma once
#include<vector>
#include <string>
#include <ostream>
#include <sstream> 
/*
有一个小问题：
1.在创建静态库文件时，template<type_name T>的作用范围只有紧邻的class。
这意味在头文件（.h）中声明的 type_name T 无法在 .cpp 中继续使用。
2.经过百度后，貌似直接在.hpp中编写template是没有问题的。
但是这样的话，以后调用静态库直接 include"xxx.hpp" 即可，那还有必要再引入lib文件么？

*/

namespace dsaUtils
{
	using namespace std;

	class CStu
	{
	public:
		int _id = 0;						//学生_id，姓名，年龄，三科成绩 
		string _name = "None";
		float _age = 0;
		double _score;

		CStu()
		{
			_score = -1;
		}

		//两个构造函数
		CStu(int _id, string _name, float _age, double _score)
		{
			this->_id = _id;
			this->_name = _name;
			this->_age = _age;
			this->_score = _score;
		}

		CStu(int _id, char* _name, float _age, double _score)
		{
			this->_id = _id;
			this->_name = string(_name);
			this->_age = _age;
			this->_score = _score;
		}

		//比较操作
		bool operator<(CStu& s)
		{
			return this->_id < s._id;
		}
		bool operator>(CStu& s)
		{
			return this->_id > s._id;
		}

		//输出为文本
		friend ostream& operator<<(ostream& os, const CStu& s) {
			os << s._id << ' ' << s._name << ' ' << s._age << ' ' << s._score;
			return os;
		}

		string str(bool DisplayTypeName = false)
		{
			stringstream oss("");
			if (DisplayTypeName)
			{
				oss << "CStu Type:";
			}
			oss << *this;
			return oss.str();
		}

	};
}

