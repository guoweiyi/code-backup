#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
using PII = pair<int,int>;
int n;
vector<PII> g;
bool cmp(PII a,PII b){
    return a.second < b.second;
}
int main(){
    cin >> n;
    g.resize(n);
    for(int i = 0;i < n;i++) cin >> g[i].first;
    for(int i = 0;i < n;i++) cin >> g[i].second;
    sort(g.begin(), g.end(), cmp);
    int cnt = 0;
    int last_end = -1;
    for(int i = 0; i < n; i++) {
        if(g[i].first >= last_end) {
            cnt++;
            last_end = g[i].second;
        }
    }
    cout << cnt;
    return 0;
}