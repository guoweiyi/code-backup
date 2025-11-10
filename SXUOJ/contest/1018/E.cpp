// 16:42AC  WA*1 line 34/35
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
#define ll long long

struct cmp {
    bool operator()(auto &a, auto &b) const {
        if(a.first != b.first) return a.first < b.first;
        else return a.second > b.second;
    }
};

priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> arr;
int n,x1,y1;

int main() {
    cin >> n;
    for(int i = 0;i < n;i++){
        int x,y;
        cin >> x >> y;
        if(i == 0) x1 = x,y1 = y;
        arr.push({x,y});
    }
    int cnt = 1,ans = -1;
    while(!arr.empty()) {
        if(arr.top().first == x1 && arr.top().second == y1) ans = cnt;
        arr.pop();
        cnt++;
    }
    if(ans <= n/10) cout << "gold";
    else if(ans <= n/10 * 3) cout << "silver";
    else if(ans <= n/10 * 6) cout << "bronze";
    else cout << "iron";
    return 0;
}
