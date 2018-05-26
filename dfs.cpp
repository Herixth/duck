#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 5;
int data[maxn][maxn];
int max_vale = 0;

void dfs(int row, int col, int list[maxn], int record) {
	if (col == maxn) {
		cout << "路径: ";
		for (int i = 0; i < maxn; i ++) 
			cout << list[i] << " ";
		cout << endl << "当前总值: " << record;
		if (record > max_vale) {
			max_vale = record;
			cout << " get√";
		}
		cout << endl << endl;
		return;
	}
	if (!col) 
	for (row = 0; row < maxn; row ++) {
		list[col] = row;
		if (row > 0)
			dfs(row - 1, col + 1, list, record + data[row][col]);
			
		dfs(row, col + 1, list, record + data[row][col]);
		
		if (row + 1 < maxn)
			dfs(row + 1, col + 1, list, record + data[row][col]);
	} 
	else {
		list[col] = row;
		if (row > 0)
			dfs(row - 1, col + 1, list, record + data[row][col]);
			
		dfs(row, col + 1, list, record + data[row][col]);
		
		if (row + 1 < maxn)
			dfs(row + 1, col + 1, list, record + data[row][col]);
	}
	return;
}

int main() {
	#ifdef DEBUG
	freopen("tt.txt", "r", stdin);
	#endif
	for (int i = 0; i < maxn; i ++)
		for (int j = 0; j < maxn; j ++)
			cin >> data[i][j];
	int list[maxn] = { 0 };
	dfs(0, 0, list, 0);
	cout << "最大: " << max_vale;
	return 0;
}
