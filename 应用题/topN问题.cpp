/************************************************************************/
/*@File Name         : topN问题.cpp
/*@Created Date      : 2020/6/9 15:28
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       : 使用堆排序解决topN问题
/************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;

 
//输入是一个{3,4,6,32,23,6,63,23,65,232,12,5,6,7,4}
//输出最小的5个数 top5 {3,4,4,5,6}


class Solution {
public:
	vector<int> findTopK(vector<int>& input,int k) {
		
		
		vector<int>heap;
		for (int i = 0; i < k; i++) {
			heap.push_back(input[i]);
		}

		//构建大顶堆
		buildHeap(heap);

		for (int i = k; i < input.size(); i++) {
			if (input[i] < heap[0]) {
				heap[0] = input[i];
				adjustHeap(heap, 0, k);
			}
		}
		return heap;
	}

	//构建大顶堆
	void buildHeap(vector<int>& heap) {
		for (int i = heap.size() / 2 - 1; i >= 0; i--) { //只对堆上的父节点进行调整
			adjustHeap(heap, i, heap.size());
		}
	}

	//大顶堆调整
	void adjustHeap(vector<int>& heap, int i, int length) {
		int temp = heap[i];
		for (int k = 2 * i + 1; k < length; k = 2 * k + 1) {
			if (k + 1 < length && heap[k + 1] > heap[k])
				k = k + 1;

			if (heap[k] > temp) {
				heap[i] = heap[k];
				i = k;
			}
			else
				break;
		}
		heap[i] = temp;
	}
};



int main() {

	vector<int>input = { 3,4,6,32,23,6,63,23,65,232,12,5,6,7,4 };
	vector<int>result = Solution().findTopK(input, 5);
	for (auto & m : result)
		cout << m << endl;
	system("pause");
	return 0;
}