/************************************************************************/
/*@File Name         : 饿汉式.cpp
/*@Created Date      : 2020/5/29 6:59
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 使用饿汉式实现单例模式
/************************************************************************/

/************************************************************************/
/*@File Name         : 饿汉式.cpp
/*@Created Date      : 2020/5/29 7:14
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       :
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
public:
	//获取实例
	static Singleton* getInstance() {
		return instance;
	}

	static void deleteInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
private:
	Singleton() { cout << "构造函数" << endl; }
	~Singleton() { cout << "析构函数" << endl; }
	Singleton(const Singleton &signal) = delete;
	const Singleton &operator=(const Singleton &signal) = delete;

private:
	static Singleton *instance;
};

//程序一运行就初始化创建实例
Singleton * Singleton::instance = new Singleton();



int main() {
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	if (p1 == p2)
		cout << "是同一个对象" << endl;
	else 
		cout << "不是同一个对象" << endl;

	Singleton::deleteInstance();
	system("pause");
	return 0;
}