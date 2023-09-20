

#include "pch.h"
#include <string>
#include<iostream>
#include<sstream>
#include <ostream>
#include <vector>
#include <functional>

#include<fstream>



using namespace std;

class Robot
{

public:
	string ID;
	string Name;
	string IQ;
	

public:
	Robot()				//两个构建函数，分别无参数，有参数
	{
		ID = "None";
		Name = "None";
		IQ = "None";
	}

	Robot(string a, string b, string c)
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
			f = [](Robot& a, Robot& b) {return atol(a.IQ.c_str()) > atol(b.IQ.c_str()); };
			break;
		default:
			f = [](Robot& a, Robot& b) {return a> b; };	//默认的重载大小于
			break;

		}
		return f;
	}

	static vector<Robot> TempRobotList;
	static vector<Robot>  Readxml(string filepath) //懒得用xml库了，直接手写个建议list遍历器完事
	{
		vector<Robot> result;				//读取txt
		string xml = UTF8ToANSI(readtxt(filepath));

		while (true)
		{
			string sID = StringBetween(xml, "<ID>", "</ID>",false,true);
			string sName = StringBetween(xml, "<Name>", "</Name>", false,true);
			string sIQ = StringBetween(xml, "<IQ>", "</IQ>", false, true);
			if (sID == "") break;
			result.push_back(Robot(sID.c_str(), sName, sIQ.c_str()));
		}

		return result;
	}

	static string readtxt(string filepath)	//读取文本
	{
		ifstream fin;			//filestream


		fin.open(filepath, ios::in);
		if (!fin.is_open())
		{
			cout << "无法找到这个文件！" << endl;
			return "";
		}

		char buff;
		string temp = "";
		while ((buff = fin.get()) != EOF) //读到末尾，一个char一个char读取，都放到buff
		{
			cout << buff;
			temp += buff;
		}
		fin.close();

		return temp;
	}

	static string StringBetween(string& Text, string StartWith, string EndWith ,bool BothEnds , bool distory)    //获取Text中StartWith和EndWith之间内容，BothEnds表示从两端开始寻找
	{
		if (Text == "" || Text.find(StartWith) == -1 || Text.find(EndWith) == -1)
		{
			return "";
		}
		else
		{
			int Flag1 = Text.find(StartWith);				//开始位置
			int Flag2 = Text.find(EndWith);					//结束位置（从左向右）
			int Flag3 = Text.find_last_of (EndWith);		//结束位置(从右向左)
			string Result;
			if (BothEnds)	//剪切
			{
				Result = Text.substr(Flag1 + StartWith.length(), Flag3 - Flag1 - EndWith.length() + 1);
				Result = Text.substr(Flag1 + StartWith.length(), Flag2 - Flag1 - EndWith.length() + 1);
				if (distory)	//用完即删除
				{
					Text.erase(Flag1, Flag3);
				}
			}
			else
			{
				Result = Text.substr(Flag1 + StartWith.length(), Flag2 - Flag1 - EndWith.length() + 1);
				if (distory)
				{
					Text.erase(Flag1, Flag2 - Flag1 + EndWith.length());
				}
			}
			return Result;
		}
	}

	static string UTF8ToANSI(string s) //文本格式编码，舶来品
	{
		BSTR    bstrWide;
		char* pszAnsi;
		int     nLength;
		const char* pszCode = s.c_str();

		nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
		bstrWide = SysAllocStringLen(NULL, nLength);

		MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

		nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
		pszAnsi = new char[nLength];

		WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
		SysFreeString(bstrWide);

		string r(pszAnsi);
		delete[] pszAnsi;
		return r;
	}
};