#include <iostream>
#include <stack>
#include <string>
using namespace std;

int n ,ans = 0; 
string s;
stack<int> st;

int main() {
    cin >> n >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') st.push(i);
        else if (s[i] == ')') {
            if (!st.empty()) {
                int l = st.top(); 
                st.pop();
                bool ok = true;
                for (int j = l + 1; j < i; j++){
                    if (s[j] != '#') {
                        ok = false; 
                        break; 
                    }
                }
                if (ok) ans = max(ans, i - l + 1);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
