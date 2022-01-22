#include<iostream>
#include<string>
using namespace std;

string add(string str1, string str2)//高精度加法
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    //前面补0，弄成长度相同
    if (len1 < len2)
    {
        for (int i = 1; i <= len2 - len1; i++)
            str1 = "0" + str1;
    }
    else
    {
        for (int i = 1; i <= len1 - len2; i++)
            str2 = "0" + str2;
    }
    len1 = str1.length();
    int cf = 0;//进位
    int temp;
    for (int i = len1 - 1; i >= 0; i--)
    {
        temp = str1[i] - '0' + str2[i] - '0' + cf;
        cf = temp / 10;
        temp %= 10;
        str = char(temp + '0') + str;
    }
    if (cf != 0) {
        str = char(cf + '0') + str;
    }
    return str;
}

//高精度乘法
//只能是两个正数相乘
string mul(string str1, string str2)
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    string tempstr;
    for (int i = len2 - 1; i >= 0; i--)
    {
        tempstr = "";
        int temp = str2[i] - '0';
        int t = 0;
        int cf = 0;
        if (temp != 0)
        {
            for (int j = 1; j <= len2 - 1 - i; j++) {
                tempstr += "0";
            }
            for (int j = len1 - 1; j >= 0; j--)
            {
                t = (temp * (str1[j] - '0') + cf) % 10;//每位的值
                cf = (temp * (str1[j] - '0') + cf) / 10;//进位
                tempstr = char(t + '0') + tempstr;
            }
            if (cf != 0) {
                tempstr = char(cf + '0') + tempstr;
            }
        }
        str = add(str, tempstr);
    }
    str.erase(0, str.find_first_not_of('0'));
    return str;
}

string each(string n, string a);

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n;
    string  a;
    cin >> n >> a;
    string ans="0";
    for (int i = 1; i <= n; i++) {
        string tmp = a;
        for (int j = 1; j <= i-1; j++) {
            tmp = mul(tmp, a);
        }
        tmp = mul(tmp, to_string(i));
        ans = add(ans, tmp);
    }
    cout << ans;
    return 0;
}