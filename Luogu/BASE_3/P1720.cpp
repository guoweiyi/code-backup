#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin >> n;
    long double f = (pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5);
    cout << fixed << setprecision(2) << f;
    return 0;
}