/************************************************************************/
/*@File Name         : Observer.h.cpp
/*@Created Date      : 2020/5/27 10:27
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 实现观察者模式，观察者模式一般会有抽象观察者和抽象目标类，我们在这里只写有一个待观察参数的抽象目标类。
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

//参考文献：https://medium.com/@gayashanbc/explore-the-observer-design-pattern-with-c-8592459b0486
//观察者类
class Observer {
	int _id;
public:
	Observer(int id) {
		this->_id = id;
	}

	virtual void update(int val) {
		std::cout << "--观察者: " << _id << "   值为：  " << val << endl;
	}

};


//目标类
class Subject {
	int _value;
	vector<Observer*> _views;

public:
	//注册
	void attach(Observer* obs) {
		_views.push_back(obs);	
	}

	//注销
	void detach(Observer *obs) {
		for (auto it = _views.begin(); it != _views.end(); it++) {
			if (*it == obs) {
				_views.erase(it);
				return;
			}
		}
	}

	//设置值
	void setVal(int val) {
		this->_value = val;
		std::cout << "被观察对象设置了新的值" << endl;
		notify();
	}

	//获取值
	int getVal() {
		return _value;
	}

	//通知
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
//	//1.将观察者注册到目标上
//	sub1.attach(&one);
//	sub1.attach(&two);
//	sub1.attach(&three);
//	
//	//2.设置目标的值
//	std::cout << "请设置目标的值：";
//	cin >> val;
//	std::cout << endl;
//	sub1.setVal(val);
//
//	//3.移除第二个观察者
//	std::cout << "移除第二个观察者" << endl;
//	sub1.detach(&two);		
//
//
//	//2.设置目标的值
//	std::cout << "请设置目标的值：" << std::endl;
//	cin >> val;
//	std::cout << endl;
//	sub1.setVal(val);
//
//	//
//	std::cout << "重新注册第二个观察者" << endl;
//	sub1.attach(&two);
//
//	std::cout << "请输入值：" << std::endl;
//	cin >> val;
//	sub1.setVal(val);
//
//
//	system("pause");
//	return 0;
//}