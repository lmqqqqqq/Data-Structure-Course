#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct poker
{
	string type;
	int num;
};

bool cmp(poker v1, poker v2)
{
	return v1.num > v2.num;
}


int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	vector<poker> v;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char command[10];
		cin >> command;
		if (!strcmp(command, "Append")) {
			string type1;
			cin >> type1;
			string c;
			cin >> c;
			int num1;
			if (c == "A") {
				num1 = 1;
			}
			else if (c == "2") {
				num1 = 2;
			}
			else if (c == "3") {
				num1 = 3;
			}
			else if (c == "4") {
				num1 = 4;
			}
			else if (c == "5") {
				num1 = 5;
			}
			else if (c == "6") {
				num1 = 6;
			}
			else if (c == "7") {
				num1 = 7;
			}
			else if (c == "8") {
				num1 = 8;
			}
			else if (c == "9") {
				num1 = 9;
			}
			else if (c == "10") {
				num1 = 10;
			}
			else if (c == "J") {
				num1 = 11;
			}
			else if (c == "Q") {
				num1 = 12;
			}
			else {
				num1 = 13;
			}
			poker tmp = { type1,num1 };
			v.push_back(tmp);
		}
		else if (!strcmp(command, "Pop")) {
			if (v.size() == 0) {
				cout << "NULL\n";
			}
			else {
				poker tmp = v.front();
				cout << tmp.type << ' ';
				if (tmp.num >= 2 && tmp.num <= 10) {
					cout << tmp.num<<endl;
				}
				else if (tmp.num == 1) {
					cout << "A" << endl;
				}
				else if (tmp.num == 11) {
					cout << "J" << endl;
				}
				else if (tmp.num == 12) {
					cout << "Q" << endl;
				}
				else {
					cout << "K" << endl;
				}
				v.erase(v.begin());
			}
		}
		else if (!strcmp(command, "Revert")) {
			reverse(v.begin(), v.end());
		}
		else {
			string type2;
			cin >> type2;
			vector<poker> get;
			for (vector<poker>::iterator it = v.begin(); it != v.end();) {
				if ((*it).type == type2) {
					get.push_back(*it);
					it = v.erase(it);
				}
				else {
					it++;
				}
			}
			sort(get.begin(), get.end(), cmp);
			for (vector<poker>::iterator it = get.begin(); it != get.end(); it++) {
				v.insert(v.begin(), *it);
			}
		}
	}
	if (v.size() == 0) {
		cout << "NULL\n";
	}
	else {
		for (vector<poker>::iterator it = v.begin(); it != v.end(); it++) {
			cout << (*it).type << ' ';
			if ((*it).num >= 2 && (*it).num <= 10) {
				cout << (*it).num << endl;
			}
			else if ((*it).num == 1) {
				cout << "A" << endl;
			}
			else if ((*it).num == 11) {
				cout << "J" << endl;
			}
			else if ((*it).num == 12) {
				cout << "Q" << endl;
			}
			else {
				cout << "K" << endl;
			}
		}
	}
	return 0;
}