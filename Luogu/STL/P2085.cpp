#include<bits/stdc++.h>
using namespace std;

set<int> arr;
int n, m;

int getans(int a,int b,int c){
    int x =  b / (2*a);
    return a*pow(-x,2) + b*(-x) + c;
}

int main(){
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        int a,b,c;
        cin >> a >> b >> c;
        cout << getans(a,b,c) << endl;
    }
    return 0;
}