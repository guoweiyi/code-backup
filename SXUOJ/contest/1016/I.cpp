#include<bits/stdc++.h>
using namespace std;

int t,n,x;
void slove(){
    cin >> n;
    int maxA = 0,minA = INT_MAX;
    for(int i = 1;i <= n;i++){
        cin >> x;
        minA = min(minA,x);
        maxA = max(maxA,x);
    }
    cout << maxA - minA << endl;
}
int main(){
    cin >> t;
	while (t--) {
        slove();
	}
    return 0;
} 