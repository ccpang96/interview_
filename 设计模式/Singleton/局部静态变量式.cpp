/************************************************************************/
/*@File Name         : 静态内部类式.cpp
/*@Created Date      : 2020/5/29 6:47
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 使用局部静态对象只会被初始化一次，而且是线程安全的
/************************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;


class Singleton {
private:
	Singleton() { cout << "构造函数" << endl; }		//禁止外部构造
	~Singleton() { cout << "析构函数" << endl; }		//禁止外部析构
	Singleton(const Singleton&)  = delete;				//禁用拷贝构造函数
	Singleton operator=(const Singleton&) = delete;		//禁用拷贝赋值运算符

public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};


//int main() {
//
//	Singleton &r = Singleton::getInstance();
//	Singleton &s = Singleton::getInstance();
//
//	cout << &s << endl;
//	cout << &r << endl;
//
//	system("pause");
//	return 0;
//}