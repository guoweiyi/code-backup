#include <bits/stdc++.h>
using namespace std;

int N, A, B;
string S;
queue<char> q;

int main() {
    cin >> N >> A >> B;
    cin >> S;
    for (char ch : S) q.push(ch);
    for (int i = 0; i < A; ++i) q.pop(); 
    int keep = N - A - B;
    for (int i = 0; i < keep; ++i) {
        cout << q.front();
        q.pop();
    }
    cout << '\n';
    return 0;
}