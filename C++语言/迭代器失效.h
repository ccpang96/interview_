#pragma once
#include<iostream>
#include<vector>
using namespace std;

//���Ե�����ʧЧ�����
int main() {

	//
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(1);
	v1.push_back(2);
	for (auto &m : v1)
		printf("%d ", m);
	cout << endl;  //1 2 1 2

				   //ɾ�����������ʧЧ
	vector<int>::iterator it = v1.begin();
	while (it != v1.end()) {
		if (*it != 2) {
			it = v1.erase(it);  //�������ȡ����erase()�ķ���ֵ
		}
		else
			it++;
	}
	for (auto &m : v1)
		printf("%d ", m);
	cout << endl;

	system("pause");
	return 0;
}