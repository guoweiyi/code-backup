#include<bits/stdc++.h>
using namespace std;

int t,n,x;

#define rd read()
inline long long read()
{
    long long x = 0, y = 1;
    char c = getchar();
    while (c > '9' || c < '0')
    {
        if (c == '-')
            y = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * y;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    t = rd;
    for(int i = 1; i <= t; i++){
        n = rd;
        x = rd;
        
        vector<int> arr(n);
        vector<int> result;
        for(int j = 0; j < n; j++){
            arr[j] = rd;
        }
        
        for(int j = 0; j < n; j++){
            if(arr[j] % x == 0){
                result.push_back(j + 1); 
            }
        }
        
        if(result.empty()) cout << -1 << endl;
        else {
            for(int j = 0; j < result.size(); j++){
                if(j > 0) cout << " ";
                cout << result[j];
            }
            cout << endl;
        }
    }
    return 0;
}