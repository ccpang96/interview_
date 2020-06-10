/************************************************************************/
/*@File Name         : ������ʵ����������.cpp
/*@Created Date      : 2020/5/25 22:04
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       :	ʹ��������ʵ���������У���������������ʱ���漰����̬�ڴ���ͷţ����ײ���ABA���⣬���Բ��Ƽ�
/************************************************************************/


#include <iostream>
#include <stdlib.h>
#include<atomic>		//c++11 STL�ṩ��ԭ�Ӳ���

//GCC��CAS
//#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)

//c++11�ṩ��CAS
#define CAS(ptr,oldvalue,newvalue) atomic_compare_exchange_weak(ptr,oldvalue,newvalue);

//����ڵ�
template<typename T>
struct ListNode
{
	T* _data;
	ListNode<T>* _next;
};


//��������
template<typename T>
struct Queue
{
	ListNode<T>* _head;
	ListNode<T>* _tail;
};


template<typename T>
Queue<T>* queueNew(void)
{
	ListNode<T>* tmp = new ListNode<T>;
	Queue<T>* queue = new Queue<T>;
	queue->_head = queue->_tail = tmp;	//��ʼ�����е�ͷβ��ָ��һ��dummy�ڵ�
	return queue;
}

//���
Queue<int>* myqueue;
template<typename T>
void queuePush(Queue<T>* queue, T* data)
{
	//"��׼���Ķ�׼���ã�Ȼ�󹫲����"��
	//1.����һ���½ڵ�
	ListNode<T>* onenode = new ListNode<T>;
	onenode->_data = data;
	onenode->_next = nullptr;
	ListNode<T>* tail;
	ListNode<T>* next;

	while (true)
	{
		//��ȡ��βָ���βָ���next��
		tail = queue->_tail;
		next = tail->_next;

		//�б���߳��Ѿ��Ѿ�����˲��������βָ���Ѿ����ƶ��ˣ����¿�ʼ
		if (tail != queue->_tail)		
			continue;					//������"��ʱ"�Ķ�β���������

		//���˴����Ѿ���������µĶ�βָ��
		//��ʹ��βָ���Ѿ����£�����˵������û�������߳��Ѿ�������nextָ�룬����Ҫ�ж�nextָ���Ƿ�Ϊ��


		//���nextָ�벻Ϊnullptr����fetchȫ��ָ�뵽next�� ����ʱ�������߳�����tail->next = newnode;���ǻ�û���ü�����βָ��
		if (next != nullptr)	//�����Ϊ�գ�
		{
			//"����Ϊ�֣����������"
			CAS(&queue->_tail, tail, next);
			continue;
		}

		/*
		���˴���tailָ���Ѿ����£���nextָ��Ҳָ��Ϊ��
		*/


		//�������ڵ�ɹ������˳�ѭ��
		if (CAS(&tail->_next, next, onenode))		 
			break;
	}
	//���¶�βָ��
	CAS(&queue->_tail, tail, onenode);
}


//����
template<typename T>
T*	queuePop(Queue<T>* queue)
{
	ListNode<T>* head;
	ListNode<T>* tail;
	ListNode<T>* next;
	T* data = nullptr;
	while (true)
	{
		//ȡ��ͷָ�롢βָ��͵�һ��Ԫ�ص�ָ��
		head = queue->head;
		tail = queue->tail;
		next = head->next;
		
		//Q->headָ�����ƶ���������ȡheadָ��
		if (head != queue->head)		//��������ֵ������Ԫ���Ѿ�������߳�����һ������
			continue;	

		//����ǿն���
		if (head == tail && next == nullptr)
			return nullptr;

		//�������ʱ�ȸ���tail��next���ٸ���tail�����������һ�������
		//���ǳ�����ʱ��head��tail��ȣ���tail��next���Ѿ��õ����£�
		//��������д˲��жϣ��ܿ���headָ��Ҫ����tailָ�룬��������߻�δ������
		//��������ȴ�Ѿ�������ѵ��߼�����
		if (head == tail)//prevent head exceed tail
		{
			CAS(&queue->tail, tail, next);
			continue;
		}
		//��ȡ������Ԫ�أ����¶���ͷָ�룬�������ʧ�ܣ��������������ɹ����˳�ѭ����������Ԫ���ڴ�
		//���ض���Ԫ�ظ�����������
		
		if (CAS(&queue->head, head, next))		//��headҲָ��next
			data = next->data;
			break;
	}
	delete head;		//	ABA����
	return data;
}

/*
1.�߳�T1�õ��˶���Ԫ�ص�ֵ������ͣ���˳����91�� ��
2.�߳�T2��ռCPU���ɹ�ִ���˳����91�е�CAS���������ҳɹ��Ƴ������߳�T1��ȡֵʱ��ͬ�Ķ���Ԫ�أ��ͷ����ڴ档
3.�߳�T2����һ���������߳̽�������в���������ڴ����������صĵ�ַ�Ͳ��裨2���ͷŵ���ͬ��
4.����ָ������ֵ��ĳĳ�̸߳��³��˲��裨3���·���Ľڵ��ַ
5.�߳�T1�����٣�������CAS���������ֶ���ָ������ֵ���Լ���ȡheadָ��һ������Ϊ�Լ��õ���head���ǵ�ǰ����ֵ����ʵֻ�ǵ�ַһ������ַ�������Ѿ���������ˣ��߳�T1����֪�飬�������¶���ָ�벢����head������ֵ�������ߣ�����Ԫ�ػ�û�����Ѿͱ������ɾ���ˣ������ABA���⡣

*/