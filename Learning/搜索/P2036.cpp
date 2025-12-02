#include<iostream>
#include<vector>
#include <climits>
using namespace std;
#define ll long long
vector<int> s,k;
int deep,n,ans = INT_MAX;

void dfs(ll s1,ll k1,int e,bool used){
    if(e == n){
        if(used) ans = min(ans,(int)abs(s1 - k1));
        return;
    }
    dfs(s1, k1, e + 1, used);
    dfs(s1 * s[e], k1 + k[e], e + 1, true);
}

int main(){
    cin >> n;
    s.resize(n);
    k.resize(n);
    for(int i = 0;i < n;i++){
        cin >> s[i] >> k[i];
    } 
    dfs(1,0,0,false);
    cout << ans;
    return 0;
}