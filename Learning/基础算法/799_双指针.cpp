#include<vector>
#include<iostream>
using namespace std;
const int N = 100010;
int count[N];
vector<int> a;
int maxA = -1;

int main(){
    int n;cin >> n;
    a.resize(n + 1);
    for(int i = 0;i < n;i++) cin >> a[i];

    for(int i = 0,j = 0;i < n;i++){
        count[a[i]]++;
        while(count[a[i]] > 1){
            count[a[j]]--;
            j++;
        }
        maxA = max(maxA,i - j + 1);
    }
    cout << maxA;
    return 0;
}