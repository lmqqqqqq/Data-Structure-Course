#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

typedef struct ship//飞船信息
{
	float total;//总值
	float speed;//速度
	float speed_w;//速度权值
	float fire;//火力
	float fire_w;//火力权值
	float food;//食物
	float food_w;//食物权值
	float fuel;//燃料
	float fuel_w;//燃料权值
}ship;

typedef struct ship_order//单个飞船信息
{
	string name;
	ship* info;
}ship_order;

typedef struct TrieNode//字典树结点
{
	bool IsEnd;//是否为字典树的叶子结点
	ship* node;
	TrieNode** map;
	TrieNode() {
		IsEnd = false;
		node = NULL;
		map = new TrieNode * [63]{}; //26个字母与0~9与下划线'_'，共63个
	}
}TrieNode;

//找到对应元素的位置
int find_pos(char c)
{
	if (c >= 'A' && c <= 'z') {
		return int(c - 'A');
	}
	else if (c >= '0' && c <= '9') {
		return int(c - '0' + 52);
	}
	else {
		return 62;
	}
}

//字典树
class Trie
{
public:
	Trie();
	TrieNode* read(string name);
	void insert(string name);
	void init();
	void set(ship*& node, char* kind, float data, float w);
	void order();
	void display();
private:
	int num;
	TrieNode* root;
	ship_order* ship_name;
};

Trie::Trie()
{
	num = 0;
	root = new(nothrow)TrieNode;
	ship_name = NULL;
}

void Trie::set(ship*& node, char* kind, float data, float w)
{
	if (!strcmp(kind, "speed")) {
		node->speed = data;
		node->speed_w = w;
	}
	else if (!strcmp(kind, "fire")) {
		node->fire = data;
		node->fire_w = w;
	}
	else if (!strcmp(kind, "food")) {
		node->food = data;
		node->food_w = w;
	}
	else {
		node->fuel = data;
		node->fuel_w = w;
	}
}

TrieNode* Trie::read(string name)
{
	TrieNode* p = root;
	for (int i = 0; i < name.size(); i++) {
		int pos = find_pos(name[i]);
		if (i == name.size() - 1) {
			if (p->map[pos]->IsEnd == true) {
				return p->map[pos];
			}
			else {
				return NULL;
			}
		}
		if (p->map[pos] == NULL) {
			return NULL;
		}
		p = p->map[pos];
	}
}

void Trie::insert(string name)
{
	TrieNode* p = root;
	for (int i = 0; i < name.size(); i++) {
		int pos = find_pos(name[i]);
		if (p->map[pos] == NULL) {
			TrieNode* node = new(nothrow)TrieNode;
			p->map[pos] = node;
		}
		if (i == name.size() - 1) {
			p->map[pos]->IsEnd = true;
		}
		else {
			p = p->map[pos];
		}
	}
}

void Trie::init()
{
	char kind[6];
	float w;
	cout << "请输入飞船的数量" << endl;
	cin >> num;
	ship_name = new(nothrow)ship_order[num];
	for (int i = 1; i <= 4; i++) {
		cout << "请输入飞船的数据种类和权重" << endl;
		cin >> kind;
		cin >> w;
		string name;
		float data;
		for (int j = 0; j < num; j++) {
			cout << "请输入飞船的名字和数据" << endl;
			cin >> name;
			if (i == 1) {
				ship_name[j].name = name;
			}
			cin >> data;
			TrieNode* temp;
			if (read(name) == NULL) {
				insert(name);
				temp = read(name);
				temp->node = new(nothrow)ship;
			}
			else {
				temp = read(name);
			}
			set(temp->node, kind, data, w);
			if (i == 4) {
				ship* p = temp->node;
				p->total = p->food * p->food_w + p->fire * p->fire_w + p->speed * p->speed_w + p->fuel * p->fuel_w;
			}
		}
	}
}

void Trie::order()
{
	for (int i = 0; i < num; i++) {
		ship_name[i].info = read(ship_name[i].name)->node;
	}
	int gap = num;
	while (gap > 1) {
		gap /= 2;
		for (int i = 0; i < num - gap; i++) {
			int end = i;
			ship_order temp = ship_name[end + gap];
			while (end >= 0) {
				if (temp.info->total < ship_name[end].info->total) {
					ship_name[end + gap] = ship_name[end];
					end -= gap;
				}
				else {
					break;
				}
			}
			ship_name[end + gap] = temp;
		}
	}
}

void Trie::display()
{
	cout << setiosflags(ios::right) << setw(15) << "name" << setw(10) << "speed" << setw(10) << "fire" << setw(10) << "food" << setw(10) << "fuel" << setw(10) << "total" << endl;
	for (int i = num - 1; i >= 0; i--) {
		cout << setw(15) << ship_name[i].name
			<< setw(10) << ship_name[i].info->speed * ship_name[i].info->speed_w
			<< setw(10) << ship_name[i].info->fire * ship_name[i].info->fire_w
			<< setw(10) << ship_name[i].info->food * ship_name[i].info->food_w
			<< setw(10) << ship_name[i].info->fuel * ship_name[i].info->fuel_w
			<< setw(10) << ship_name[i].info->total
			<< endl;
	}
}

int main()
{
	Trie T;
	T.init();
	T.order();
	T.display();
	return 0;
}