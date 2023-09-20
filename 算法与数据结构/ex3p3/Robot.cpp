#include <string>
#include<iostream>
#include<sstream>
#include <ostream>
#include <functional>


using namespace std;

class Robot
{

private:
	int ID;
	string Name;
	int IQ;

public:
	Robot()				//两个构建函数，分别无参数，有参数
	{
		ID = 0;
		Name = "None";
		IQ = 0;
	}

	Robot(long a, string b, long c)
	{
		ID = a;
		Name = b;
		IQ = c;
	}

	Robot(const Robot& r)
	{
		this->ID = r.ID;
		this->Name = r.Name;
		this->IQ = r.IQ;
	}

	Robot& operator=(const Robot& r)
	{
		this->ID = r.ID;
		this->Name = r.Name;
		this->IQ = r.IQ;
		return *this;
	}

	~Robot()
	{

	}

	bool operator<(Robot r)				//两个重载比较符号，默认用ID比较
	{
		return (this->ID < r.ID);
	}

	bool operator>(Robot r)
	{
		return (this->ID > r.ID);
	}

	friend ostream& operator<<(ostream& os, const Robot& r)  //重载cout
	{
		os << r.ID << ' ' << r.Name << ' ' << r.IQ << endl;
		return os;
	}

	string str(bool DisplayTypeName = false)	//重载str
	{
		stringstream oss("");
		if (DisplayTypeName)
		{
			oss << "Robot Type:";
		}
		oss << *this;
		return oss.str();
	}

	static function<bool(Robot& a, Robot& b)> CompareItem(int n)	//返回一个比较参数：0 ID，1 名称， 2 IQ，其他默认用大小
	{
		function<bool(Robot& a, Robot& b)> f;
		switch (n)
		{
		case 0:
			f = [](Robot& a, Robot& b) {return a.ID > b.ID; };
			break;
		case 1:
			f = [](Robot& a, Robot& b) {return a.Name > b.Name; };
			break;
		case 2:
			f = [](Robot& a, Robot& b) {return a.IQ > b.IQ; };
			break;
		default:
			f = [](Robot& a, Robot& b) {return a> b; };	//默认的重载大小于
			break;

		}
		return f;
	}

};