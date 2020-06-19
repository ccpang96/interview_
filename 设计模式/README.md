### һ������ģʽ
#### 1.1 �ֲ���̬����ʵ������ģʽ
��Ϊ�ֲ���̬����ֻ�ᱻ��ʼ��һ�Σ�������c++11�����̰߳�ȫ�ģ���������һ����򵥵ķ�����



#### 1.2����ʽ
����ʽ��ָϵͳһ���У��ͳ�ʼ������ʵ��������Ҫʱ��ֱ�ӵ��ü��ɡ���������̰߳�ȫ��û�ж��̵߳����⣩
�ڳ�������ʱ�Ͷ����˶��󣬲������ʼ����֮�󣬲����ĸ��̵߳��ó�Ա����getinstance()��ֻ�����Ƿ���
һ�������ָ����ѣ�����Ҫ�ڻ�ȡʵ���ĳ�Ա�����м�����
```

class Singleton {
public:
	//��ȡʵ��
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
	Singleton() { cout << "���캯��" << endl; }
	~Singleton() { cout << "��������" << endl; }
	Singleton(const Singleton &signal) = delete;
	const Singleton &operator=(const Singleton &signal) = delete;

private:
	static Singleton *instance;
};

//����һ���оͳ�ʼ������ʵ��
Singleton * Singleton::instance = new Singleton();



int main() {
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	if (p1 == p2)
		cout << "��ͬһ������" << endl;
	else
		cout << "����ͬһ������" << endl;

	Singleton::deleteInstance();
	system("pause");
	return 0;
}
```


### ���� �۲���ģʽ
����һ�ֶ��������֮���������ϵ��һ���������ı�ʱ���Զ�֪ͨ������������������Ӧ������Ӧ���ڴˣ������ı�Ķ����Ϊ�۲�Ŀ�꣬����֪ͨ�Ķ����Ϊ�۲��ߣ�һ���۲�Ŀ����Զ�Ӧ����۲��ߣ�������Щ�۲���֮��û���໥��ϵ�����Ը�����Ҫ���Ӻ�ɾ���۲��ߣ�ʹ��ϵͳ��������չ������ǹ۲���ģʽ��ģʽ������


�۲���ģʽ(Observer Pattern)�����������һ��һ�Զ�������ϵ��ʹ��ÿ��һ������״̬�����ı�ʱ���������������Եõ�֪ͨ�����Զ����¡��۲���ģʽ�ֽ�������-���ģ�Publish/Subscribe��ģʽ��ģ��-��ͼ��Model/View��ģʽ��Դ-��������Source/Listener��ģʽ������ߣ�Dependents��ģʽ��

#### 2.1 ģʽ�ṹ
- Subject: Ŀ��
- ConcreteSubject: ����Ŀ��
- Observer: �۲���
- ConcreteObserver: ����۲���

> ģʽͼ
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527102150181-2021994371.png)


> ʱ��ͼ
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527102338990-924493856.png)

#### 2.2 ����
![](https://img2020.cnblogs.com/blog/1755696/202005/1755696-20200527143925411-30126464.png)





#### 2.3 �ܽ�
�۲�����������ν������������֮���������ϵ��һ��Ŀ��������������۲��ߣ�һ��Ŀ��״̬�����ı䣬���еĹ۲��߶���õ�֪ͨ��