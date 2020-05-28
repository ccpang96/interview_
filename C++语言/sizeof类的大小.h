#pragma once
#include<iostream>
using namespace std;


//测试空类大小
class Fruit {
public:

};


//测试有虚函数的类的大小
class Student {
public:
	int age;
	virtual void getValue() {

	}
};
class B : public Student {

	int age;
};
//D由Student和B派生而来
class D : public Student, public B {

};

class E : public virtual Student {

};
int main() {

	Student s1;
	B b1;
	D d1;
	E e1;
	cout << "空基类Student大小：" << sizeof(s1) << "\n" << "空子类B的大小：" << sizeof(b1) << endl;
	cout << "空多重继承类D的大小" << sizeof(d1) << endl;
	cout << "空虚基类E的大小" << sizeof(e1) << endl;
	system("pause");
	return 0;
}