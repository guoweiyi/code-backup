#include <iostream>
#include <vector>
using namespace std;

int table[5][5] = {
    {0, -1,  1,  1, -1},
    {1,  0, -1,  1, -1},
    {-1, 1,  0, -1,  1},
    {-1,-1,  1,  0,  1},
    {1,  1, -1, -1,  0}
};

int main() {
    int n, na, nb;
    cin >> n >> na >> nb;

    vector<int> A(na + 1), B(nb + 1);
    for (int i = 1; i <= na; i++) cin >> A[i];
    for (int i = 1; i <= nb; i++) cin >> B[i];

    int x = 1, y = 1;
    int ansA = 0, ansB = 0;

    while (n--) {
        int res = table[A[x]][B[y]];
        if (res == 1) ansA++;
        else if (res == -1) ansB++;

        x++; if (x > na) x = 1;
        y++; if (y > nb) y = 1;
    }

    cout << ansA << " " << ansB;
    return 0;
}
