#include<iostream>
#include<cmath>
using namespace std;

int m;
int HashTable[20005];//10005不够，例如9999之后的一个素数大于10005

bool IsPrime(int n)
{
	if (n == 1) {
		return false;
	}
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int CreateHash(char* s)
{
	int hkey = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		hkey = hkey * 37 + s[i];
		hkey %= m;
	}
	if (HashTable[hkey] == 0) {
		HashTable[hkey] = 1;
		return hkey;
	}
	else {
		int new_hkey;
		for (int i = 1; i <= m / 2; i++) {
			new_hkey = (hkey + i * i) % m;
			if (HashTable[new_hkey] == 0) {
				HashTable[new_hkey] = 1;
				return new_hkey;
			}
			new_hkey = (hkey - i * i+m*i) % m;//+m*i保证是个正数
			if (HashTable[new_hkey] == 0) {
				HashTable[new_hkey] = 1;
				return new_hkey;
			}
		}
		return -1;
	}
}

int main()
{
	int n,p;
	cin >> n >> p;
	m = p;
	while (!IsPrime(m)) {
		m++;
	}
	for (int i = 0; i < n; i++) {
		char s[105];
		cin >> s;
		int ans = CreateHash(s);
		if (ans != -1) {
			cout << ans << ' ';
		}
		else {
			cout << "- ";
		}
	}
	return 0;
}
