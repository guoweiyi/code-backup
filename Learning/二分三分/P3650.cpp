#include<iostream>
#include<climits>
#include<vector>
using namespace std;

int n,l = INT_MAX,r = -1;
vector<int> a;

int find(int x){
    int ans = 0;
    for(int i = 0;i < n;i++){
        if(a[i] < x) ans+= (a[i] - x) * (a[i] - x);
        else if(a[i] > x + 17) ans += (a[i] - x - 17) * (a[i] - x - 17);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    a.resize(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        l = min(l,a[i]);
        r = max(r,a[i]);
    } 
    r-=17;
    while(l < r){
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if(find(mid1) < find(mid2)) r = mid2 - 1;
        else l = mid1 + 1;
    }
    cout << find(l);
    return 0;
}