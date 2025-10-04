#include<bits/stdc++.h>
using namespace std;

int main(){

    queue<int> que;
    que.push(1);
    que.push(2);
    cout << que.front() << endl; //首
    cout << que.back() << endl; //尾
    que.pop();
    
    return 0;
}