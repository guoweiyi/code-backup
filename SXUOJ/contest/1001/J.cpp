#include<bits/stdc++.h>
using namespace std;

int t;

int main(){
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        cout << n << endl;
        for(int i = 1;i < n;i++) cout << i << " ";
        cout << n << endl;
    }
    return 0;
}