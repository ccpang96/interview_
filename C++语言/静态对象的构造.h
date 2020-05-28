#pragma once
#include<iostream>
using namespace std;

class Student {
private:
	int age;
public:
	Student() {}
	Student(int val) : age(val) {
		cout << "默认构造函数" << endl;
	}

	Student(const Student& s2) {
		cout << "调用拷贝构造函数" << endl;
		age = s2.age;
	}

	Student& operator=(const Student & s2) {
		cout << "调用移动赋值运算符" << endl;
		age = s2.age;
		return *this;
	}
	~Student() {
		cout << "全局对象的析构" << endl;
	}
};

//1.测试全局对象：
//编译器在进入main函数之后安插一个_main()函数，_main()中含有全局变量的静态初始化操作
//在程序结束前，安插一个exit()函数,exit()中含有全局变量的静态释放操作。
Student s1(10); //全局Student对象


				//2.测试局部静态对象的构造与析构
void fun() {

	//导入一个临时对象，当第一次调用fun时，临时对象被评估为false，所以调用其
	//构造函数，然后将临时对象设置为true，所以保证了局部静态对象只会被构造一次。
	static Student s4(10);
	//析构时也要判断临时对象是否为true，为true才析构。
}

//3.测试对象数组


int main() {
	//1.测试全局对象的构造与析构
	//Student s3;
	//Student s2 = s1;
	//s3 = s1; //拷贝赋值预算符
	// _main()  全局对象的构造

	//2.测试局部静态对象的构造与析构
	//int i = 10;
	//while (i > 0) {
	//	fun(); //当fun第一次被调用时，会执行构造函数以后都不会再执行了
	//	i--;
	//}

	//3.对象数组
	Student group[10];



	//在这里进行局部静态变量的析构 
	// _exit()   全局对象的析构
	return 0;
}

void fun() {

	static Student s;
}