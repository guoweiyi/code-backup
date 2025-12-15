#include<iostream>
#include<string>
using namespace std;
int pos,len;
string s;
int main(){
    getline(cin, s);
    cin >> pos >> len;
    for(int i = pos - 1; i < pos + len - 1&& i < s.size(); i++) {
        cout << s[i];
    }
    return 0;
}