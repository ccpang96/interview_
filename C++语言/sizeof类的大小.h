#pragma once
#include<iostream>
using namespace std;


//���Կ����С
class Fruit {
public:

};


//�������麯������Ĵ�С
class Student {
public:
	int age;
	virtual void getValue() {

	}
};
class B : public Student {

	int age;
};
//D��Student��B��������
class D : public Student, public B {

};

class E : public virtual Student {

};
int main() {

	Student s1;
	B b1;
	D d1;
	E e1;
	cout << "�ջ���Student��С��" << sizeof(s1) << "\n" << "������B�Ĵ�С��" << sizeof(b1) << endl;
	cout << "�ն��ؼ̳���D�Ĵ�С" << sizeof(d1) << endl;
	cout << "�������E�Ĵ�С" << sizeof(e1) << endl;
	system("pause");
	return 0;
}