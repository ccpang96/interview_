#pragma once
//���ֱ�׼ת������
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
	//1.1 �����������͵�ת��


	//dynamic_cast


	//3.const_cast:
	//3.1ȥ��thisָ��ĳ�������
	//Student s1(12);
	//cout << s1.getAge() << endl;
	//s1.fun(); //�ı�s1������
	//cout << s1.getAge() << endl;
	//	//3.2 const_castͨ��ȥ��const���ԣ���һ�����շ�const�����ĺ�����Ҳ�ܽ���const ����
	//const int val = 10;
	//const int *p1 = &val;
	//int *p2 = const_cast<int*>(p1);
	//cout << addTen(p2) << endl;

	//	//3.3 const_cast����ͬʱȥ��volatile����
	//int  a = 10;
	//const volatile int * p3 = &a;
	//cout << typeid(p3).name() << endl;
	//int *p4 = const_cast<int*>(p3);
	//cout << typeid(p4).name() << endl;


	//int a1 = 40;
	//const int *b1 = &a1;
	//char *c1 = (char*)(b1); //��b1���һ��ָ��char*��ָ�� ָ���ǿ���ǿ��ת��Ϊ�κ����͵�
	//*c1 = 'A';


	//4.reinterpret_cast �ǳ�Σ�� �Ըö����λģʽ�����½���
	//ָ�����ͻ�̵���������ν���ĳ���ض���ַ�е��ڴ����ݼ����С

	//int *p = new int(65);
	//char *cp = reinterpret_cast<char*>(p);
	//cout << *p << endl;  //65
	//cout << *cp << endl; //A
	//cout << p << endl; //0x1609c20
	//cout << cp << endl; //A ��Ȼ��һ��ָ��ת������char

	//mystruct s;
	//s.x = 5;
	//s.y = 10;
	//s.c = 'a';
	//s.b = true;

	//int * pp = reinterpret_cast<int*>(&s);
	//cout << sizeof(s) << endl;

	//cout << *pp << endl; //��ӡpp����ָ�����ʲôֵ
	//pp++;
	//char *ch1 = reinterpret_cast<char*>(pp);
	//cout << *ch1 << endl;

	system("pause");
	return 0;
}