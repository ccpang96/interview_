### 一、单例模式
#### 1.1 局部静态变量实现懒汉模式
因为局部静态变量只会被初始化一次，而且在c++11后是线程安全的，所以这是一种最简单的方法。



#### 1.2饿汉式
饿汉式：指系统一运行，就初始化创建实例，当需要时，直接调用即可。（本身就线程安全，没有多线程的问题）
在程序运行时就定义了对象，并对其初始化，之后，不管哪个线程调用成员函数getinstance()都只不过是返回
一个对象的指针而已，不需要在获取实例的成员函数中加锁。
```

class Singleton {
public:
	//获取实例
	static Singleton* getInstance() {
		return instance;
	}

	static void deleteInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
private:
	Singleton() { cout << "构造函数" << endl; }
	~Singleton() { cout << "析构函数" << endl; }
	Singleton(const Singleton &signal) = delete;
	const Singleton &operator=(const Singleton &signal) = delete;

private:
	static Singleton *instance;
};

//程序一运行就初始化创建实例
Singleton * Singleton::instance = new Singleton();



int main() {
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	if (p1 == p2)
		cout << "是同一个对象" << endl;
	else
		cout << "不是同一个对象" << endl;

	Singleton::deleteInstance();
	system("pause");
	return 0;
}
```


### 二、 观察者模式
建立一种对象与对象之间的依赖关系，一个对象发生改变时将自动通知其他对象，其他对象将相应做出反应。在此，发生改变的对象称为观察目标，而被通知的对象称为观察者，一个观察目标可以对应多个观察者，而且这些观察者之间没有相互联系，可以根据需要增加和删除观察者，使得系统更易于扩展，这就是观察者模式的模式动机。


观察者模式(Observer Pattern)：定义对象间的一种一对多依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新。观察者模式又叫做发布-订阅（Publish/Subscribe）模式、模型-视图（Model/View）模式、源-监听器（Source/Listener）模式或从属者（Dependents）模式。

#### 2.1 模式结构
- Subject: 目标
- ConcreteSubject: 具体目标
- Observer: 观察者
- ConcreteObserver: 具体观察者

> 模式图
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527102150181-2021994371.png)


> 时序图
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527102338990-924493856.png)

#### 2.2 代码
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527143925411-30126464.png)





#### 2.3 总结
观察者描述了如何建立对象与对象之间的依赖关系，一个目标可以有任意多个观察者，一旦目标状态发生改变，所有的观察者都会得到通知。