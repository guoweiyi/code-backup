// 10minAC  WA*0 
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
#define ll long long

int n;
ll ans = 1;

int main() {
    cin >> n;
    for(int i = 1;i <= n;i++){
        int x,y;
        cin >> x >> y;
        ans *= y - x + 1;
    }
    if(ans <= 1e5) cout << "NO TLE";
    else if(ans > 1e5 && ans <= 1e7) cout << "POSSIBLE";
    else cout << "TLE";
    return 0;
}
