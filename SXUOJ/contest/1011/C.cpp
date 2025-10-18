#include<bits/stdc++.h>
using namespace std;

int t;

int main(){
    cin >> t;
    int n,a,b;
    while(t--){
        cin >> n >> a >> b;
        if(n%2 == 0){
            if((a*n) > (n/2) * b) cout << (n/2) * b << "\n";
            else cout << a*n << "\n";
        }
        else {
            if((a*n) > ((n/2)) * b + a) cout << ((n/2)) * b + a << "\n";
            else cout << a*n << "\n";
        }
    }
    return 0;
}