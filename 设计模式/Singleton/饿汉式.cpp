/************************************************************************/
/*@File Name         : ����ʽ.cpp
/*@Created Date      : 2020/5/29 6:59
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : ʹ�ö���ʽʵ�ֵ���ģʽ
/************************************************************************/

/************************************************************************/
/*@File Name         : ����ʽ.cpp
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
	//��ȡʵ��
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
	Singleton() { cout << "���캯��" << endl; }
	~Singleton() { cout << "��������" << endl; }
	Singleton(const Singleton &signal) = delete;
	const Singleton &operator=(const Singleton &signal) = delete;

private:
	static Singleton *instance;
};

//����һ���оͳ�ʼ������ʵ��
Singleton * Singleton::instance = new Singleton();



int main() {
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	if (p1 == p2)
		cout << "��ͬһ������" << endl;
	else 
		cout << "����ͬһ������" << endl;

	Singleton::deleteInstance();
	system("pause");
	return 0;
}