#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int max_len = 101;

int main() {
	int ans[max_len] = { 0 };
	int m, n;
	cin >> m >> n;
	int len = 0;
	for (int inc = 1; inc <= n; inc ++) {
		int buff[max_len] = { 0 };
		for (int x = 0; x < inc; x ++) {
			buff[x] = m;
		}
		int r = 0, col = 0;
		for (col = 0; col < max(inc, len); col ++) {
			if (col < len) {
				int tmp = ans[col] + buff[col] + r;
				ans[col] = tmp % 10;
				r = tmp / 10;
			}
			else {
				ans[col] = (buff[col] + r) % 10;
				r = (buff[col] + r) / 10;
			}
		}
		if (r) ans[col] = r; 
		
		bool flag = true;
		for (int dec = max_len; dec >= 0; dec --) {
			if (!ans[dec] && flag) continue;
			if (ans[dec] && flag) {
				len = dec + 1;
				break;
			}
		}
//		cout << "num:" << inc << " ";
//		for (int dec = len - 1; dec >= 0; dec --) {
//			cout << ans[dec];
//		}
//		cout << endl;
	}
	
	for (int dec = len - 1; dec >= 0; dec --) {
		cout << ans[dec];
	}
	cout << endl;
	return 0;
}
