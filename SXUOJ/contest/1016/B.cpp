#include <bits/stdc++.h>
using namespace std;

int n,m,k,cnt = 0;
string s,x;

int main(){
    cin >> n >> m >> k;
    cin >> s;
    for(int i = 0;i < m;i++){
        cin >> x;
        if(cnt > 0){
            --cnt;
            continue;
        }
        if(x == s){
            cnt += k;
            cout << x << " ";
        }
        else cout << x << " ";
    }
    return 0;
}