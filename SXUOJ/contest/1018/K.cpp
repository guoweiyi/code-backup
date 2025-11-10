#include <iostream>
#include <string>
using namespace std;

int n;
bool cnt = 0;
string s;

int main() {
    cin >> n >> s;
    for(int i = 0;i < n;i++) {
		if(cnt == 1) {
			if (s[i] == '1') cout << 0; 
            else cout << 1,cnt = 0;
		} 
        else {
            if (s[i] == '1') cnt = 1;
			cout << s[i];
		}
	}
    return 0;
}
