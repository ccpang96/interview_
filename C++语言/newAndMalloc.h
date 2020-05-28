#pragma once
#include<cstdlib>
#include<iostream>
using std::cout;
using std::endl;
int main() {

	//1.≤‚ ‘new∫Õdelete
	int *p = new int;
	cout << *p << endl;
	*p = 3;
	cout << *p << endl;
	delete p;
	p = nullptr;
	//	cout << *p << endl;

	int *p2 = new int[10];
	p2[0] = 11;
	p2[1] = 3;
	cout << *p2 << endl;
	cout << p2[1] << endl;
	delete[] p2;
	p2 = nullptr;
	//	cout << *p2 << endl;


	//2.≤‚ ‘malloc
	int *pi = (int *)malloc(sizeof(int));
	*pi = 3;
	if (pi == nullptr) {
		printf("out of memory");
	}
	cout << *pi << endl;
	free(pi);
	cout << *pi << endl;
	p = nullptr;
	cout << *pi << endl;


	//3.≤‚ ‘calloc∫Õrealloc
	int *pc = (int *)calloc(3, sizeof(int));
	cout << *pc << endl;


	int*pr = (int *)realloc(pc, sizeof(int));
	cout << *pr << endl;
	//	free(pc);
	free(pr);


	system("pause");
	return 0;
}
