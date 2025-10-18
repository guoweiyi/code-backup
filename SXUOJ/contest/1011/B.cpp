#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        string arr[3];
        for(int i = 0; i < 3; i++) cin >> arr[i];
        for(int i = 0; i < 3; i++) {
            bool hA = false, hB = false, hC = false;
            int Mark = 0;
            
            for (int j = 0; j < 3; j++) {
                if (arr[i][j] == 'A') hA = true;
                else if (arr[i][j] == 'B') hB = true;
                else if (arr[i][j] == 'C') hC = true;
                else if (arr[i][j] == '?') Mark++;
            }
            if (Mark != 0) {
                if (!hA) cout << 'A' << endl;
                else if (!hB) cout << 'B' << endl;
                else if (!hC) cout << 'C' << endl;
                break;
            }
        }
    }
    return 0;
}