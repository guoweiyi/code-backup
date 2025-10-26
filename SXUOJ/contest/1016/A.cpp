#include<bits/stdc++.h>
using namespace std;

long long a,b,mul,real_mul;

int main(){
    cin >> a >> b >> mul;
    real_mul = a * b;
    if(real_mul == mul){
        if(real_mul < INT_MIN || real_mul > INT_MAX){
            cout << "Yes";
        }
        else cout << "MAYBE";
    }
    else cout << "NO";
    return 0;
}