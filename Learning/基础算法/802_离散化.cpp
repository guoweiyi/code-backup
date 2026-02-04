#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using PII = pair<int,int>;

int n,m;
int a[300010],s[300010];
vector<int> alls;
vector<PII> add,query;

int find(int x)
{
    int l = 0,r = alls.size() - 1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}

int main(){
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        int x,c;
        cin >> x >> c;
        add.push_back({x,c});
        alls.push_back(x);
    }
    for(int i = 0;i < m;i++){
        int l,r;
        cin >> l >> r;
        alls.push_back(l);
        alls.push_back(r);
        query.push_back({l,r});
    }
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());

    for(auto e : add){
        int x = find(e.first);
        a[x] += e.second;
    }
    for(int i = 1;i <= alls.size(); i++) s[i] = s[i - 1] + a[i];

    for(auto e : query){
        cout << s[find(e.second)] - s[find(e.first) - 1] << endl;
    }
    return 0;
}