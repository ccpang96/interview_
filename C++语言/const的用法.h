#pragma once
#include<iostream>

using namespace std;


class Student {
public:
	Student(int x) : age(x) {}
	int getStudentAge() const {
		return age;
	}
	bool compareTwoStudentAge(Student s2) const {
		if (age > s2.age)
			return true;
		else
			return false;
	}
private:
	int age;
};

//const是用作定义常量

int main() {
	//1.指针本身是个常量
	int a = 1;
	int * const p1 = &a; //指针本身是个常量，从此以后指针就一直指向a
	cout << a << endl; //输出为1
	(*p1)++;
	cout << a << endl; //输出为2

					   //2.指针所指向的对象是一个常量: 自以为是的指针 
	const int c = 1;
	int d = 2;
	const int *p2 = &d;
	int const *p3 = &c;
	cout << *p2 << endl;
	//3.顶层const表示任意对象本身是个常量。
	const int e = 1;
	const int * const p4 = &e; //p4本身是个常量
	const int p5 = 1; //p5本身是个常量
					  //4.指针所指的对象或引用所引用的对象是个常量，叫底层const
	const int *p6; //p6是一个指向常量的指针
	int f = 1;
	const int &r = f;
	//5.指向常量的引用：也是一个可怜的引用，自以为不能通过自己改变所指对象的值，实际上对象是不是个常量都不清楚。
	const  int &  m = f;

	//6.成员函数的末尾是const
	const Student s1(12); //定义一个10岁的学生
	Student s2(10);
	cout << s1.getStudentAge() << "岁" << endl;
	cout << s2.getStudentAge() << "岁" << endl; //非常量对象也可以调用常量成员函数啊，可怜的指向常量对象的指针
											   //比较两个学生的年龄

	if (s1.compareTwoStudentAge(s2)) {
		cout << "学生s1大于学生s2" << endl;
	}
	system("pause");
	return 0;
}
