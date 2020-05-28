#pragma once
#include<iostream>
#include<vector>
using namespace std;

//volatile:告诉编译器不要优化它，它有可能在外部被改变
//剩余的用法和const类似：指向volatile的指针，
class Student {
public:
	void setStudentAge(int val) volatile {
		age = val;
	}
	int getStudentAge() volatile {
		return age;
	}
private:
	int age;

};
int main() {

	volatile int a = 10; //顶层volatile
	volatile int * p1 = &a;
	int b = 20;
	volatile int *p2 = &b; //告诉编译器不要优化它，它有可能在外部被改变
	int * volatile p4 = &b; //p4不能再被改变 p4是一个volatile指针
	volatile int * volatile p5; //p5是一个指向volatile的volatile指针

	cout << a << endl;


	volatile Student s1;
	s1.setStudentAge(10);
	cout << s1.getStudentAge() << endl;


	system("pause");
	return 0;
}
