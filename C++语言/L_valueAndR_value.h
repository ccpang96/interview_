#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;



//例子
class MyString {
private:
	char* _data;
	size_t   _len;
	void _init_data(const char *s) {
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}
public:
	MyString() {
		_data = NULL;
		_len = 0;
	}

	MyString(const char* p) {
		_len = strlen(p);
		_init_data(p);
	}

	MyString(const MyString& str) {
		_len = str._len;
		_init_data(str._data);
		std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
	}

	MyString& operator=(const MyString& str) {
		if (this != &str) {
			_len = str._len;
			_init_data(str._data);
		}
		std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
		return *this;
	}

	//定义移动构造函数和移动赋值运算符实现移动语义
	
	MyString(MyString&& str) {
	std::cout << "Move Constructor is called! source: " << str._data << std::endl;
	_len = str._len;
	_data = str._data;
	str._len = 0;
	str._data = NULL;
	}

	MyString& operator=(MyString&& str) {
	std::cout << "Move Assignment is called! source: " << str._data << std::endl;
	if (this != &str) {
	_len = str._len;
	_data = str._data;
	str._len = 0;
	str._data = NULL;
	}
	return *this;
	}
	
	virtual ~MyString() {
		if (_data) free(_data);
	}
};

//例子2：完美转发
void process_value(const int &i) {  //int &&a = 1;和const int &a = 1;是完全一样的，即现在数据区开辟一个值为1的无名整型数
	std::cout << "const LValue Processed:" << i << std::endl;
}
void process_value(int& i) {
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i) {
std::cout << "RValue processed: " << i << std::endl;
}


//2.1 没有完美转发时:要重载两种不同的类型
/*
template <typename T> void forward_value(const T& val) {
process_value(val);
}

template <typename T> void forward_value(T& val) {
cout << val << endl;
process_value(val);
}
*/


//有了完美转发之后：只需要定义一个接受右值引用的参数，就可以将所有的参数原封不动的传递给所有目标参数。
template<typename T> void forward_value(T &&val) {
	process_value(val);
}


int main()
{

	//例子1：移动语义
	MyString aString;
	aString = MyString("Hello"); //拷贝赋值运算符
	std::vector<MyString> vec;
	vec.push_back(MyString("World")); //拷贝构造函数

	
	//例子2：完美转发
	int a = 0;
	const int &b = 1;
	forward_value(a); // int& 
	forward_value(b); // const int& 
	forward_value(2); // int&
	system("pause");
	return 0;
}



