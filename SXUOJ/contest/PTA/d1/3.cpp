#include<iostream>
#include<vector>
using namespace std;
int n;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= 4;j++){
            string s;cin >> s;
            if(s[2] == 'T') cout << (s[0] - 'A' + 1);;
        }
    }
    return 0;
}