#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn = 351;
int data[maxn][maxn] = { 0 };

int cmp(void const *a, void const *b) {
	return *(int *)b - *(int *)a;
}

void D_p(int n) {
	for (int row = 1; row < n; row ++) {
		for (int col = 0; col <= row; col ++) {
			if (col - 1 >= 0) data[row][col] += max(data[row - 1][col - 1], data[row - 1][col]);
			else data[row][col] += data[row - 1][col];
		}
	}
	qsort(data[n - 1], n, sizeof(int), cmp);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j <= i; j ++)	
			cin >> data[i][j];
	D_p(n);
	cout << data[n - 1][0] << endl;
	return 0;
}
