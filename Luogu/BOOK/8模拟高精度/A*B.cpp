#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a(5010);
vector<int> b(5010);
vector<int> c(5010);
string A,B;

int main(){
    cin >> A >> B;
    int lena = A.length();
    int lenb = B.length();
    for(int i = lena - 1,j = 1;i >= 0;j++,i--){
        a[j] = A[i] - '0';    
    }
    for(int i = lenb - 1,j = 1;i >= 0;j++,i--){
        b[j] = B[i] - '0';    
    }
    for(int i = 1;i <= lena;i++){
        for(int j = 1;j <= lenb;j++){
            c[i + j - 1] += a[i] * b[j];
        }
    }
    int len = lena + lenb;
    for(int i = 1;i <= len;i++){
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    while(!c[len]) len--;
    for(int i = max(1,len);i >= 1;i--) cout << c[i];
    return 0;
}