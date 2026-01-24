//dfs + 贪心剪枝
//已经证明在 Hack 数据下还是需要的记忆话搜索才可 AC
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

int n;
double x[20], y[20];
double d[20][20];// 预处理距离
double ans = 1e18;
bool vis[20]; 

double dist(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

// u: 当前所在的点编号
// cnt: 已经吃掉的奶酪数量
// sum: 当前走过的总距离
void dfs(int u, int cnt, double sum) {
    if (sum >= ans) return;
    if (cnt == n) {
        ans = min(ans, sum);
        return;
    }

    // 贪心优化
    // 将所有未访问的点，按照“离当前点 u 的距离”从小到大排序
    // 这样能先找到一个较优解，大大加强剪枝效果
    pair<double,int> next_moves[20];
    int k = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            next_moves[k++] = make_pair(d[u][i], i);
        }
    }

    sort(next_moves, next_moves + k);

    for (int i = 0; i < k; i++) {
        int v = next_moves[i].second;
        double dist_uv = next_moves[i].first;
        
        // 如果加上这一步已经超过最优解，后面的点更远，肯定也超过，直接剪枝（强力剪枝）
        if (sum + dist_uv >= ans) continue;

        vis[v] = true;
        dfs(v, cnt + 1, sum + dist_uv);
        vis[v] = false;
    }
}

int main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    x[0] = 0; y[0] = 0;

    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];

    //预处理
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            d[i][j] = dist(i, j);
        }
    }

    // 从第 0 点出发，已吃 0 个，距离 0
    dfs(0, 0, 0.0);
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}