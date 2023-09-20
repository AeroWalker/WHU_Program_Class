#include <complex>
#include <iostream>
using namespace std;

int main()
{
	//构建、输出一个复数
	complex<double> c(12,-1);
	cout << c << endl;
	cout << "实部为 " << c.real() << "虚部为 " << c.imag() << endl;

	//基本运算
	complex<double> a(1.5, -1), b(-8, 9);
	cout << a << "+" << b << "=" << a + b << endl;
	cout << a << "-" << b << "=" << a - b << endl;
	cout << a << "*" << b << "=" << a * b << endl;
	cout << a << "/" << b << "=" << a / b << endl;

	//输入方式
	complex<double> d;
	cout << "请输入一个复数:(a,b)" << endl;
	cin >> d;

	//对应函数功能
	cout << d << "的绝对值=" << abs(d) << endl;
	cout << d << "的共轭复数="  << conj(d) << endl;
	cout << d << "的x轴夹角=" << arg(d) << endl;
	cout << d << "的黎曼投影=" << proj(d) << endl;
	cout << d << "的极坐标=" << polar(d) << endl;
	cout << d << "的exp=" << exp(d) << endl;
	cout << d << "的ln=" << log(d) << endl;

}