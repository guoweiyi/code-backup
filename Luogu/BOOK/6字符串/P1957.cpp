//字符串转数字 stoi（）
//string 拼接时to_string(b)  size();

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    char op;
    while (n--) {
        //fgets(s ,sizeof(s),stdin);读入一行 有最大输入量 含空格
        //if() last = s[0],s[0] = '';
        //sscanf(a,b);忽略空格输入两个数字
        string s;
        cin >> s;
        int a, b;
        if (s[0] == 'a' || s[0] == 'b' || s[0] == 'c') {
            op = s[0];
            cin >> a >> b;
        } else {
            a = stoi(s);
            cin >> b;
        }
        int res;
        char symbol;

        if (op == 'a') res = a + b, symbol = '+';
        else if (op == 'b') res = a - b, symbol = '-';
        else res = a * b, symbol = '*';

        string expr = to_string(a) + symbol + to_string(b) + "=" + to_string(res);

        cout << expr << "\n" << expr.size() << "\n";
    }
    return 0;
}
