#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int mid = n / 2;
    for (int i = 0; i < n; ++i) {
        int stars = i <= mid ? (2 * i + 1) : (2 * (n - i - 1) + 1);//上下
        int spaces = (n - stars) / 2;
        for (int j = 0; j < spaces; ++j) cout << ' ';
        for (int j = 0; j < stars; ++j) cout << '*';
        cout << endl;
    }
    return 0;
}