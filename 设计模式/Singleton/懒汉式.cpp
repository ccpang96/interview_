/************************************************************************/
/*@File Name         : singleton.cpp
/*@Created Date      : 2020/5/28 15:04
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 实现单例模式,有懒汉、饿汉、以及局部静态变量三种实现方法
/************************************************************************/

/* Includes *************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;


// 方法一：懒汉式线程安全-双重检查 [5/28/2020 Administrator]
class Singleton {
private:
	//这里存储
	static Singleton *instance;
	//私有的构造函数
	Singleton() {};
public:
	static Singleton* getInstance();
};


Singleton* Singleton::instance = nullptr;
Singleton* Singleton::getInstance() {
	if (instance == nullptr)
		instance = new Singleton();
	return instance;
}





//方法二、静态内部类模式


//int main() {
//	//Singleton *s = new Singleton();   构造函数是私有的，根本不成立
//	Singleton *s = Singleton::getInstance(); 
//	Singleton *r = Singleton::getInstance();
//
//	cout << s << endl;
//	cout << r << endl;
//
//	system("pause");
//	return 0;
//}
