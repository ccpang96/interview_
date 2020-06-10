#pragma once
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>


std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string &url)
{
	// simulate a long page fetch
	std::this_thread::sleep_for(std::chrono::seconds(2)); //睡眠2秒
	std::string result = "fake content";

	//lock_guard对象构造时自动加锁，离开作用域时调用析构函数释放互斥锁
	std::lock_guard<std::mutex> guard(g_pages_mutex);  //对互斥锁自动加锁和解锁，
	g_pages[url] = result;
}

int main()
{
	std::thread t1(save_page, "http://foo"); //线程1
	std::thread t2(save_page, "http://bar"); //线程2
	t1.join();
	t2.join();

	// safe to access g_pages without lock now, as the threads are joined
	for (const auto &pair : g_pages) {
		std::cout << pair.first << " => " << pair.second << '\n';
	}
	system("pause");
	return 0;
}