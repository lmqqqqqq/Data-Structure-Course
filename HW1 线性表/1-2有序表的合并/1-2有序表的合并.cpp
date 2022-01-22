#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
using namespace std;

int la[10005], lb[10005];

void MergeList(int* la, int* lb, int* &lc ,int lena,int lenb)
{
	int* pa = la;
	int* pb = lb;
	int lenc = lena + lenb;
	lc = (int*)malloc(lenc * sizeof(int));
	if (lc == NULL) {
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
	}
	int* pa_last = pa + lena - 1;
	int* pb_last = pb + lenb - 1;
	int* pc = lc;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) {
			*pc++ = *pa++;
		}
		else {
			*pc++ = *pb++;
		}
	}
	while (pa <= pa_last) {
		*pc++ = *pa++;
	}
	while (pb <= pb_last) {
		*pc++ = *pb++;
	}
	return;
}

int main()
{
	int lena = 0, lenb = 0;
	for (int i = 1; i <= 10005; i++) {
		scanf("%d", &la[i - 1]);
		if (la[i - 1] != 0) {
			lena++;
		}
		else {
			break;
		}
	}
	sort(la, la + lena);
	for (int i = 1; i <= 10005; i++) {
		scanf("%d", &lb[i - 1]);
		if (lb[i - 1] != 0) {
			lenb++;
		}
		else {
			break;
		}
	}
	sort(lb, lb + lenb);
	int* lc;
	MergeList(la, lb, lc, lena, lenb);
	for (int i = 1; i <= lena + lenb; i++) {
		printf("%d ", *(lc+i-1));
	}
	return 0;
}