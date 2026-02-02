//qian 是前缀和 qian的数值是改处的起火叠加
//used 是差分
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
using PII = pair<ll,ll>;

vector<PII> add;
vector<ll> alls;
int n,qian = 0;
int used[40010];
ll res = 0;

int find(ll x){
    ll l = 0,r = alls.size() - 1;
    while(l < r){
        ll mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1; 
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    for(int i = 0;i < n;i++){
        ll a,b;
        cin >> a >> b;
        alls.push_back(a);
        alls.push_back(b);
        add.push_back({a,b});
    }

    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());

    for(int i = 0;i < n;i++){
        int L = find(add[i].first);
        int R = find(add[i].second);
        used[L]++;
        used[R]--;
    }
    for (int i = 0; i < (int)alls.size() - 1; i++) {
        qian += used[i];
        if(qian > 0) res += alls[i + 1] - alls[i];
    }
    cout << res;
    return 0;
}