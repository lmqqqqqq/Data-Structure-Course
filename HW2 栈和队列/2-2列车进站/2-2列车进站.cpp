#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

struct Node
{
	char* base;
	char* top;
	int stacksize;
};


bool InitStack(Node& s)
{
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(int));
	if (s.base == NULL) {
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
		exit(-1);
	}
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
}

bool Push(Node& s, char e)
{
	if (s.top - s.base >= s.stacksize) {
		s.base = (char*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(int));
		if (s.base == NULL) {
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
			exit(-1);
		}
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return true;
}

bool Pop(Node& s, char& e)
{
	if (s.top == s.base) {
		return false;
	}
	e = *--s.top;
	return true;
}

char showtop(Node s)
{
	return *--s.top;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	string in_order, out_order;
	cin >> in_order;
	while (cin >> out_order) {
		Node s;
		InitStack(s);
		int i, j;
		for (i = 0, j = 0; i < in_order.length();) {
			if (in_order[i] == out_order[j]) {
				i++;
				j++;
				continue;
			}
			if (s.top != s.base) {
				char e1 = showtop(s);
				if (e1 == out_order[j]) {
					Pop(s, e1);
					j++;
				}
				else {
					Push(s, in_order[i]);
					i++;
				}
			}
			else {
				Push(s, in_order[i]);
				i++;
			}
		}
		if (j == out_order.length()) {
			cout << "yes" << endl;
			continue;
		}
		for (; j < in_order.length(); j++) {
			char e2;
			Pop(s, e2);
			if (e2 == out_order[j]) {
				if (j == in_order.length() - 1) {
					cout << "yes" << endl;
					break;
				}
				else {
					continue;
				}
			}
			else {
				cout << "no" << endl;
				break;
			}
		}
	}
	return 0;


}