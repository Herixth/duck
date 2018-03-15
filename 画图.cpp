#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
const int maxn = 101;
char canvas[maxn][maxn]; //列  行 

int traver(int m, int n, char ch) {
	int flag = 0;
	for (int row = 0; row < n; row ++) {
		for (int col = 0; col < m; col ++) {
			if (canvas[row][col] == '|' || canvas[row][col] == '-' || canvas[row][col] == '+' || canvas[row][col] == ch) continue;
			if ((row - 1 >= 0 && canvas[row - 1][col] == ch) || (row + 1 < n && canvas[row + 1][col] == ch)
			|| (col - 1 >= 0 && canvas[row][col - 1] == ch) || (col + 1 < m && canvas[row][col + 1] == ch)) {
				flag = 1;
				canvas[row][col] = ch;
			}
		}
	}
	return flag;
}

void line(int m, int n) {
	int x1, y1, x2, y2;
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

	if (x1 == x2) {
		if(y1 > y2) {
			y1 ^= y2 ^= y1 ^= y2;
		}
		for (int i = y1; i <= y2; i ++) {
			if (canvas[i][x1] == '-' || canvas[i][x1] == '+') 
				canvas[i][x1] = '+';
			else 
				canvas[i][x1] = '|';
		} 
	}
	else {
		if(x1 > x2) {
			x1 ^= x2 ^= x1 ^= x2;
		}
		for (int i = x1; i <= x2; i ++) {
			if (canvas[y1][i] == '|' || canvas[y1][i] == '+') 
				canvas[y1][i] = '+';
			else
				canvas[y1][i] = '-';
		}
	}
}

void photo(int m, int n) {
	int x, y, al;
	int row, col;
	scanf("%d %d %c", &x, &y, &al);
	
	
	for (col = x; col < m; col ++) {
		if (canvas[y][col] == '-' || canvas[y][col] == '|' || canvas[y][col] == '+') break;
		canvas[y][col] = al;
	}
	for (col = x; col >= 0; col --) {
		if (canvas[y][col] == '-' || canvas[y][col] == '|' || canvas[y][col] == '+') break;
		canvas[y][col] = al;
	}
	for (row = y; row < n; row ++) {
		if (canvas[row][x] == '-' || canvas[row][x] == '|' || canvas[row][x] == '+') break;
		canvas[row][x] = al;
	}
	for (row = y; row >= 0; row --) {
		if (canvas[row][x] == '-' || canvas[row][x] == '|' || canvas[row][x] == '+') break;
		canvas[row][x] = al;
	}
	int flag = 1;
	while (flag) {
		flag = traver(m, n, al);
	}
}
int main() {
	int m, n, q;
	scanf("%d%d%d", &m, &n, &q);   //n行 m列 
	
	for (int i = 0; i < n; i ++)
		memset(canvas[i], '.', m);
	
	while (q --) {
		int op;
		scanf("%d", &op);
		if (op) 
			photo(m, n);
		else
			line(m, n);
		
	}
	for (int row = n - 1; row >= 0; row --) 
		printf("%s\n", canvas[row]);
	
	return 0;
}
