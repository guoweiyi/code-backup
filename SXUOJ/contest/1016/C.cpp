#include <bits/stdc++.h>
using namespace std;

int n,a,b;
struct cmp {
    bool operator()(const pair<int,int> &a, const pair<int,int> &b) const {
        return a.second < b.second;
    }
};

int main(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> arr;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> a >> b;
        arr.push({a,b});
    }
    while(!arr.empty()) {
        cout << arr.top().first << " " << arr.top().second << endl;
        arr.pop();
    }
    return 0;
}