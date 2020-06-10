//http://www.thinkingyu.com/articles/LockFreeQueue/
#include <iostream>
#include <stdint.h>
#include <stdlib.h>



//GCC的CAS
//#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)

//c++11提供的CAS
#define CAS(ptr,oldvalue,newvalue) atomic_compare_exchange_weak(ptr,oldvalue,newvalue);

#define FULL false
#define EMPTY false
#define DEFAULTSIZE 100



template<typename T, uint32_t arraysize = DEFAULTSIZE>
class CLArrayLockedFree
{
public:
	CLArrayLockedFree();
	bool push(T);
	T pop();
private:
	T m_Queue[arraysize];
	uint32_t m_CurrentWriteIndex;		//一个新元素即将插入的位置，生产者即将生产的位置
	uint32_t m_CurrentReadIndex;		//下一个可读元素的位置，消费者即将消费的位置
	uint32_t m_MaxReadIndex;			//“哨兵”，读取指针ReadIndex只能落后于该指针
	inline uint32_t countToIndex(uint32_t);
};


template<typename T, uint32_t arraysize>
CLArrayLockedFree<T, arraysize>::CLArrayLockedFree()
{
	m_CurrentWriteIndex = 0;
	m_CurrentReadIndex = 0;
	m_MaxReadIndex = 0;
}

template<typename T, uint32_t arraysize>
inline uint32_t
CLArrayLockedFree<T, arraysize>::countToIndex(uint32_t count)
{
	return (count%arraysize);
}



template<typename T, uint32_t arraysize>
bool
CLArrayLockedFree<T, arraysize>::push(T element)
{
	uint32_t CurrentWriteIndex;
	uint32_t CurrentReadIndex;
	do
	{
		CurrentReadIndex = m_CurrentReadIndex;
		CurrentWriteIndex = m_CurrentWriteIndex;
		//当前写的位置+1 = 当前读的位置
		if (countToIndex(CurrentWriteIndex + 1) == countToIndex(CurrentReadIndex))
			return FULL;
		//如果当前写的位置和我获取的当前写的位置相等，说明我获得是最新的当前写位置，那么让当前写位置= 当前写位置+1
		if (!CAS(&m_CurrentWriteIndex, CurrentWriteIndex, CurrentWriteIndex + 1))
			continue;
		//发布新元素
		m_Queue[countToIndex(CurrentWriteIndex)] = element;
		break;
	} while (1);

	// 如果发现更新不是按顺序发生就放弃处理器给别的线程
	while (!CAS(&m_MaxReadIndex, CurrentWriteIndex, CurrentWriteIndex + 1))
	{
		sched_yield();		//让当前线程主动让出处理器
	}
	return true;
}
template<typename T, uint32_t arraysize>
T CLArrayLockedFree<T, arraysize>::pop()
{
	uint32_t CurrentReadIndex;
	uint32_t result;
	do
	{
		CurrentReadIndex = m_CurrentReadIndex;
		if (countToIndex(CurrentReadIndex) == countToIndex(m_MaxReadIndex))
			return EMPTY;
		result = m_Queue[countToIndex(CurrentReadIndex)];
		if (!CAS(&m_CurrentReadIndex, CurrentReadIndex, CurrentReadIndex + 1))
			continue;
		return result;
	} while (1);
}