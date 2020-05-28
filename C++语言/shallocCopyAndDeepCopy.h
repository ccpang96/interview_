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
		cout << "ʹ���Զ���Ĺ��캯��" << endl;
		assert(denominator != 0);
	}
	//�Զ���Ŀ�����ֵ�����
	Fraction& operator= (const Fraction &fraction);

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
};

std::ostream& operator<<(std::ostream& out, const Fraction &f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}


//�Զ���Ŀ�����ֵ�����
// A better implementation of operator=
Fraction& Fraction::operator= (const Fraction &fraction)
{
	cout << "ʹ���Լ��Ŀ�����ֵ�����" << endl;
	// self-assignment guard
	if (this == &fraction)
		return *this;

	// do the copy
	m_numerator = fraction.m_numerator;
	m_denominator = fraction.m_denominator;

	// return the existing object so we can chain this operator
	return *this;
}
//����2�����Ի������͵İ�ֵ����
int AddNumbers(int loc_X, int loc_Y)
{
	return (loc_X + loc_Y);
}

//����3.���Ժ��ж�̬�����ڴ��ǳ���������
class ShalloC {
private:
	int *x;
public:
	//���캯��
	ShalloC(int m) {
		cout << "ʹ���Զ���Ĺ��캯��" << endl;
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

	//�Զ��忽�����캯��
	ShalloC(const ShalloC&c) {
		cout << "ʹ���Զ���Ŀ������캯��" << endl;
		x = c.x;
	}

	//�Զ��忽����ֵ�����

};


int main() {

	//1.���Կ������캯������ʱ����û�ж�̬����ĺ��������趨���Լ��Ŀ�����ֵ�����
	Fraction fa;
	cout << "��ʼ���ڶ��������" << endl;
	fa = Fraction(1, 2);
	cout << fa << endl;

	//2.���Ի������͵Ŀ���
	int a = 3, b = 9;
	int result = AddNumbers(a, b);
	cout << result << endl;

	//3.���������ǳ����
	ShalloC ob1(10); //���캯��
	ShalloC ob2(ob1); //�������캯��
	ShalloC ob3 = ob1;//�������캯��

	system("pause");
	return 0;
}

