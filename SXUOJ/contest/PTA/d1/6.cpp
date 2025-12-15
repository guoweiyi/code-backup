#include<iostream>
using namespace std;
int main(){
    int T;cin >> T;
    int t = 0;
    int td = 0,rd = 0;
    while(t < T){
        int runtime = min(10,T - t);
        rd += runtime * 9;
        td += runtime * 3;
        t += runtime;
        if(t == T) break;
        if(rd > td){
            int rest = min(30,T - t);
            td += rest * 3;
            t += rest;
        }
    }
    if(td > rd) cout << "@_@ " << td;
    else if(td < rd) cout << "^_^ " << rd;
    else cout << "-_- " << td;
    return 0;
}