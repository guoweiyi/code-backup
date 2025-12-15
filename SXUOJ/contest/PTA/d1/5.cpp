#include <iostream>
#include <string>
using namespace std;

void solve() {
    string s;
    cin >> s;

    bool letter = false;
    bool digit = false;
    bool no = false;

    if (s.size() < 6) {
        cout << "Your password is tai duan le." << endl;
        return;
    }

    for (char c : s) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            letter = true;
        else if (c >= '0' && c <= '9')
            digit = true;
        else if (c != '.')
            no = true;
    }

    if (no)
        cout << "Your password is tai luan le." << endl;
    else if (!digit)
        cout << "Your password needs shu zi." << endl;
    else if (!letter)
        cout << "Your password needs zi mu." << endl;
    else
        cout << "Your password is wan mei." << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
