#pragma once
#include<iostream>

using namespace std;


class Student {
public:
	Student(int x) : age(x) {}
	int getStudentAge() const {
		return age;
	}
	bool compareTwoStudentAge(Student s2) const {
		if (age > s2.age)
			return true;
		else
			return false;
	}
private:
	int age;
};

//const���������峣��

int main() {
	//1.ָ�뱾���Ǹ�����
	int a = 1;
	int * const p1 = &a; //ָ�뱾���Ǹ��������Ӵ��Ժ�ָ���һֱָ��a
	cout << a << endl; //���Ϊ1
	(*p1)++;
	cout << a << endl; //���Ϊ2

					   //2.ָ����ָ��Ķ�����һ������: ����Ϊ�ǵ�ָ�� 
	const int c = 1;
	int d = 2;
	const int *p2 = &d;
	int const *p3 = &c;
	cout << *p2 << endl;
	//3.����const��ʾ����������Ǹ�������
	const int e = 1;
	const int * const p4 = &e; //p4�����Ǹ�����
	const int p5 = 1; //p5�����Ǹ�����
					  //4.ָ����ָ�Ķ�������������õĶ����Ǹ��������еײ�const
	const int *p6; //p6��һ��ָ������ָ��
	int f = 1;
	const int &r = f;
	//5.ָ���������ã�Ҳ��һ�����������ã�����Ϊ����ͨ���Լ��ı���ָ�����ֵ��ʵ���϶����ǲ��Ǹ��������������
	const  int &  m = f;

	//6.��Ա������ĩβ��const
	const Student s1(12); //����һ��10���ѧ��
	Student s2(10);
	cout << s1.getStudentAge() << "��" << endl;
	cout << s2.getStudentAge() << "��" << endl; //�ǳ�������Ҳ���Ե��ó�����Ա��������������ָ���������ָ��
											   //�Ƚ�����ѧ��������

	if (s1.compareTwoStudentAge(s2)) {
		cout << "ѧ��s1����ѧ��s2" << endl;
	}
	system("pause");
	return 0;
}
