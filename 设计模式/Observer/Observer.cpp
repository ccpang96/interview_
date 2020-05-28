/************************************************************************/
/*@File Name         : Observer.h.cpp
/*@Created Date      : 2020/5/27 10:27
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : ʵ�ֹ۲���ģʽ���۲���ģʽһ����г���۲��ߺͳ���Ŀ���࣬����������ֻд��һ�����۲�����ĳ���Ŀ���ࡣ
/************************************************************************/

/* Includes *************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;

//�ο����ף�https://medium.com/@gayashanbc/explore-the-observer-design-pattern-with-c-8592459b0486
//�۲�����
class Observer {
	int _id;
public:
	Observer(int id) {
		this->_id = id;
	}

	virtual void update(int val) {
		std::cout << "--�۲���: " << _id << "   ֵΪ��  " << val << endl;
	}

};


//Ŀ����
class Subject {
	int _value;
	vector<Observer*> _views;

public:
	//ע��
	void attach(Observer* obs) {
		_views.push_back(obs);	
	}

	//ע��
	void detach(Observer *obs) {
		for (auto it = _views.begin(); it != _views.end(); it++) {
			if (*it == obs) {
				_views.erase(it);
				return;
			}
		}
	}

	//����ֵ
	void setVal(int val) {
		this->_value = val;
		std::cout << "���۲�����������µ�ֵ" << endl;
		notify();
	}

	//��ȡֵ
	int getVal() {
		return _value;
	}

	//֪ͨ
	void notify() {
		for (int i = 0; i < _views.size(); ++i) {
			_views[i]->update(_value);
		}
	}

};



//int main() {
//
//	Subject sub1;
//	Observer one(1), two(2), three(3);
//	float val;
//
//	//1.���۲���ע�ᵽĿ����
//	sub1.attach(&one);
//	sub1.attach(&two);
//	sub1.attach(&three);
//	
//	//2.����Ŀ���ֵ
//	std::cout << "������Ŀ���ֵ��";
//	cin >> val;
//	std::cout << endl;
//	sub1.setVal(val);
//
//	//3.�Ƴ��ڶ����۲���
//	std::cout << "�Ƴ��ڶ����۲���" << endl;
//	sub1.detach(&two);		
//
//
//	//2.����Ŀ���ֵ
//	std::cout << "������Ŀ���ֵ��" << std::endl;
//	cin >> val;
//	std::cout << endl;
//	sub1.setVal(val);
//
//	//
//	std::cout << "����ע��ڶ����۲���" << endl;
//	sub1.attach(&two);
//
//	std::cout << "������ֵ��" << std::endl;
//	cin >> val;
//	sub1.setVal(val);
//
//
//	system("pause");
//	return 0;
//}