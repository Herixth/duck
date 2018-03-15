#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main() {
	#ifdef DEBUG
	freopen("×Ö·û´®.txt", "r", stdin);
	#endif
	char sam[101] = { 0 };
	char wai[101][101] = { 0 };
	char mid[101] = { 0 };
	char buff[101] = { 0 };
	int op = 0, n = 0, len = 0, len2 = 0;
	scanf("%s", sam);
	len = strlen(sam);
	scanf("%d", &op);
	if (!op) 
		for (int i = 0; i < len; i ++) 
			if (sam[i] >= 'A' && sam[i] <= 'Z') sam[i] += 32;
	scanf("%d", &n);
	for (int i = 0; i < n; i ++) {
		scanf("%s", wai[i]);
		strcpy(mid, wai[i]);
		len2 = strlen(wai[i]);
		if (!op) 
		for (int j = 0; j < len2; j ++) 
			if (wai[i][j] >= 'A' && wai[i][j] <= 'Z') wai[i][j] += 32;
		for (int g = 0; g < len2; g ++) {
			if (wai[i][g] == sam[0]) {
				strncpy(buff, wai[i] + g, len);
				if (!strcmp(buff, sam)) {
					printf("%s\n", mid);
					break;
				}
			}
		}
	}
	
	
	return 0;
}
