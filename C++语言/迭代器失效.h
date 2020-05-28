#pragma once
#include<iostream>
#include<vector>
using namespace std;

//测试迭代器失效的情况
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

				   //删除引起迭代器失效
	vector<int>::iterator it = v1.begin();
	while (it != v1.end()) {
		if (*it != 2) {
			it = v1.erase(it);  //如果不获取返回erase()的返回值
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