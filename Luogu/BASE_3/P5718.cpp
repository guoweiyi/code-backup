#include<bits/stdc++.h>
using namespace std;

priority_queue<int ,vector<int>,greater<int>> arr;
int n;

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
        int x;cin >> x;
        arr.push(x);
    }
    cout << arr.top();
    return 0;
}