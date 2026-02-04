#include<iostream>
#include<vector>
using namespace std;

vector<int> a,b;

void insert(int l,int r,int c){
    b[l] += c;
    b[r + 1] -=c;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    a.resize(n+1);
    b.resize(n+1);
    
    for(int i = 1;i <= n;i++) cin >> a[i];

    for(int i = 1;i <= n;i++) insert(i,i,a[i]);

    while(m--){
        int l,r,c;cin >> l >> r >> c;
        insert(l,r,c);
    }
    //对差分数组求一次自己的前缀和
    for(int i = 1;i <= n;i++) b[i] += b[i - 1];
    
    for(int i = 1;i <= n;i++) cout << b[i] << " ";
    
    return 0;
}