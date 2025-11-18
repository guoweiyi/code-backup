#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a(520);
vector<int> b(520);
vector<int> c(520);
string A,B;

int main(){
    cin >> A >> B;
    int len = max(A.length(),B.length());
    for(int i = A.length() - 1,j = 1;i >= 0;j++,i--){
        a[j] = A[i] - '0';    
    }
    for(int i = B.length() - 1,j = 1;i >= 0;j++,i--){
        b[j] = B[i] - '0';    
    }
    for(int i = 1;i <= len;i++){
        c[i] += a[i] + b[i];
        c[i + 1] = c[i] / 10;
        c[i] %= 10;
    }
    if(c[len + 1]) len++;
    for(int i = len;i >= 1;i--) cout << c[i];
    return 0;
}