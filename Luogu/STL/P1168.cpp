#include <bits/stdc++.h>
using namespace std;

priority_queue<int> lefta; // 大根堆
priority_queue<int, vector<int>, greater<int>> righta; // 小根堆
int N;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    N = rd;
    for(int i = 0; i < N; i++) {
        int x = rd;

        if(lefta.empty() || x <= lefta.top()) lefta.push(x);
        else righta.push(x);

        // 保持 lefta 堆大小 >= righta 堆大小，且 lefta 堆最多比 righta 多 1 个
        if(lefta.size() < righta.size()) {
            lefta.push(righta.top());
            righta.pop();
        } else if(lefta.size() > righta.size() + 1) {
            righta.push(lefta.top());
            lefta.pop();
        }

        if(i % 2 == 0) { 
            cout << lefta.top() << endl;
        }
    }
    
    return 0;
}
