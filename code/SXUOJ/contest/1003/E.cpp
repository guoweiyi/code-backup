#include<bits/stdc++.h>
using namespace std;

int get_unique_count(int a[], int n) {
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(a[i]);
    }
    return s.size();
}

int main(){
    int n,q[1010];
    scanf("%d",&n);
    for(int i = 0;i < n;i++) scanf("%d",&q[i]);
    int ans = get_unique_count(q,n);
    printf("%d",ans);
    return 0;
}