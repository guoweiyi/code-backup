
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    char op;
    while (n--) {
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
}
