#include<bits/stdc++.h>
using namespace std;

int N, M, x;
vector<int> arr;

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> x;
        arr.push_back(x);
    }
    cin >> M;
    string buf;
    while(M--){
        cin >> buf;
        if(buf == "add"){
            cin >> x;
            arr.push_back(x);
        }
        else{
            sort(arr.begin(), arr.end());
            int l = arr.size();
            cout << arr[(l-1) / 2] << endl;  
        }
    }
    return 0;
}