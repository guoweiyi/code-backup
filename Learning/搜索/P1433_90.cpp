#include<vector>
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
using PII = pair<double,double>;

vector<PII> g;
vector<bool> vis;
int n;
double ans = 1e18;
double dist(int a, int b) {
    double dx = g[a].first - g[b].first;
    double dy = g[a].second - g[b].second;
    return sqrt(dx * dx + dy * dy);
}
double dist_from_origin(int i) {
    double dx = g[i].first;
    double dy = g[i].second;
    return sqrt(dx * dx + dy * dy);
}

void dfs(int u,int cnt,double sum){
    if(sum > ans) return;
    if(cnt == n){
        ans = min(sum,ans);
        return;
    }
    for(int i = 0;i < n;i++){
        if(!vis[i]){
            vis[i] = true;
            dfs(i,cnt + 1,sum + dist(u,i));
            vis[i] = false;
        }
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    g.resize(n);
    vis.resize(n,0);
    for(int i = 0;i < n;i++){
        cin >> g[i].first >> g[i].second;
    }
    for(int i = 0; i < n; i++) {
        vis[i] = true;
        dfs(i, 1, dist_from_origin(i));
        vis[i] = false;
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}