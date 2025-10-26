#include<bits/stdc++.h>
using namespace std;

int t;
vector<int> a(3);

int main(){
    cin >> t;
	while (t--) {
		cin >> a[0] >> a[1] >> a[2];
        sort(a.begin(), a.end());
		cout << a[2] - a[0] << endl;
	}
    return 0;
} 