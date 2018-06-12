//#include<iostream>
//#include<cstdio>
//#include<cmath>
//#include<cstdlib>
//using namespace std;
//
//bool is_angle(int x, int y, int z) {
//	return (x + y <= z || x + z <= y);
//}
//
//int cmp(const void *a, const void *b) {
//	return *(int *)a - *(int *)b;
//}
//
//int main() {
//	int a[3];
//	while (scanf("%d,%d,%d", &a[0], &a[1], &a[2])) {
//		if (is_angle(a[0], a[1], a[2])) {
//			cout << "illegal" << endl;
//			continue;
//		}
//		qsort(a, 3, sizeof(int), cmp);
//		double k = hypot(a[0], a[1]);
//		if (k > a[2]) cout << "acute" << endl;
//		if (k == a[2]) cout << "right" << endl;
//		if (k < a[2]) cout << "obtuse" << endl;
//	}
//}

#include<stdio.h>
#include<math.h>

int main() {
	double k;
	int a[3] = {0};
	while(scanf("%d,%d,%d", &a[0], &a[1], &a[2]) != EOF) {
		
		if ((a[0] + a[1] <= a[2]) || (a[0] + a[2] <= a[1])) {
			printf("illegal\n");
			continue;
		}
		for (int i = 0; i < 2; i ++)
			for (int j = i + 1; j < 3; j ++)
				if (a[i] > a[j])
					a[i] ^= a[j] ^= a[i] ^= a[j];
		k = sqrt(a[0] * a[0] + a[1] * a[1]);
		if (k == a[2]) printf("right\n");
		if (k < a[2]) printf("obtuse\n");
		if (k > a[2]) printf("acute\n");
	}
}
