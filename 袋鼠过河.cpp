#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
using namespace std;

int main() {
	int n;
	cin >> n;
	int num[10001] = { 0 };
	int record[10001] = { 0 };
	for (int i = 0; i < n; i ++)
		cin >> num[i];
//	vector<int> record(n, 0);
	record[0] = 1;
	for (int i = 1; i <= n; i ++) {
		int ss = 0, flag = 0;
//		if (!num[i]) continue;
		for (int j = i - 1; j >= 0; j --) {
			if (!num[j]) continue;
			if (num[j] + j >= i) {
				if (!flag) {
					ss = record[j];
					record[i] = ss + 1;
					flag = 1;
				}
				if (record[j] < ss) {
					record[i] = record[j] + 1;
					ss = record[j];
				} 
			}
		}
	}
//	for (int i = 0; i <= n; i ++)
//		cout << record[i] << " ";
//	cout << endl;
	cout << (record[n] - 1 ? record[n] - 1: -1) << endl;
	return 0;
}
