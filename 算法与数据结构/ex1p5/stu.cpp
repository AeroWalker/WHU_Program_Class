#include <string>
# include<iostream>

using namespace std;

class student
{
public:
	int id = 0;						//学生id，姓名，年龄，三科成绩 
	string name = "None";
	float age = 0;
	double score;

	//构造函数
	student(int id, string name, float age, double score)
	{
		this->id = id;
		this->name = name;
		this->age = age;
		this->score = score;
	}

	//输出cout，别忘了friend！！！！不然重载不了
	friend ostream& operator<<(ostream& os, const student& s) {
		os << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.score;
		return os;
	}

};