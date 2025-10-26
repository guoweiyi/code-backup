#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n,ans = 0;
ll m, k;
vector<ll> a(n);

bool check(int l,int r,ll k,ll m){
    ll total = a[r] - a[l] + min(abs(k - a[l]), abs(k - a[r])); //距离+返回值
    return total <= m;
}

void solve(){
    cin >> n >> m >> k;
    a.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    /*
    int r = 0,ans = 0;
    int best = 0;
    for(int l = 0; l < n;l++){//循环 l
        int L = max(r,l),R = n - 1,best = l;
        while(L <= R){
            int mid = (L + R) / 2;
            if(check(l,mid,k,m)) best = mid,L = mid + 1;
            else R = mid - 1;
        }
        r = best;
        ans = max(ans,r - l + 1);
    }*/
    int l = 0,ans = 0;
    for(int r = 0;r < n;r++){
        while(l <= r){
            if(check(l,r,k,m)) break;
            l++;
        }
        ans = max(ans,r - l + 1);
    }
    cout << ans << "\n";
}
int main() {
    solve();
    return 0;
}
