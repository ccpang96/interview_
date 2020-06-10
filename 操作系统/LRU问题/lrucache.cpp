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

	//访问缓存中的值
	int get(int key) {
		auto it = _m.find(key);			//在hashmap中查找key
		if (it != _m.end()) {			//key在hashmap中存在
			//将key对应的value挪到list的头部
			_cache.splice(_cache.begin(), _cache, it->second);
			return it->second->second;	//返回key对应的value值
		}
		else {
			return -1;
		}
	}

	//向缓存中插入新的值
	void put(int key, int value) {
		//先查找key在缓存中是否存在
		auto it = _m.find(key);
		if (it != _m.end()) {	//在缓存中存在
			it->second->second = value;		//更新_m中key对应的value
			_cache.splice(_cache.begin(), _cache, it->second);
			return;
		}

		//判断_cache是否达到_max_size
		if (_cache.size() == _max_size) {	//如果达到，就删除_cache中最后的一个值
			const auto &node = _cache.back();		//最后一个元素
			_m.erase(node.first);	//hash表中删除node对应的key这一项
			_cache.pop_back();
		}
		//将新的这一项插入list并更新hashmap的值
		_cache.emplace_front(key, value);
		_m[key] = _cache.begin();
	}

};