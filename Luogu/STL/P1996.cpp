#include<bits/stdc++.h>
using namespace std;

int n,m;
queue<int> arr;

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) arr.push(i);
    while(!arr.empty()){
        for(int i = 1;i < m;i++){
            int x = arr.front();
            arr.pop();
            arr.push(x);
        }
        cout << arr.front();
        arr.pop();
        if(!arr.empty()) cout << " ";
    }
    return 0;
}