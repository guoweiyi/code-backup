#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char c[N];
int n,cnt[256] = {0};
priority_queue<int, vector<int>,greater<int>> maina;

int main(){
    scanf("%d",&n);
    getchar(); // 去换行
    cin.getline(c, n + 1); 
    for(int i = 0;i < n;i++) cnt[(unsigned char)c[i]]++;
    maina.push(cnt['c']);
    maina.push(cnt['i']);
    maina.push(cnt['a']);
    maina.push(cnt['l'] / 2);
    maina.push(cnt['o']);
    cout << maina.top();
    return 0;
}