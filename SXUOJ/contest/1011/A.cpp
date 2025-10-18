#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin >> n;
    while(n--){
        int a,b,c;
        cin >> a >> b >> c;
        if(a == b) cout << c << "\n";
        if(a == c) cout << b << "\n";
        if(b == c) cout << a << "\n";
    }
    return 0;
}