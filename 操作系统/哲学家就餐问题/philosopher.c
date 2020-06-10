///************************************************************************/
///*@File Name         : philosopher.c
///*@Created Date      : 2020/5/17 10:14
///*@Author            : ccpang(ccpang96@163.com)
///*@blog              : www.cnblogs.com/ccpang
///*@Description       : ʹ���ź��������ѧ�ҾͲ�����
///************************************************************************/
//
//
///* Includes ---------------------------------------------------*/
//
//#include <iostream>
//#include<thread>
//#include<chrono>
//#include <semaphore.h>			//windows��û���ź�����ʵ��
//#include <vector>
//#include <unistd.h>
//
//using namespace std;
//
//
//#define		N		5				//��ѧ�Ҹ���
//#define		LEFT	(i+N-1)%N		//��i����ѧ�ҵ����ھ�
//#define		RIGHT	(i+1)%N			//��i����ѧ�ҵ����ھ�
//#define		THINKING	0			//˼��״̬
//#define		HUNGRY		1			//����״̬
//#define		EATING		2			//�Է�״̬
//int		state[N];					//��¼ÿ���˵�״̬
//int		thinkingtime[N];			//ÿ����ѧ��˼���Ĵ���
//int		eatingtime[N];				//ÿ����ѧ�ҳԷ��Ĵ���
//
//
///*�ٽ���Դ�������ķ���Ӧ�û���Ľ���*/
//sem_t mutex;			//�����ź�������ֵΪ1
//
///*һ����ѧ�ҳԱ��󣬿���Ҫ�����ھӣ�������ͬ����ϵ*/
//sem_t s[N];				//ͬ���ź�������ֵΪ0
//
//
///************************************************************************/
///*@FullName:  test_take_left_right_forks
///*@Brief:      ��������������������
///*@Parameter: i�� ��0��N-1
///*@Returns:   ��
///*@time:      2020/5/17 15:27
///*@author:    ccpang
///************************************************************************/
//void test_take_left_right_forks(int i) {
//	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
//		state[i] = EATING;			//���Ѳ��ӵ���
//		sem_post(&s[i]);			//֪ͨ��i���˿���Է��ˣ����滹��P����
//	}
//}
//
///************************************************************************/
///*@FullName:  take_forks
///*@Brief:     Ҫô�õ����Ѳ��ӣ�Ҫô����������
///*@Parameter: i��ȡֵ��0��N-1
///*@Returns:   ��
///*@time:      2020/5/17 12:27
///*@author:    ccpang
///************************************************************************/
//void take_forks(int i) {
//	sem_wait(&mutex);					//�����ٽ��� ��ΪҪ�޸�state��ֵ
//	state[i] = HUNGRY;					//�Ҷ���
//	test_take_left_right_forks(i);		//��ͼ�����Ѳ���
//	sem_post(&mutex);					//�˳��ٽ���
//	sem_wait(&s[i]);					//û�в��Ӿ�����
//}
//
///************************************************************************/
///*@FullName:  put_forks
///*@Brief:     �Ѳ��ӷŻ�ԭ������������Ҫ��ʱ��֪ͨ��������óԷ���
///*@Parameter: i����0��N-1
///*@Returns:   ��
///*@time:      2020/5/17 15:42
///*@author:    ccpang
///************************************************************************/
//void put_forks(int i) {
//
//	sem_wait(&mutex);							//�����ٽ���
//	state[i] = THINKING;						//�������Ѳ���
//	test_take_left_right_forks(LEFT);			//�����ھ��ܷ�Ͳ� ���ڲ���sem_post(i)���Խ����������ھӻ���
//	test_take_left_right_forks(RIGHT);			//�����ھ��ܷ�Ͳ�
//	sem_post(&mutex);							//�˳��ٽ���
//}
//
///************************************************************************/
///*@FullName:  think
///*@Brief:     ˼������
///*@Parameter: i : ��0��N-1
///*@Returns:   ��
///*@time:      2020/5/17 16:25
///*@author:    ccpang
///************************************************************************/
//void think(int i) {
//	thinkingtime[i]++;
//	cout << "��" << i << "����ѧ�ң���ʼ��" << thinkingtime[i] << "��˼��" << endl;
//	std::this_thread::sleep_for(std::chrono::seconds(1)); //˯��1��
//
//}
//
//
///************************************************************************/
///*@FullName:  eat
///*@Brief:     �Է�����
///*@Parameter: i : ��0��N-1
///*@Returns:   ��
///*@time:      2020/5/17 16:27
///*@author:    ccpang
///************************************************************************/
//void eat(int i) {
//	eatingtime[i]++;
//	cout << "��" << i << "����ѧ�ң���ʼ��" << eatingtime[i] << "�γԷ�" << endl;
//	std::this_thread::sleep_for(std::chrono::seconds(1)); //˯��1��
//}
///************************************************************************/
///*@FullName:  philosopher
///*@Brief:
///*@Parameter: i����ѧ�ҵ�����
///*@Returns:   ��
///*@time:      2020/5/17 10:35
///*@author:    ccpang
///************************************************************************/
//void  philosopher(int i) {		//i��ȡֵ��0��N-1
//	while (1) {					//���ʽѭ��
//		think(i);				//˼����...
//		take_forks(i);			//�õ����Ѳ��ӻ�����
//		eat(i);					//�Է�...
//		put_forks(i);			//�����Ѳ��ӷ���
//	}
//}
//
//
//int main() {
//
//	//����N���߳�
//	std::thread t[N];
//
//	//��ʼ��ͬ���ź���
//	for (int i = 0; i < N; i++) {
//		sem_init(&s[i], 0, 0);
//	}
//	//��ʼ�������ź���
//	sem_init(&mutex, 0, 1);
//
//	for (int i = 0; i < N; i++) {
//		t[i] = std::thread(philosopher, i);
//	}
//
//	for (int i = 0; i < N; i++)
//		t[i].join();
//
//	//����ͬ���ź���
//	for (int i = 0; i < N; i++)
//		sem_destroy(&s[i]);
//
//	//���ٻ����ź���
//	sem_destroy(&mutex);
//
//	system("pause");
//	return 0;
//
//}