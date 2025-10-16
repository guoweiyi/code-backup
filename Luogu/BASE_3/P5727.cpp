#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int arr[100010];
    arr[0] = n;
    int j = 0;
    while(n!=1){
        j++;
        if(n % 2 == 1) n = n*3 + 1;
        else n /= 2;
        arr[j] = n;
    }
    for(int i = j ; i > 0;i--) cout << arr[i] << " ";
    cout << arr[0];
    return 0;
}