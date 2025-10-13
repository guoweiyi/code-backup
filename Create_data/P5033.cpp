#include <bits/stdc++.h>
using namespace std;

const int MAXA = 100000; // ai 的上界

// 生成一个随机数 [l,r]
inline int rnd(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(0));

    int n = 10000000; // 1e7
    ofstream fin("test.in");
    ofstream fout("test.out");

    // 生成输入
    fin << n << "\n";
    for (int i = 0; i < n; i++) {
        fin << rnd(1, MAXA) << (i + 1 == n ? '\n' : ' ');
    }
    fin.close();

    // -------------------
    // 下面直接用“双队列 Huffman”算答案，写到 test.out
    // -------------------

    // 重新读数据（避免内存太大直接存数组，可以一边生成一边统计频率）
    ifstream in("test.in");
    int dummy;
    in >> dummy; // 读掉 n

    vector<int> cnt(MAXA + 1, 0);
    for (int i = 0; i < n; i++) {
        int x; in >> x;
        cnt[x]++;
    }
    in.close();

    queue<long long> q1, q2;
    for (int v = 1; v <= MAXA; v++) {
        while (cnt[v]--) q1.push(v);
    }

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        long long a, b;

        // getMin(q1,q2)
        if ((q2.empty() || (!q1.empty() && q1.front() < q2.front()))) {
            a = q1.front(); q1.pop();
        } else {
            a = q2.front(); q2.pop();
        }
        if ((q2.empty() || (!q1.empty() && q1.front() < q2.front()))) {
            b = q1.front(); q1.pop();
        } else {
            b = q2.front(); q2.pop();
        }

        ans += a + b;
        q2.push(a + b);
    }

    fout << ans << "\n";
    fout.close();

    return 0;
}
