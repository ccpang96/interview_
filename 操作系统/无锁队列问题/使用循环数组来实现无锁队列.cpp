//http://www.thinkingyu.com/articles/LockFreeQueue/
#include <iostream>
#include <stdint.h>
#include <stdlib.h>



//GCC��CAS
//#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)

//c++11�ṩ��CAS
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
	uint32_t m_CurrentWriteIndex;		//һ����Ԫ�ؼ��������λ�ã������߼���������λ��
	uint32_t m_CurrentReadIndex;		//��һ���ɶ�Ԫ�ص�λ�ã������߼������ѵ�λ��
	uint32_t m_MaxReadIndex;			//���ڱ�������ȡָ��ReadIndexֻ������ڸ�ָ��
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
		//��ǰд��λ��+1 = ��ǰ����λ��
		if (countToIndex(CurrentWriteIndex + 1) == countToIndex(CurrentReadIndex))
			return FULL;
		//�����ǰд��λ�ú��һ�ȡ�ĵ�ǰд��λ����ȣ�˵���һ�������µĵ�ǰдλ�ã���ô�õ�ǰдλ��= ��ǰдλ��+1
		if (!CAS(&m_CurrentWriteIndex, CurrentWriteIndex, CurrentWriteIndex + 1))
			continue;
		//������Ԫ��
		m_Queue[countToIndex(CurrentWriteIndex)] = element;
		break;
	} while (1);

	// ������ָ��²��ǰ�˳�����ͷ���������������߳�
	while (!CAS(&m_MaxReadIndex, CurrentWriteIndex, CurrentWriteIndex + 1))
	{
		sched_yield();		//�õ�ǰ�߳������ó�������
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