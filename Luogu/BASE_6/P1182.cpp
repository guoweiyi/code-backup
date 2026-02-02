#include<iostream>
#include<vector>
using namespace std;

int n,m,maxa,mina = 0;
vector<int> a,sum;

bool check(int x){
    int now = 0,cnt = 1;
    for(int i = 1;i <= n;i++){
        if(sum[i] - sum[now] > x){
            now = i - 1;
            cnt++;
        }
    }
    return cnt <= m;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m;
    a.resize(n + 1);
    sum.resize(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        if(a[i] > mina) mina = a[i];
    }
    maxa = sum[n];
    int l = mina,r = maxa;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r;
    return 0;
}