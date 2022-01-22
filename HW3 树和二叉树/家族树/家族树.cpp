#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

vector<string>name(1000);//������������
map<string, string>father;//���������ϵ

int main()
{
    while (1) {
        
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        getchar();
        while (n--){
            string str;
            getline(cin,str);
            int cnt = count(str.begin(), str.end(), ' ');//����ո����Ŀ
            if (cnt == 0){
                father[str] = "root";//����
                name[0] = str;
            }
            else{
                str = str.substr(cnt);//ȡ�ո�֮����ַ���
                father[str] = name[cnt - 1];
                name[cnt] = str; //���cnt�ظ���Ḳ��֮ǰ��ͬcnt������
            }
        }
        while (m--){
            string a, b, c, d;
            cin >> a >> b >> b >> c >> b >> d;
            d = d.substr(0, d.length() - 1);//ȥ��.
            switch (c[0]){
                case 'p':
                    swap(a, d);
                case 'c':
                    if (father[a] == d) {
                        cout << "True" << endl;
                    }
                    else {
                        cout << "False" << endl;
                    }
                    break;
                case 's':
                    if (father[a] == father[d] || a == d) {
                        cout << "True" << endl;
                    }
                    else {
                        cout << "False" << endl;
                    }
                    break;
                case 'a':
                    swap(a, d);
                case 'd':
                    if (a == d) {
                        cout << "True" << endl;
                        break;
                    }
                    while (father[a] != d && father[a] != "root") {
                        a = father[a];
                    }
                    if (father[a] != "root") {
                        cout << "True" << endl;
                    }
                    else {
                        cout << "False" << endl;
                    }
            }
        }
        cout << endl;
    }
    return 0;
}