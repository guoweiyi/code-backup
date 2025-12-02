#include<vector>
#include<queue>
#include<iostream>
using namespace std;

vector<int> g,d;//g为图d为步数
int n,a,b;

void bfs(){
    queue<int> arr;
    arr.push(a);
    while(arr.size()){
        auto t = arr.front();
        arr.pop();
        
        int upa = t + g[t];
        int downa = t - g[t];

        if(upa < n && upa >= 0 && d[upa] == -1){//bug1 原写成d[t]
            d[upa] = d[t] + 1;//bug2 原写成加 g[t]
            arr.push(upa);
        }

        if(downa < n && downa >= 0 && d[downa] == -1){
            d[downa] = d[t] + 1;
            arr.push(downa);
        }
    }
}
int main(){
    cin >> n >> a >> b;
    g.resize(n);
    d.resize(n,-1);
    a--,b--;
    d[a] = 0;

    for(int i = 0;i < n;i++) cin >> g[i];

    bfs();
    cout << d[b];
    return 0;
}