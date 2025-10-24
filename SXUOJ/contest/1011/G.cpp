#include<bits/stdc++.h>
using namespace std;

int n,minA = __INT_MAX__;

int main(){
	cin >> n;
	vector<int> arr(n);
	for(int i = 0;i < n;++i) cin >> arr[i];

	sort(arr.begin(),arr.end());

	for(int i = 1;i < n;++i){
		minA = min(minA,arr[i] - arr[i - 1]);
	}
	cout << minA;
	return 0;
}