#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using PII = pair<int,int>;
using ll = long long;

vector<int> w,w_sum,v;
vector<ll> v_sum;
vector<PII> qj;
int n,m,w_max = -1,w_min = INT_MAX;
ll ans = LLONG_MAX,s;

ll check(int w_tmp){
    ll sum_tmp = 0;
    w_sum[0] = 0;
    v_sum[0] = 0;
    for(int i = 1;i <= n;i++){
        if(w[i] >= w_tmp){
            v_sum[i] = v_sum[i - 1] + v[i];
            w_sum[i] = w_sum[i - 1] + 1;
        }
        else{
            v_sum[i] = v_sum[i - 1];
            w_sum[i] = w_sum[i - 1];
        }
    }
    for(int i = 0;i < m;i++){
        int L = qj[i].first;
        int R = qj[i].second;
        sum_tmp += (v_sum[R] - v_sum[L - 1]) * (w_sum[R] - w_sum[L - 1]);
    }
    return sum_tmp;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m >> s;
    w.resize(n + 1),w_sum.resize(n + 1);
    v.resize(n + 1),v_sum.resize(n + 1);
    qj.resize(m);

    for(int i = 1;i <= n;i++){
        cin >> w[i] >> v[i];
        w_max = max(w_max,w[i]);
        w_min = min(w_min,w[i]);
    }
    for(int i = 0;i < m;i++) cin >> qj[i].first >> qj[i].second;

    int l = w_min,r = w_max + 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        ll Y = check(mid);
        if(Y > s) l = mid + 1;
        else r = mid - 1;
        ans = min(ans,abs(Y - s));
    }
    cout << ans;
    return 0;
}