#include <iostream>
#include <cstdlib>
using namespace std;

int datamap[26][30001];
int datalist[25][2];

void dp(int N, int m) {
	if (datalist[0][0] <= N) 
		datamap[1][N - datalist[0][0]] = datamap[0][N - datalist[0][0]] = datalist[0][0] * datalist[0][1];
	for (int row = 1; row < m; row ++) {
		for (int col = 0; col < N; col ++) {
			if (datamap[row][col]) {
				if (datalist[row][0] <= col && datalist[row][0] * datalist[row][1] + datamap[row][col] > datamap[row][col - datalist[row][0]])
					datamap[row + 1][col - datalist[row][0]] = datamap[row][col - datalist[row][0]] = datamap[row][col] + datalist[row][0] * datalist[row][1];
				else 
					datamap[row + 1][col] = datamap[row][col];
			}
		}
		if (datalist[row][0] <= N && datalist[row][0] * datalist[row][1] > datamap[row][N - datalist[row][0]])
			datamap[row + 1][N - datalist[row][0]] = datamap[row][N - datalist[row][0]] = datalist[row][0] * datalist[row][1];
	}
}

int main() {
	int N, m;
	cin >> N >> m;
	for (int i = 0; i < m; i ++)
		cin >> datalist[i][0] >> datalist[i][1];
	dp(N, m);
	int max = -1;
	for (int i = 0; i < N; i ++) if (max < datamap[m - 1][i]) max = datamap[m - 1][i];
	cout << max << endl;
	return 0;
}
