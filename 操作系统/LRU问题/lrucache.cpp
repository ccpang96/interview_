/************************************************************************/
/*@File Name         : lrucache.cpp
/*@Created Date      : 2020/5/25 6:19
/*@Author            : ccpang(ccpang96@163.com)
/*@blog              : www.cnblogs.com/ccpang
/*@Description       :
/************************************************************************/

/* Includes *************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
#include<list>
using namespace std;

 
class LRUCache {
private:
	int _max_size;
	list<pair<int, int>> _cache;
	unordered_map<int, list<pair<int, int>>::iterator> _m;
public:
	LRUCache(int max_size) {
		_max_size = max_size;
	}

	//���ʻ����е�ֵ
	int get(int key) {
		auto it = _m.find(key);			//��hashmap�в���key
		if (it != _m.end()) {			//key��hashmap�д���
			//��key��Ӧ��valueŲ��list��ͷ��
			_cache.splice(_cache.begin(), _cache, it->second);
			return it->second->second;	//����key��Ӧ��valueֵ
		}
		else {
			return -1;
		}
	}

	//�򻺴��в����µ�ֵ
	void put(int key, int value) {
		//�Ȳ���key�ڻ������Ƿ����
		auto it = _m.find(key);
		if (it != _m.end()) {	//�ڻ����д���
			it->second->second = value;		//����_m��key��Ӧ��value
			_cache.splice(_cache.begin(), _cache, it->second);
			return;
		}

		//�ж�_cache�Ƿ�ﵽ_max_size
		if (_cache.size() == _max_size) {	//����ﵽ����ɾ��_cache������һ��ֵ
			const auto &node = _cache.back();		//���һ��Ԫ��
			_m.erase(node.first);	//hash����ɾ��node��Ӧ��key��һ��
			_cache.pop_back();
		}
		//���µ���һ�����list������hashmap��ֵ
		_cache.emplace_front(key, value);
		_m[key] = _cache.begin();
	}

};