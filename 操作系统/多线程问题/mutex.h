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
	std::this_thread::sleep_for(std::chrono::seconds(2)); //˯��2��
	std::string result = "fake content";

	//lock_guard������ʱ�Զ��������뿪������ʱ�������������ͷŻ�����
	std::lock_guard<std::mutex> guard(g_pages_mutex);  //�Ի������Զ������ͽ�����
	g_pages[url] = result;
}

int main()
{
	std::thread t1(save_page, "http://foo"); //�߳�1
	std::thread t2(save_page, "http://bar"); //�߳�2
	t1.join();
	t2.join();

	// safe to access g_pages without lock now, as the threads are joined
	for (const auto &pair : g_pages) {
		std::cout << pair.first << " => " << pair.second << '\n';
	}
	system("pause");
	return 0;
}