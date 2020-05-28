/************************************************************************/
/*@File Name         : singleton.cpp
/*@Created Date      : 2020/5/28 15:04
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : ʵ�ֵ���ģʽ,���������������Լ��ֲ���̬��������ʵ�ַ���
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


// ����һ������ʽ�̰߳�ȫ-˫�ؼ�� [5/28/2020 Administrator]
class Singleton {
private:
	//����洢
	static Singleton *instance;
	//˽�еĹ��캯��
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





//����������̬�ڲ���ģʽ


//int main() {
//	//Singleton *s = new Singleton();   ���캯����˽�еģ�����������
//	Singleton *s = Singleton::getInstance(); 
//	Singleton *r = Singleton::getInstance();
//
//	cout << s << endl;
//	cout << r << endl;
//
//	system("pause");
//	return 0;
//}
