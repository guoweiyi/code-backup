#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	float ans = 0, maxNum = -1, minNum = 100;
	int p = n;
	while (n--) {
		float x;
		cin >> x;
		ans += x;
		maxNum = max(x, maxNum), minNum = min(x, minNum);
	}
// printf("%.2f", (ans - maxNum - minNum) / (p - 2.0));
// cout << fixed << setprecision(2) << (ans - maxNum - minNum) / (p - 2.0); //小数后两位
    cout << setprecision(3) << (ans - maxNum - minNum) / (p - 2.0);//有效数字三位
	return 0;
}
