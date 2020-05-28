/************************************************************************/
/*@File Name         : ��̬�ڲ���ʽ.cpp
/*@Created Date      : 2020/5/29 6:47
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : ʹ�þֲ���̬����ֻ�ᱻ��ʼ��һ�Σ��������̰߳�ȫ��
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
	Singleton() { cout << "���캯��" << endl; }		//��ֹ�ⲿ����
	~Singleton() { cout << "��������" << endl; }		//��ֹ�ⲿ����
	Singleton(const Singleton&)  = delete;				//���ÿ������캯��
	Singleton operator=(const Singleton&) = delete;		//���ÿ�����ֵ�����

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