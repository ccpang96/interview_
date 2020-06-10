/************************************************************************/
/*@File Name         : 用链表实现无锁队列.cpp
/*@Created Date      : 2020/5/25 22:04
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       :	使用链表来实现无锁队列，但是链表在消费时，涉及到动态内存的释放，容易产生ABA问题，所以不推荐
/************************************************************************/


#include <iostream>
#include <stdlib.h>
#include<atomic>		//c++11 STL提供的原子操作

//GCC的CAS
//#define CAS(ptr , oldvalue , newvalue) __sync_bool_compare_and_swap(ptr , oldvalue , newvalue)

//c++11提供的CAS
#define CAS(ptr,oldvalue,newvalue) atomic_compare_exchange_weak(ptr,oldvalue,newvalue);

//链表节点
template<typename T>
struct ListNode
{
	T* _data;
	ListNode<T>* _next;
};


//无锁队列
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
	queue->_head = queue->_tail = tmp;	//初始化队列的头尾都指向一个dummy节点
	return queue;
}

//入队
Queue<int>* myqueue;
template<typename T>
void queuePush(Queue<T>* queue, T* data)
{
	//"该准备的都准备好，然后公布结果"，
	//1.创建一个新节点
	ListNode<T>* onenode = new ListNode<T>;
	onenode->_data = data;
	onenode->_next = nullptr;
	ListNode<T>* tail;
	ListNode<T>* next;

	while (true)
	{
		//获取队尾指针和尾指针的next域
		tail = queue->_tail;
		next = tail->_next;

		//有别的线程已经已经完成了插入操作即尾指针已经被移动了，重新开始
		if (tail != queue->_tail)		
			continue;					//不能在"过时"的队尾后插入数据

		//到此处，已经获得了最新的队尾指针
		//即使队尾指针已经最新，但是说明不了没有其它线程已经更新了next指针，所以要判断next指针是否为空


		//如果next指针不为nullptr，则fetch全局指针到next。 即此时有其他线程做了tail->next = newnode;但是还没来得及更新尾指针
		if (next != nullptr)	//如果不为空，
		{
			//"助人为乐，帮助其更新"
			CAS(&queue->_tail, tail, next);
			continue;
		}

		/*
		到此处，tail指针已经最新；且next指针也指向为空
		*/


		//如果插入节点成功，则退出循环
		if (CAS(&tail->_next, next, onenode))		 
			break;
	}
	//更新队尾指针
	CAS(&queue->_tail, tail, onenode);
}


//出队
template<typename T>
T*	queuePop(Queue<T>* queue)
{
	ListNode<T>* head;
	ListNode<T>* tail;
	ListNode<T>* next;
	T* data = nullptr;
	while (true)
	{
		//取出头指针、尾指针和第一个元素的指针
		head = queue->head;
		tail = queue->tail;
		next = head->next;
		
		//Q->head指针已移动，则重新取head指针
		if (head != queue->head)		//不是最新值，队首元素已经被别的线程抢先一步消费
			continue;	

		//如果是空队列
		if (head == tail && next == nullptr)
			return nullptr;

		//插入操作时先更新tail的next域，再更新tail，会出现这样一种情况：
		//我们出队列时，head和tail相等，但tail得next域已经得到更新，
		//如果不进行此步判断，很可能head指针要超过tail指针，造成生产者还未生产，
		//但消费者却已经完成消费的逻辑错误
		if (head == tail)//prevent head exceed tail
		{
			CAS(&queue->tail, tail, next);
			continue;
		}
		//获取待消费元素，更新队列头指针，如果更新失败，则重新来过，成功就退出循环，回收首元素内存
		//返回队首元素给调用者消费
		
		if (CAS(&queue->head, head, next))		//让head也指向next
			data = next->data;
			break;
	}
	delete head;		//	ABA问题
	return data;
}

/*
1.线程T1拿到了队首元素的值并正好停在了程序第91行 。
2.线程T2抢占CPU，成功执行了程序第91行的CAS操作，并且成功移除了与线程T1获取值时相同的队首元素，释放其内存。
3.线程T2或者一个新来的线程进行入队列操作，这个内存分配操作返回的地址和步骤（2）释放的相同。
4.队首指针最新值被某某线程更新成了步骤（3）新分配的节点地址
5.线程T1姗姗来迟，它进行CAS操作，发现队首指针最新值和自己获取head指针一样，以为自己拿到的head就是当前最新值，其实只是地址一样，地址的内容已经今非昔比了，线程T1并不知情，继续更新队首指针并回收head，返回值给调用者，队首元素还没被消费就被意外地删除了，这就是ABA问题。

*/