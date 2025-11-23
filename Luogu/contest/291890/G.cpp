#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

bool starts_with(const string& s, const string& prefix) {
    if (s.length() < prefix.length()) {
        return false;
    }
    return s.substr(0, prefix.length()) == prefix;
}

bool ends_with(const string& s, const string& suffix) {
    if (s.length() < suffix.length()) {
        return false;
    }
    return s.substr(s.length() - suffix.length()) == suffix;
}

void solve() {
    int n;cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    int composite_count = 0;
    for(int i = 0; i < n; ++i) {
        const string& si = s[i];
        int len_si = si.length();
        if (len_si < 2) continue;
        bool is_composite = false;
        for(int k = 1; k < len_si; ++k) {
            string pi = si.substr(0, k);
            string qi = si.substr(k);
            
            bool found_p = false;
            
            for(int j = 0; j < n; ++j) {
                if(i == j) continue; 
                if(starts_with(s[j], pi)) {
                    found_p = true;
                    break;
                }
            }
            if (!found_p) continue; 
            bool found_q = false;
            for(int k_idx = 0; k_idx < n; ++k_idx) {
                if(i == k_idx) continue; // 必须是集合中另一个字符串
                if(ends_with(s[k_idx], qi)) {
                    found_q = true;
                    break;
                }
            }

            if (found_p && found_q) {
                is_composite = true;
                break;
            }
        }

        if (is_composite) {
            composite_count++;
        }
    }

    cout << composite_count << endl;
}

int main(){
    solve();
    return 0;
}

