#include <iostream>
#include <vector>
#include <string>
using namespace std;
void solve() {
    int n, m;cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        int r = i % 4; 
        for(int j = 0; j < m; ++j) {
            int c = j % 4;
            bool is_x = false;
            if (r == 0) { 
                is_x = (c != 1); 
            } else if (r == 1 || r == 2) { 
                is_x = (c == 0 || c == 2);
            } else { 
                is_x = (c != 3);
            }
            cout << (is_x ? 'x' : '.');
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}