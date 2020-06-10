#pragma once
#include<iostream>
#include<thread>
#include<memory>
#include<atomic>


using namespace std;
std::atomic<int> a(0);
int b(0);

//memory_order_relaxed： 仅对此操作要求原子性，和修改顺序一致性。(自增引用计数，std::shared_ptr)中
//memory_order_release确保了线程1在进行原子操作前所有写在前面的非原子内存写入都已经完成了,
//memory_order_acquire确保了线程2不能把任何写在原子操作之后的非原子内存读取乱序到原子操作之前执行
//shared_ptr里存放的指针是p
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
		std::cout << b << std::endl; //b不一定为5！
	}
}

int main()
{
	std::thread t1(thread1);
	std::thread t2(thread2);

	t1.join();
	t2.join();
	// 此时 a 为**一定** 2.
	system("pause");
	return 0;
}

