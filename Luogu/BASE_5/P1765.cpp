//整行输入

#include<bits/stdc++.h>
using namespace std;

string s;
int num[26]={1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};  
int ans = 0;

int main(){
    getline(cin,s);
    for(int i = 0;i < s.size();i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            ans += num[s[i] - 'a'];
        }
        if(s[i] == ' ') ans++;
    }
    cout << ans;
    return 0;
}