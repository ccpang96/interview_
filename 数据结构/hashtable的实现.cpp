/************************************************************************/
/*@File Name         : hashtable的实现.cpp
/*@Created Date      : 2020/5/26 17:05
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 使用vector数组和链表实现hashtable
/************************************************************************/

//参考文献：https://my.oschina.net/bgbfbsdchenzheng/blog/496074

/* Includes *************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;

//链表结构
struct ListNode {
	int _val;
	ListNode* _next;
	ListNode(int val) : _val(val), _next(nullptr) {}
};

class hashtable {
	
	vector<ListNode*>_m;
	int _bucketSize;	//桶的数量
};

//hash函数


//hash插入


//hash删除


