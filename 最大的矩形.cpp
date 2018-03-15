#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>

void sear(int h[1001], int &loc_f, int &loc_l, int n, int line) {
	loc_l = loc_f;
	for ( ; loc_l < n; loc_l ++) if (h[loc_l] < line) break;
}

bool check(int h[1001], int &loc_f, int n, int line, int loc_l) {
	loc_f = loc_l;
	for ( ; loc_f < n; loc_f ++)
		if (h[loc_f] >= line) return true;
	return false;
}

int main() {
	int min_lin = 10000, high = 0;
	int n, h[1001];
	scanf("%d", &n);
	for (int i = 0; i < n; i ++) {
		scanf("%d", &h[i]);
		if (min_lin >= h[i]) min_lin = h[i];
		if (high < h[i]) high = h[i];
	}
	
	long long maxone = min_lin * n;
	int loc_f = 0, loc_l = 0;
	for (int line = min_lin + 1; line <= high; line ++) {
		int flag = 1;
		loc_f = 0, loc_l = 0;
		while (flag) {
			flag = check(h, loc_f, n, line, loc_l);
			if (flag) {
				sear(h, loc_f, loc_l, n, line);
				if (maxone < line * (loc_l - loc_f)) maxone = line * (loc_l - loc_f);
			}
		}
	}
	printf("%lld\n", maxone);
	return 0;
}
