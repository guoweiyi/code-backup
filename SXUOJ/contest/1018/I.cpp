#include<iostream>
using namespace std;

int n,x,ans = 0;
bool ok = 0;
int main(){
    cin >> n >> x;
    while(x > 0){
        int a = n / 2;
        int b = n - (n / 2);
        if(!ok && a % 2 == 1 && b % 2 == 1) a--,b++;
        x-=a,n-=a;
        ans++,ok = 1;
    }
    cout << ans;
    return 0;
}