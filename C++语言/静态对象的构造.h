#pragma once
#include<iostream>
using namespace std;

class Student {
private:
	int age;
public:
	Student() {}
	Student(int val) : age(val) {
		cout << "Ĭ�Ϲ��캯��" << endl;
	}

	Student(const Student& s2) {
		cout << "���ÿ������캯��" << endl;
		age = s2.age;
	}

	Student& operator=(const Student & s2) {
		cout << "�����ƶ���ֵ�����" << endl;
		age = s2.age;
		return *this;
	}
	~Student() {
		cout << "ȫ�ֶ��������" << endl;
	}
};

//1.����ȫ�ֶ���
//�������ڽ���main����֮�󰲲�һ��_main()������_main()�к���ȫ�ֱ����ľ�̬��ʼ������
//�ڳ������ǰ������һ��exit()����,exit()�к���ȫ�ֱ����ľ�̬�ͷŲ�����
Student s1(10); //ȫ��Student����


				//2.���Ծֲ���̬����Ĺ���������
void fun() {

	//����һ����ʱ���󣬵���һ�ε���funʱ����ʱ��������Ϊfalse�����Ե�����
	//���캯����Ȼ����ʱ��������Ϊtrue�����Ա�֤�˾ֲ���̬����ֻ�ᱻ����һ�Ρ�
	static Student s4(10);
	//����ʱҲҪ�ж���ʱ�����Ƿ�Ϊtrue��Ϊtrue��������
}

//3.���Զ�������


int main() {
	//1.����ȫ�ֶ���Ĺ���������
	//Student s3;
	//Student s2 = s1;
	//s3 = s1; //������ֵԤ���
	// _main()  ȫ�ֶ���Ĺ���

	//2.���Ծֲ���̬����Ĺ���������
	//int i = 10;
	//while (i > 0) {
	//	fun(); //��fun��һ�α�����ʱ����ִ�й��캯���Ժ󶼲�����ִ����
	//	i--;
	//}

	//3.��������
	Student group[10];



	//��������оֲ���̬���������� 
	// _exit()   ȫ�ֶ��������
	return 0;
}

void fun() {

	static Student s;
}