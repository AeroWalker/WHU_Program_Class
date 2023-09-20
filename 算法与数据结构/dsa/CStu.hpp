#pragma once
#include<vector>
#include <string>
#include <ostream>
#include <sstream> 
/*
��һ��С���⣺
1.�ڴ�����̬���ļ�ʱ��template<type_name T>�����÷�Χֻ�н��ڵ�class��
����ζ��ͷ�ļ���.h���������� type_name T �޷��� .cpp �м���ʹ�á�
2.�����ٶȺ�ò��ֱ����.hpp�б�дtemplate��û������ġ�
���������Ļ����Ժ���þ�̬��ֱ�� include"xxx.hpp" ���ɣ��ǻ��б�Ҫ������lib�ļ�ô��

*/

namespace dsaUtils
{
	using namespace std;

	class CStu
	{
	public:
		int _id = 0;						//ѧ��_id�����������䣬���Ƴɼ� 
		string _name = "None";
		float _age = 0;
		double _score;

		CStu()
		{
			_score = -1;
		}

		//�������캯��
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

		//�Ƚϲ���
		bool operator<(CStu& s)
		{
			return this->_id < s._id;
		}
		bool operator>(CStu& s)
		{
			return this->_id > s._id;
		}

		//���Ϊ�ı�
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

