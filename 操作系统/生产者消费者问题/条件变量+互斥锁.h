#pragma once
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class BoundedBuffer {
public:
	BoundedBuffer(const BoundedBuffer& rhs) = delete;
	BoundedBuffer& operator=(const BoundedBuffer& rhs) = delete;

	BoundedBuffer(std::size_t size)
		: begin_(0), end_(0), buffered_(0), circular_buffer_(size) {
	}

	//�������в���n
	void Produce(int n) {
		{
			std::unique_lock<std::mutex> lock(mutex_); //�����������Զ�����
													   // �ȴ����岻Ϊ����
			not_full_cv_.wait(lock, [=] { return buffered_ < circular_buffer_.size(); }); //��ֵ���ݲ������б���

																						  // �����µ�Ԫ�أ������±ꡣ
			circular_buffer_[end_] = n;
			end_ = (end_ + 1) % circular_buffer_.size(); //ѭ��

			++buffered_;
		}  // ֪ͨǰ���Զ�������

		   // ֪ͨ�����ߡ�
		not_empty_cv_.notify_one();
	}

	int Consume() {
		std::unique_lock<std::mutex> lock(mutex_);
		// �ȴ����岻Ϊ�ա�
		not_empty_cv_.wait(lock, [=] { return buffered_ > 0; });

		// �Ƴ�һ��Ԫ�ء�
		int n = circular_buffer_[begin_];
		begin_ = (begin_ + 1) % circular_buffer_.size();

		--buffered_;

		// ֪ͨǰ���ֶ�������
		lock.unlock(); //���ѵ��߳̿���������û�����
					   // ֪ͨ�����ߡ�
		not_full_cv_.notify_one();
		return n;
	}

private:
	std::size_t begin_;
	std::size_t end_;
	std::size_t buffered_;
	std::vector<int> circular_buffer_;  //ѭ��������
	std::condition_variable not_full_cv_;
	std::condition_variable not_empty_cv_;
	std::mutex mutex_;
};

BoundedBuffer g_buffer(2);
std::mutex g_io_mutex;

//������
//���� 100000 ��Ԫ�أ�ÿ 10000 ����ӡһ�Ρ�
void Producer() {
	std::thread::id thread_id = std::this_thread::get_id();
	int n = 0;
	while (n < 100000) {
		g_buffer.Produce(n);
		if ((n % 10000) == 0) {
			std::unique_lock<std::mutex> lock(g_io_mutex);
			std::cout << "Produce: " << n << " (" << thread_id << ")" << std::endl;
		}
		++n;
	}

	g_buffer.Produce(-1);
}
//������
//ÿ���ѵ� 10000 �ı�������ӡһ�Ρ�
void Consumer() {
	std::thread::id thread_id = std::this_thread::get_id();

	int n = 0;
	do {
		n = g_buffer.Consume();
		if ((n % 10000) == 0) {
			std::unique_lock<std::mutex> lock(g_io_mutex);
			std::cout << "Consume: " << n << " (" << thread_id << ")" << std::endl;
		}
	} while (n != -1);  // -1 ��ʾ�����Ѵ�ĩβ��

						// ���������ٷ�һ�� -1���������������߲��ܽ�����
	g_buffer.Produce(-1);
}
//������
int main() {
	std::vector<std::thread> threads;

	threads.push_back(std::thread(&Producer)); //һ�������� ������������
	threads.push_back(std::thread(&Consumer));
	threads.push_back(std::thread(&Consumer));
	threads.push_back(std::thread(&Consumer));

	for (auto& t : threads) {
		t.join();
	}
	system("pause");
	return 0;
}


//�ο����ף� https://segmentfault.com/a/1190000006703543