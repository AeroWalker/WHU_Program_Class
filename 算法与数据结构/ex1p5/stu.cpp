#include <string>
# include<iostream>

using namespace std;

class student
{
public:
	int id = 0;						//ѧ��id�����������䣬���Ƴɼ� 
	string name = "None";
	float age = 0;
	double score;

	//���캯��
	student(int id, string name, float age, double score)
	{
		this->id = id;
		this->name = name;
		this->age = age;
		this->score = score;
	}

	//���cout��������friend����������Ȼ���ز���
	friend ostream& operator<<(ostream& os, const student& s) {
		os << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.score;
		return os;
	}

};