#include<iostream>
using namespace std;
int n, a[500010], c[500010];
long long ans;

void msort(int b, int e)//πÈ≤¢≈≈–Ú
{
    if (b == e) {
        return;
    }
    int mid = (b + e) / 2;
    int i = b;
    int j = mid + 1;
    int k = b;
    msort(b, mid);
    msort(mid + 1, e);
    while (i <= mid && j <= e) {
        if (a[i] <= a[j]) {
            c[k++] = a[i++];
        }
        else {
            c[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) {
        c[k++] = a[i++];
    }
    while (j <= e) {
        c[k++] = a[j++];
    }
    for (int l = b; l <= e; l++) {
        a[l] = c[l];
    }
}

int main()
{
    while (1) {
        cin >> n;
        if (n == 0) {
            break;
        }
        ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        msort(1, n);
        cout << ans << endl;
    }
    return 0;
}