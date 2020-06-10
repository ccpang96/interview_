///************************************************************************/
///*@File Name         : philosopher.c
///*@Created Date      : 2020/5/17 10:14
///*@Author            : ccpang(ccpang96@163.com)
///*@blog              : www.cnblogs.com/ccpang
///*@Description       : 使用信号量解决哲学家就餐问题
///************************************************************************/
//
//
///* Includes ---------------------------------------------------*/
//
//#include <iostream>
//#include<thread>
//#include<chrono>
//#include <semaphore.h>			//windows下没有信号量的实现
//#include <vector>
//#include <unistd.h>
//
//using namespace std;
//
//
//#define		N		5				//哲学家个数
//#define		LEFT	(i+N-1)%N		//第i个哲学家的左邻居
//#define		RIGHT	(i+1)%N			//第i个哲学家的右邻居
//#define		THINKING	0			//思考状态
//#define		HUNGRY		1			//饥饿状态
//#define		EATING		2			//吃饭状态
//int		state[N];					//记录每个人的状态
//int		thinkingtime[N];			//每个哲学家思考的次数
//int		eatingtime[N];				//每个哲学家吃饭的次数
//
//
///*临界资源，对它的访问应该互斥的进行*/
//sem_t mutex;			//互斥信号量，初值为1
//
///*一个哲学家吃饱后，可能要唤醒邻居，存在着同步关系*/
//sem_t s[N];				//同步信号量，初值为0
//
//
///************************************************************************/
///*@FullName:  test_take_left_right_forks
///*@Brief:      尝试拿起左右两个叉子
///*@Parameter: i： 从0到N-1
///*@Returns:   无
///*@time:      2020/5/17 15:27
///*@author:    ccpang
///************************************************************************/
//void test_take_left_right_forks(int i) {
//	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
//		state[i] = EATING;			//两把叉子到手
//		sem_post(&s[i]);			//通知第i个人刻意吃饭了，后面还有P操作
//	}
//}
//
///************************************************************************/
///*@FullName:  take_forks
///*@Brief:     要么拿到两把叉子，要么被阻塞起来
///*@Parameter: i的取值从0到N-1
///*@Returns:   无
///*@time:      2020/5/17 12:27
///*@author:    ccpang
///************************************************************************/
//void take_forks(int i) {
//	sem_wait(&mutex);					//进入临界区 因为要修改state的值
//	state[i] = HUNGRY;					//我饿了
//	test_take_left_right_forks(i);		//试图拿两把叉子
//	sem_post(&mutex);					//退出临界区
//	sem_wait(&s[i]);					//没有叉子就阻塞
//}
//
///************************************************************************/
///*@FullName:  put_forks
///*@Brief:     把叉子放回原处，并在有需要的时候通知左邻右舍该吃饭了
///*@Parameter: i：从0到N-1
///*@Returns:   无
///*@time:      2020/5/17 15:42
///*@author:    ccpang
///************************************************************************/
//void put_forks(int i) {
//
//	sem_wait(&mutex);							//进入临界区
//	state[i] = THINKING;						//交出两把叉子
//	test_take_left_right_forks(LEFT);			//看左邻居能否就餐 其内部的sem_post(i)可以将阻塞的左邻居唤醒
//	test_take_left_right_forks(RIGHT);			//看右邻居能否就餐
//	sem_post(&mutex);							//退出临界区
//}
//
///************************************************************************/
///*@FullName:  think
///*@Brief:     思考函数
///*@Parameter: i : 从0到N-1
///*@Returns:   无
///*@time:      2020/5/17 16:25
///*@author:    ccpang
///************************************************************************/
//void think(int i) {
//	thinkingtime[i]++;
//	cout << "第" << i << "个哲学家，开始第" << thinkingtime[i] << "次思考" << endl;
//	std::this_thread::sleep_for(std::chrono::seconds(1)); //睡眠1秒
//
//}
//
//
///************************************************************************/
///*@FullName:  eat
///*@Brief:     吃饭函数
///*@Parameter: i : 从0到N-1
///*@Returns:   无
///*@time:      2020/5/17 16:27
///*@author:    ccpang
///************************************************************************/
//void eat(int i) {
//	eatingtime[i]++;
//	cout << "第" << i << "个哲学家，开始第" << eatingtime[i] << "次吃饭" << endl;
//	std::this_thread::sleep_for(std::chrono::seconds(1)); //睡眠1秒
//}
///************************************************************************/
///*@FullName:  philosopher
///*@Brief:
///*@Parameter: i是哲学家的数量
///*@Returns:   无
///*@time:      2020/5/17 10:35
///*@author:    ccpang
///************************************************************************/
//void  philosopher(int i) {		//i的取值：0到N-1
//	while (1) {					//封闭式循环
//		think(i);				//思考中...
//		take_forks(i);			//拿到两把叉子或被阻塞
//		eat(i);					//吃饭...
//		put_forks(i);			//把两把叉子放下
//	}
//}
//
//
//int main() {
//
//	//定义N个线程
//	std::thread t[N];
//
//	//初始化同步信号量
//	for (int i = 0; i < N; i++) {
//		sem_init(&s[i], 0, 0);
//	}
//	//初始化互斥信号量
//	sem_init(&mutex, 0, 1);
//
//	for (int i = 0; i < N; i++) {
//		t[i] = std::thread(philosopher, i);
//	}
//
//	for (int i = 0; i < N; i++)
//		t[i].join();
//
//	//销毁同步信号量
//	for (int i = 0; i < N; i++)
//		sem_destroy(&s[i]);
//
//	//销毁互斥信号量
//	sem_destroy(&mutex);
//
//	system("pause");
//	return 0;
//
//}