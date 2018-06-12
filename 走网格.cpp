#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 20;
int node[maxn][maxn];
int x, y;

void move() {
	node[0][0] = 1;
	for (int i = 0; i <= x; i ++)
		for (int j = 0; j <= y; j ++) {
			node[i][j] += j > 0 ? node[i][j - 1] : 0;
			node[i][j] += i > 0 ? node[i - 1][j] : 0;
		}
		
	cout << node[x][y] << endl;
}

int main() {
	cin >> x >> y;
	move();
	return 0;
}
