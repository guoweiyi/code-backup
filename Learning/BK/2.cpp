#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
#define ll long long

//过河卒P1002 不考虑马

int main() {
    int x,y;
    cin >> x >> y;
    for(int i = 0;i < x;i++){
        mat[i][1] = 1;
    }
    for(int i = 0;i < y;i++){
        mat[1][i] = 1;
    }
    cout << f4(x,y);
    return 0;
}
