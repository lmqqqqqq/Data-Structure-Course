#include<iostream>
#include<cstring>
using namespace std;

int a[100005];
int n;

int Search_Bin(char* s, int key)
{
	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (a[mid] == key) {
			if (!strcmp(s, "lower")) {
				while (mid!=0&&a[mid - 1]==key) {
					mid--;
				}
				return mid;
			}
			else {
				while (mid != n-1 && a[mid + 1] == key) {
					mid++;
				}
				return mid;
			}
		}
		else if (a[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	while (1) {
		char s[10];
		cin >> s;
		if (!strcmp(s, "done")) {
			return 0;
		}
		else {
			int key;
			cin >> key;
			int ans = Search_Bin(s, key);
			cout << ans << endl;
		}
	}
	return 0;

}