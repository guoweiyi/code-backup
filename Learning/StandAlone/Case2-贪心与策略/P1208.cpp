#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
int n,m,ans = 0;
vector<PII> a;

bool cmp(PII x,PII y){
    return x.first < y.first;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m;
    a.resize(m);
    for(int i = 0;i < m;i++) cin >> a[i].first >> a[i].second;
    sort(a.begin(),a.end(),cmp);

    for(int i = 0;i < m;i++){
        if(n <= a[i].second){
            ans += a[i].first * n;
            break;
        }
        else{
            ans += a[i].first * a[i].second;
            n -= a[i].second;
        }
    }
    cout << ans;
    return 0;
}