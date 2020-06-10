#pragma once
// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
	std::unique_lock<std::mutex> lck(mtx); //这里也可以使用lock_gurad<std::mutex>lck(mtx)来加锁
	while (!ready)
		cv.wait(lck);
	// ...
	std::cout << "thread " << id << '\n';
}

void go() {
	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all(); //主线程让ready变成true,然后通知所有线程
}

int main()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_id, i); //函数名称，函数的参数

	std::cout << "10 threads ready to race...\n";
	go();                       // go!

	for (auto& th : threads) th.join();

	system("pause");
	return 0;
}