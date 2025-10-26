#include <bits/stdc++.h>
using namespace std;

// 计算 log2 的和（暴力，O(n)）
double compute_ans(long long N) {
    double sum = 0;
    for (long long i = 1; i <= N; i++) {
        sum += log2(i);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 配置测试点大小
    vector<long long> testNs = {1000, 100000, 2000000, 4000000};

    for (size_t t = 0; t < testNs.size(); t++) {
        long long N = testNs[t];
        string inFile = "test" + to_string(t+1) + ".in";
        string outFile = "test" + to_string(t+1) + ".out";

        // 生成输入文件
        ofstream fin(inFile);
        fin << N << "\n";
        fin.close();

        // 计算答案
        double ans = compute_ans(N);

        // 生成输出文件
        ofstream fout(outFile);
        fout << fixed << setprecision(2) << ans << "\n";
        fout.close();

        cerr << "生成测试点 " << t+1 << ": N=" << N << " → " << inFile << " / " << outFile << "\n";
    }

    cerr << "所有测试点生成完成。\n";
    return 0;
}
