//尽量使用碰撞
#include<iostream>
#include<vector>
using namespace std; 

vector<int> a,b;
int n,m,x;

int main(){
    cin >> n >> m >> x;
    a.resize(n + 1);
    b.resize(m + 1);
    for(int i = 0;i < n;i++) cin >> a[i];
    for(int i = 0;i < m;i++) cin >> b[i];
    
    for(int i = 0,j = m - 1;i < n;i++)
    {
       while(j >= 0 && a[i] + b[j] > x) j--;
       if(a[i] + b[j] == x){
            cout << i << " " << j;
            return 0;
       }
    }
    
    return 0;
}