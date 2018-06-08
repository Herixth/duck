#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1E5 + 1;

int data[maxn];
int record[maxn];

void Dp(int n) {
	record[0] = 1;
	for (int i = 1; i < n; i ++) {
		for (int j = i - 1; j >= 0; j --) 
			if (data[i] > data[j] && record[j] + 1 > record[i])
				record[i] = record[j] + 1;
	}
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++)
		cin >> data[i];
	Dp(n);
	sort(record, record + n, cmp);
	cout << record[0] << endl;
	return 0;
}
