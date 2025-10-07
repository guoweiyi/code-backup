#include <bits/stdc++.h>
using namespace std;

int n;
string s;
long long arrH = 0, arrHJ = 0, arrHJM = 0;

int main() {
    cin >> n;
    cin >> s;
    for (char ch : s) {
        if (ch == 'h') arrH++;
        else if (ch == 'j') arrHJ += arrH;
        else if (ch == 'm') arrHJM += arrHJ;
    }
    cout << arrHJM << endl;
    return 0;
}