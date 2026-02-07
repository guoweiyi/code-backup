#include<bits/stdc++.h>
using namespace std;

int N, M;
string s;
priority_queue<int> lefta; //大顶堆
priority_queue<int,vector<int>,greater<int>> righta; //小顶堆bug1

void insert(int x){
    if(lefta.empty() || x <= lefta.top())  lefta.push(x); //bug2
    else righta.push(x);

    if(righta.size() > lefta.size()){
        lefta.push(righta.top());
        righta.pop();
    }
    else if(righta.size() + 1 < lefta.size()){//bug3
        righta.push(lefta.top());
        lefta.pop();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 0;i < N;i++){
        int x; cin >> x;
        insert(x);
    }
    cin >> M;
    while(M--){
        cin >> s;
        if(s == "add"){
            int x; cin >> x;
            insert(x);
        }
        else cout << lefta.top() << endl;
    }
    return 0;
}