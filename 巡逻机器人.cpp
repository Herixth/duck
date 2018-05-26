#include <iostream>
#include <cstring>
#define ILLEGAL x<0||x>=m||y<0||y>=n||show[x][y]
using namespace std;
const int maxn = 20;

void Show(int canvas[maxn][maxn], int m, int n, int len = 0) {
	for (int i = 0; i < m; i ++) {
		for (int j = 0; j < n; j ++)	
			cout << canvas[i][j] << " ";
		cout << endl;
	}
	if (len) cout << "Length: " << len << endl << endl;
}

void Copy(int last_show[maxn][maxn], int show[maxn][maxn], int &last_len, int &len, int m, int n) {
	for (int i = 0; i < m; i ++)
		for (int j = 0; j < n; j ++)
			last_show[i][j] = show[i][j];
	last_len = len;
}

void dfs(int pic[maxn][maxn], int show[maxn][maxn], int last_show[maxn][maxn], int m, int n, int &last_len, int len, int ls_block, int x, int y) {
	if (ILLEGAL) return;
	show[x][y] = 1;
	if (x == m - 1 && y == n - 1) {
		Show(show, m, n, len);
		if (len < last_len) 
			Copy(last_show, show, last_len, len, m, n);
	}
	if (!ls_block || !pic[x + 1][y])
		dfs(pic, show, last_show, m, n, last_len, len + 1, pic[x + 1][y], x + 1, y);
	if (!ls_block || !pic[x - 1][y])
		dfs(pic, show, last_show, m, n, last_len, len + 1, pic[x - 1][y], x - 1, y);
	if (!ls_block || !pic[x][y + 1])
		dfs(pic, show, last_show, m, n, last_len, len + 1, pic[x][y + 1], x, y + 1);
	if (!ls_block || !pic[x][y - 1])
		dfs(pic, show, last_show, m, n, last_len, len + 1, pic[x][y - 1], x, y - 1);
	show[x][y] = 0;
} 

int main() {
	int pic[maxn][maxn] = { 0 };
	int show[maxn][maxn] = { 0 };
	int last_show[maxn][maxn] = { 0 };
	int m = 4, n = 6;
//	cin >> m >> n;
	pic[0][1] = pic[0][2] = pic[1][2] = pic[1][4] = pic[1][5] = 1;
	pic[2][1] = pic[2][2] = pic[2][3] = pic[2][4] = pic[3][1] = pic[3][2] = pic[3][3] = 1;
	
//	for (int i = 0; i < m; i ++)
//		for (int j = 0; j < n; j ++)
//			cin >> pic[i][j];
	cout << endl;
	int len = 0, last_len = maxn * maxn * maxn;
	dfs(pic, show, last_show, m, n, last_len, len, pic[0][0], 0, 0);
	cout << "the minlen is: " << last_len << endl;
	return 0;
}
