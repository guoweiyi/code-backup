#include<bits/stdc++.h>
using namespace std;

string s;
stack<bool> st;
int main(){
    getline(cin, s, '@');
    for (char ch : s){
        if(ch == '(') st.push(true);
        else if(ch == ')'){
            if(st.empty()){
                cout << "NO";
                return 0;
            }
            st.pop();//抵消一次
        }
    }
    if(st.empty()) cout << "YES";
    else cout << "NO";
    return 0;
}