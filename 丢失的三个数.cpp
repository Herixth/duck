#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;
const int maxn = 10001;
int tem[maxn];

int cmp (const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int aa(int a) {
	int s = 0;
	while (a) {
		s ++;
		a /= 10;
	}
	return s;
}

int main() {
	for (int i = 1; i < maxn; i ++)
		tem[i] = i;
	int num;
	for (int j = 1; j < maxn - 3; j ++) {
		cin >> num;
		tem[num] = 0;
	}
	int ans[3];
	int count = 0;
	for (int g = 1; g < maxn; g ++)
		if (tem[g]) ans[count ++] = g;
	char hum[3][300] = { 0 };
//	for (int i = 0; i < 3; i ++)
//		itoa(ans[i], hum[i], 10);
	qsort(ans, 3, sizeof(int), cmp);
	long long aaa = ans[0] * pow(10, aa(ans[1]) + aa(ans[2])) + ans[1] * pow(10, aa(ans[2])) + ans[2];
	aaa %= 7;
	cout << aaa << endl;
	return 0;
}
