#include <iostream>
using namespace std;

int t,n,a[100010];

void solve(){
    cin>>n;
    long long ans=0;
	for(int i = 1;i <= n;i++) cin >> a[i],ans+=a[i];
	if(ans % n == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}
int main(){
	cin>>t;
	while(t--){
        solve();
    }
	return 0;
}