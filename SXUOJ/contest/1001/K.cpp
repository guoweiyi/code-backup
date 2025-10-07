#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int X = (n + 1) / 2; 
        for(int i = 1;i < n;i++) cout << X - i << " ";
        cout << X - n << endl;
    }
    return 0;
}
