#define _CRT_SECURE_NO_DEPRECATE 
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;

 
class Trie
{
private:
	bool is_string = false;			//表示这是一个字符串了
	Trie* next[26] = { nullptr };
public:
	Trie() {}

	void insert(const string& word)//插入单词
	{
		Trie* root = this;
		for (const auto& w : word) {
			if (root->next[w - 'a'] == nullptr) root->next[w - 'a'] = new Trie();
			root = root->next[w - 'a'];
		}
		root->is_string = true;
	}

	bool search(const string& word)//查找单词
	{
		Trie* root = this;
		for (const auto& w : word) {
			if (root->next[w - 'a'] == nullptr)	return false;
			root = root->next[w - 'a'];
		}
		return root->is_string;
	}

	bool startsWith(const string& prefix)//查找前缀
	{
		Trie* root = this;
		for (const auto& p : prefix) {
			if (root->next[p - 'a'] == nullptr)return false;
			root = root->next[p - 'a'];
		}
		return true;
	}
};


//int main() {
//
//	Trie* trie = new Trie();
//
//	trie->insert("apple");
//	cout << trie->search("apple") << endl;   // 返回 true
//	cout << trie->search("app") << endl;     // 返回 false
//	cout << trie->startsWith("app") << endl; // 返回 true
//	trie->insert("app");
//	cout << trie->search("app") << endl;     // 返回 true
//	
//	system("pause");
//	return 0;
//}