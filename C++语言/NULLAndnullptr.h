#pragma once
#include<cstdlib>
#include<iostream>
using namespace std;
int main() {

	int *p = NULL;
	int *p2 = nullptr;
	int *p3 = 0;
	cout << *p3 << endl;
	cout << *p2 << endl;
	cout << *p << endl;

	system("pause");
	return 0;
}
