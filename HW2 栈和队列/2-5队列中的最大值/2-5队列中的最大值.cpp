#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstring>
using namespace std;


struct QNode
{
	int data;
	QNode* next;
};

struct LinkQueue
{
	QNode* front;
	QNode* rear;
};

bool InitQueue(LinkQueue &q)
{
	q.front = q.rear = (QNode*)malloc(sizeof(QNode));
	if (q.front == NULL) {
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
		exit(-1);
	}
	q.front->next = NULL;
	return true;
}

bool EnQueue(LinkQueue& q, int data)
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if (p == NULL) {
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
		exit(-1);
	}
	p->data = data;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
	return true;
}

bool DeQueue(LinkQueue& q, int& data)
{
	if (q.front == q.rear) {
		cout << "Queue is Empty" << endl;
		return false;
	}
	QNode* p = q.front->next;
	data = p->data;
	q.front->next = p->next;
	if (q.rear == p) {
		q.rear = q.front;
	}
	//free(p);
	return true;
}

void display(LinkQueue q)
{
	QNode* p = q.front->next;
	while (p != q.rear) {
		cout << p->data <<' ';
		p = p->next;
	}
	cout << p->data;
	return;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	LinkQueue q;
	InitQueue(q);
	deque<int> maxDeq;  //¸¨Öú¶ÓÁÐ
	char command[10];
	int num = 0;
	while (1) {
		cin >> command;
		if (!strcmp(command, "dequeue")) {
			if (num == 0) {
				cout << "Queue is Empty" << endl;
			}
			else {
				int data;
				DeQueue(q, data);
				cout << data << endl;
				num--;
				int ret = data;
				if (maxDeq.front() == ret) {
					maxDeq.pop_front();
				}
			}
		}
		else if (!strcmp(command, "enqueue")) {
			int data;
			cin >> data;
			if (num == n) {
				cout << "Queue is Full" << endl;
			}
			else {
				EnQueue(q, data);
				num++;
				if (maxDeq.empty()) { 
					maxDeq.push_back(data);	
				}
				else {
					while (!maxDeq.empty() && maxDeq.back() < data) {
						maxDeq.pop_back();
					}
					maxDeq.push_back(data);
				}
			}
		}
		else if (!strcmp(command, "max")) {
			if (num == 0) {
				cout << "Queue is Empty" << endl;
			}
			}
		else {
			display(q);
			break;
		}
	}
	return 0;
}
