#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

struct Node
{
	int* base;
	int* top;
	int stacksize;
};

bool InitStack(Node& s, int n)
{
	s.base = (int*)malloc(n * sizeof(int));
	if (s.base == NULL) {
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
		exit(-1);
	}
	s.top = s.base;
	s.stacksize = n;
	return true;
}

bool Push(Node& s, int e)
{
	if (s.top - s.base >= s.stacksize) {
		cout << "Stack is Full" << endl;
		return false;
	}
	*s.top++ = e;
	return true;
}

bool Pop(Node& s, int& e)
{
	if (s.top == s.base) {
		cout << "Stack is Empty" << endl;
		return false;
	}
	e = *--s.top;
	return true;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	Node s;
	InitStack(s, n);
	while (1)
	{
		char command[10];
		cin >> command;
		if (!strcmp(command, "pop")) {
			int e;
			if (Pop(s, e)) {
				cout << e << endl;
			}
		}
		else if (!strcmp(command, "push")) {
			int num;
			cin >> num;
			Push(s, num);
		}
		else {
			while (s.top > s.base) {
				cout << *--s.top << " ";
			}
			break;
		}
	}
	return 0;
}