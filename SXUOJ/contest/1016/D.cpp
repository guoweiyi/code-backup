#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n,k,x;
vector<ll> arr;
vector<pair<int,int>> ops;

int main(){
    cin >> n >> k >> x;
    for(int i = 0;i < n;i++){
        int a; cin >> a;
        arr.push_back(a);
    }
    for(int i = 0;i < n;i++){
        if (arr[i] <= x){
            x += arr[i];
            continue;
        } 
        if(k <= 0){
            cout << -1;
            return 0;     
        }
        int best_j = -1;
        ll best_value = -1;
        for(int j = i + 1;j < n;j++){
            if(arr[j] <= x){
                if(arr[j] > best_value){
                    best_value = arr[j];
                    best_j = j;
                }
            }
        }
        if(best_j == -1){
            cout << -1;
            return 0;
        }
        swap(arr[i],arr[best_j]);
        ops.push_back({i + 1,best_j + 1});
        k--,i--;
    }
    cout << ops.size() << "\n";
    for (auto [u,v] : ops) cout << u << " " << v << endl;
    return 0;
}