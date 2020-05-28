#pragma once
//四种标准转换类型
#include<iostream>
#include<vector>
#include<typeinfo>
using namespace std;
//1.static_cast
class A {
};
class B : public A {

};

//3.const_cast
class Student {
private:
	int age;
public:
	Student(int val) : age(val) {}
	void fun() const {
		(const_cast<Student*>(this))->age = 5;
	}
	int getAge() {
		return age;
	}
};

int addTen(int *p) {
	return (*p + 10);
}
//4.
struct mystruct {
	int x;
	int y;
	char c;
	bool b;
};


int main() {

	//1.static_cast<int>(a)
	//1.1 基本数据类型的转换


	//dynamic_cast


	//3.const_cast:
	//3.1去掉this指针的常量属性
	//Student s1(12);
	//cout << s1.getAge() << endl;
	//s1.fun(); //改变s1的年龄
	//cout << s1.getAge() << endl;
	//	//3.2 const_cast通过去除const属性，让一个接收非const参数的函数，也能接受const 参数
	//const int val = 10;
	//const int *p1 = &val;
	//int *p2 = const_cast<int*>(p1);
	//cout << addTen(p2) << endl;

	//	//3.3 const_cast可以同时去掉volatile属性
	//int  a = 10;
	//const volatile int * p3 = &a;
	//cout << typeid(p3).name() << endl;
	//int *p4 = const_cast<int*>(p3);
	//cout << typeid(p4).name() << endl;


	//int a1 = 40;
	//const int *b1 = &a1;
	//char *c1 = (char*)(b1); //让b1变成一个指向char*的指针 指针是可以强制转换为任何类型的
	//*c1 = 'A';


	//4.reinterpret_cast 非常危险 对该对象从位模式上重新解释
	//指针类型会教导编译器如何解释某个特定地址中的内存内容及其大小

	//int *p = new int(65);
	//char *cp = reinterpret_cast<char*>(p);
	//cout << *p << endl;  //65
	//cout << *cp << endl; //A
	//cout << p << endl; //0x1609c20
	//cout << cp << endl; //A 竟然将一个指针转换成了char

	//mystruct s;
	//s.x = 5;
	//s.y = 10;
	//s.c = 'a';
	//s.b = true;

	//int * pp = reinterpret_cast<int*>(&s);
	//cout << sizeof(s) << endl;

	//cout << *pp << endl; //打印pp到底指向的是什么值
	//pp++;
	//char *ch1 = reinterpret_cast<char*>(pp);
	//cout << *ch1 << endl;

	system("pause");
	return 0;
}