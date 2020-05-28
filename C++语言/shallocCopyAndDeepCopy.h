#pragma once
#include <cassert>
#include <iostream>
#include<string>
using namespace std;
class Fraction
{
private:
	int m_numerator;
	int m_denominator;

public:
	// Default constructor
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator },
		m_denominator{ denominator }
	{
		cout << "使用自定义的构造函数" << endl;
		assert(denominator != 0);
	}
	//自定义的拷贝赋值运算符
	Fraction& operator= (const Fraction &fraction);

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
};

std::ostream& operator<<(std::ostream& out, const Fraction &f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}


//自定义的拷贝赋值运算符
// A better implementation of operator=
Fraction& Fraction::operator= (const Fraction &fraction)
{
	cout << "使用自己的拷贝赋值运算符" << endl;
	// self-assignment guard
	if (this == &fraction)
		return *this;

	// do the copy
	m_numerator = fraction.m_numerator;
	m_denominator = fraction.m_denominator;

	// return the existing object so we can chain this operator
	return *this;
}
//例子2：测试基础类型的按值传递
int AddNumbers(int loc_X, int loc_Y)
{
	return (loc_X + loc_Y);
}

//例子3.测试含有动态分配内存的浅拷贝和深拷贝
class ShalloC {
private:
	int *x;
public:
	//构造函数
	ShalloC(int m) {
		cout << "使用自定义的构造函数" << endl;
		x = new int;
		*x = m;

	}
	int GetX() const {
		return *x;
	}
	void SetX(int m) {
		*x = m;
	}
	void PrintX() {
		cout << "X =" << *x << endl;
	}
	~ShalloC() {
		delete x;
	}

	//自定义拷贝构造函数
	ShalloC(const ShalloC&c) {
		cout << "使用自定义的拷贝构造函数" << endl;
		x = c.x;
	}

	//自定义拷贝赋值运算符

};


int main() {

	//1.测试拷贝构造函数：此时类内没有动态分配的函数，无需定义自己的拷贝赋值运算符
	Fraction fa;
	cout << "初始化第二个类变量" << endl;
	fa = Fraction(1, 2);
	cout << fa << endl;

	//2.测试基本类型的拷贝
	int a = 3, b = 9;
	int result = AddNumbers(a, b);
	cout << result << endl;

	//3.测试深拷贝和浅拷贝
	ShalloC ob1(10); //构造函数
	ShalloC ob2(ob1); //拷贝构造函数
	ShalloC ob3 = ob1;//拷贝构造函数

	system("pause");
	return 0;
}

