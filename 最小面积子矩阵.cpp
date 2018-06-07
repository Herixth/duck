#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;
const int maxn = 100;

int main() {
	int m = 0, n = 0, k = 0;
	cin >> m >> n >> k;
	int data[maxn][maxn] = { 0 };
	int ans = 10000000;
	for (int row = 0; row < m; row ++) {
		for (int col = 0; col < n; col ++) {
			cin >> data[row][col];
		
	        for (int row_loc = 0; row_loc <= row; row_loc ++) {
	        	for (int col_loc = 0; col_loc <= col; col_loc ++) {
	        		int record = 0;
	        		for (int loc_r = row_loc; loc_r <= row; loc_r ++) {
	        			for (int loc_c = col_loc; loc_c <= col; loc_c ++) {
	        				record += data[loc_r][loc_c];
						}
					}
					if (record >= k && (row - row_loc + 1) * (col - col_loc + 1) < ans) {
						ans = (row - row_loc + 1) * (col - col_loc + 1);
					}
				}
			}
		}
	}
	
	if (ans == 10000000) {
		cout << -1 << endl;
	}
	else {
		cout << ans << endl;
	}
	return 0;
}
