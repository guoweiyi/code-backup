#include<bits/stdc++.h>
using namespace std;

vector<int> arrA;
vector<int> arrB;
int n,k;
int numA = 0,numB = 0,sumA = 0,sumB = 0;

int main(){
    cin >> n >> k;
    for(int i = 1;i <= n;i++){
        if(i%k == 0){
            arrA.push_back(i);
            numA++;
        } 
        else {
            arrB.push_back(i);
            numB++;
        }
    }
    for(int i = 0;i < numA;i++) sumA += arrA[i];
    for(int i = 0;i < numB;i++) sumB += arrB[i];
    cout << fixed << setprecision(1) << (numA ? (double)sumA/numA : 0.0) << " ";
    cout << fixed << setprecision(1) << (numB ? (double)sumB/numB : 0.0);
//    cout << fixed << setprecision(2) << sumA/numA << " ";
//    cout << fixed << setprecision(2) << sumB/numB;
    return 0;
}