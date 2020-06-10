#pragma once
#include<iostream>
#include<thread>
#include<memory>
#include<atomic>


using namespace std;
std::atomic<int> a(0);
int b(0);

//memory_order_relaxed�� ���Դ˲���Ҫ��ԭ���ԣ����޸�˳��һ���ԡ�(�������ü�����std::shared_ptr)��
//memory_order_releaseȷ�����߳�1�ڽ���ԭ�Ӳ���ǰ����д��ǰ��ķ�ԭ���ڴ�д�붼�Ѿ������,
//memory_order_acquireȷ�����߳�2���ܰ��κ�д��ԭ�Ӳ���֮��ķ�ԭ���ڴ��ȡ����ԭ�Ӳ���֮ǰִ��
//shared_ptr���ŵ�ָ����p
void thread1()
{
	b = 5;
	int x = a.fetch_add(1, std::memory_order_relaxed);
}


void thread2()
{
	int x = a.fetch_add(1, std::memory_order_relaxed);
	int read_b = b;
	if (x == 1)
	{
		std::cout << b << std::endl; //b��һ��Ϊ5��
	}
}

int main()
{
	std::thread t1(thread1);
	std::thread t2(thread2);

	t1.join();
	t2.join();
	// ��ʱ a Ϊ**һ��** 2.
	system("pause");
	return 0;
}

