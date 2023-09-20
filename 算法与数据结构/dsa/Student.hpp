#pragma once
#include<vector>
#include <string>
#include <ostream>
/*
��һ��С���⣺
1.�ڴ�����̬���ļ�ʱ��template<typename T>�����÷�Χֻ�н��ڵ�class��
����ζ��ͷ�ļ���.h���������� typename T �޷��� .cpp �м���ʹ�á�
2.�����ٶȺ�ò��ֱ����.hpp�б�дtemplate��û������ġ�
���������Ļ����Ժ���þ�̬��ֱ�� include"xxx.hpp" ���ɣ��ǻ��б�Ҫ������lib�ļ�ô��

*/

namespace dsaUtils
{
	using namespace std;

	class Student
	{
	public:
		int id = 0;						//ѧ��id�����������䣬���Ƴɼ� 
		string name = "None";
		float age = 0;
		double score;

		//�������캯��
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
		
		//�Ƚϲ���
		bool operator<(Student& s) 
		{ 
			return this->id < s.id; 
		}
		bool operator>(Student& s)
		{
			return this->id > s.id;
		}

		//���Ϊ�ı�
		friend ostream& operator<<(ostream& os, const Student& s) {
			os << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.score;
			return os;
		}


	};
}

