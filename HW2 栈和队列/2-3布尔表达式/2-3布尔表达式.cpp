#include<iostream>
#include<stack>
#include<cstdio>
using namespace std;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

int N;

struct Node
{
	char* base;
	char* top;
	int stacksize;
};

int Precede(char a, char b)
{
	if (a == '&' && (b == '&' || b == '|' || b == ')' || b == '\n')) {
		return 1;
	}
	if (a == '&' && (b == '!' || b == '(')) {
		return -1;
	}
	if (a == '|' && (b == '&' || b == '!' || b == '(')) {
		return -1;
	}
	if (a == '|' && (b == '|' || b == ')' || b == '\n')) {
		return 1;
	}
	if (a == '!' && (b == '&' || b == '|' || b == '!' || b == ')' || b == '\n')) {
		return 1;
	}
	if (a == '!' && b == '(') {
		return -1;
	}
	if (a == '(' && (b == '&' || b == '|' || b == '!' || b == '(')) {
		return -1;
	}
	if (a == '(' && b == ')') {
		return 0;
	}
	if (a == ')') {
		return 1;
	}
	if (a == '#' && (b == '&' || b == '|' || b == '!' || b == '(')) {
		return -1;
	}
	if (a == '#' && b == '\n') {
		return 0;
	}
	return 0;
}

bool InitStack(Node& s)
{
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(int));
	if (s.base == NULL) {
		cout << "动态内存申请失败" << endl;
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
			cout << "动态内存申请失败" << endl;
			exit(-1);
		}
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return true;
}

char showtop(Node s)
{
	return *--s.top;
}

bool Pop(Node& s, char& e)
{
	if (s.top == s.base) {
		return false;
	}
	e = *--s.top;
	return true;
}

bool ifOPND(char c)
{
	if (c == 'V' || c == 'F') {
		return true;
	}
	else {
		return false;
	}
}

char Operate(char a, char theta, char b)
{
	int a1, b1;
	if (a == 'V') {
		a1 = 1;
	}
	else {
		a1 = 0;
	}
	if (b == 'V') {
		b1 = 1;
	}
	else {
		b1 = 0;
	}
	if (theta == '|') {
		if (a1 || b1 == 1) {
			return 'V';
		}
		else {
			return 'F';
		}
	}
	else {
		if (a1 && b1 == 1) {
			return 'V';
		}
		else {
			return 'F';
		}
	}

}

void EvaluateExpression()
{
	while (1) {
		bool flag = true;
		Node OPTR, OPND;
		InitStack(OPTR);
		Push(OPTR, '#');
		InitStack(OPND);
		char c;
		while (1) {
			c = getchar();
			if (c == EOF) {
				flag = false;
				break;
			}
			if (c != ' ') {
				break;
			}
		}
		if (!flag) {
			break;
		}
		char e = showtop(OPTR);
		while (c != '\n' || e != '#') {
			if (ifOPND(c)) {//不是运算符则进栈
				Push(OPND, c);
				while (1) {
					c = getchar();
					if (c == EOF) {
						flag = false;
						break;
					}
					if (c != ' ') {
						break;
					}
				}
				if (!flag) {
					break;
				}
			}
			else {
				char e1 = showtop(OPTR);
				switch (Precede(e1, c)) {
					case -1://栈顶元素优先权低
						Push(OPTR, c);
						while (1) {
							c = getchar();
							if (c == EOF) {
								flag = false;
								break;
							}
							if (c != ' ') {
								break;
							}
						}
						break;
					case  0: //脱括号并接受下一字符
						char x;
						Pop(OPTR, x);
						while (1) {
							c = getchar();
							if (c == EOF) {
								flag = false;
								break;
							}
							if (c != ' ') {
								break;
							}
						}
						break;
					case 1: //退栈并将运算结果入栈
						char theta;
						Pop(OPTR, theta);
						if (theta != '!') {
							char a, b;
							Pop(OPND, b);
							Pop(OPND, a);
							Push(OPND, Operate(a, theta, b));
						}
						else {
							char a;
							Pop(OPND, a);
							if (a == 'V') {
								Push(OPND, 'F');
							}
							else {
								Push(OPND, 'V');
							}
						}
						break;
				}
			}
			e = showtop(OPTR);
		}
		if (!flag) {
			break;
		}
		char e2 = showtop(OPND);
		N++;
		cout << "Expression "<<N<<": "<<e2 << endl;
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	EvaluateExpression();
	return 0;
}