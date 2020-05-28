#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;



//����
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

	//�����ƶ����캯�����ƶ���ֵ�����ʵ���ƶ�����
	
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

//����2������ת��
void process_value(const int &i) {  //int &&a = 1;��const int &a = 1;����ȫһ���ģ�����������������һ��ֵΪ1������������
	std::cout << "const LValue Processed:" << i << std::endl;
}
void process_value(int& i) {
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i) {
std::cout << "RValue processed: " << i << std::endl;
}


//2.1 û������ת��ʱ:Ҫ�������ֲ�ͬ������
/*
template <typename T> void forward_value(const T& val) {
process_value(val);
}

template <typename T> void forward_value(T& val) {
cout << val << endl;
process_value(val);
}
*/


//��������ת��֮��ֻ��Ҫ����һ��������ֵ���õĲ������Ϳ��Խ����еĲ���ԭ�ⲻ���Ĵ��ݸ�����Ŀ�������
template<typename T> void forward_value(T &&val) {
	process_value(val);
}


int main()
{

	//����1���ƶ�����
	MyString aString;
	aString = MyString("Hello"); //������ֵ�����
	std::vector<MyString> vec;
	vec.push_back(MyString("World")); //�������캯��

	
	//����2������ת��
	int a = 0;
	const int &b = 1;
	forward_value(a); // int& 
	forward_value(b); // const int& 
	forward_value(2); // int&
	system("pause");
	return 0;
}



