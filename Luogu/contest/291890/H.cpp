#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    int n,r;cin >> n;
    vector<int> p(n);
    iota(p.begin(),p.end(),1);
    do{
        for(int i = 0; i < n;i++) cout << p[i] << (i == n - 1 ? "" : " ");
        cout << endl;
        cin >> r;
        if(r) return 0;
    } while(next_permutation(p.begin(), p.end()));
    return 0;
}