#pragma once
#include<iostream>
#include<vector>
using namespace std;

//volatile:���߱�������Ҫ�Ż��������п������ⲿ���ı�
//ʣ����÷���const���ƣ�ָ��volatile��ָ�룬
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

	volatile int a = 10; //����volatile
	volatile int * p1 = &a;
	int b = 20;
	volatile int *p2 = &b; //���߱�������Ҫ�Ż��������п������ⲿ���ı�
	int * volatile p4 = &b; //p4�����ٱ��ı� p4��һ��volatileָ��
	volatile int * volatile p5; //p5��һ��ָ��volatile��volatileָ��

	cout << a << endl;


	volatile Student s1;
	s1.setStudentAge(10);
	cout << s1.getStudentAge() << endl;


	system("pause");
	return 0;
}
