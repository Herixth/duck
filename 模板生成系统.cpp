#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main() {
	#ifdef DEBUG
	freopen("Ä£°å.txt", "r", stdin);
	#endif
	char buff[110], *mid;
	char mod[110][110] = { 0 };
	char name[110][110] = { 0 };
	char vale[110][110] = { 0 };
	int count = 0;
	char ss[110];
	int m, n;
	scanf("%d %d\n", &m, &n);
	for (int j = 0; j < m; j ++)
		fgets(mod[j], sizeof(mod[j]), stdin);
	for (int j = 0; j < n; j ++) {
		scanf("%s", name[j]);
		fgets(vale[j], 110, stdin);
		vale[j][strlen(vale[j]) - 2] = '\0';
	}
	for (int i = 0; i < m; i ++) {
		count = 0;
		int flag = 1;
		for (int j = 0; j < strlen(mod[i]); j ++) {
			if (mod[i][j] == '{' && flag && mod[i][j + 1] == '{') {
				j ++;
				count += 2;
				flag = 0;
			}
			if (mod[i][j] == '}' && !flag && mod[i][j + 1] == '}') flag = 1; 
		}
		mid = mod[i];
		count /= 2;
		for (int g = 0; g < count; g ++) {
			memset(ss, 0, sizeof(ss));
			memset(buff, 0, sizeof(buff));
			sscanf(mid, "%[^{]", buff);
			for (int gg = 0; ; gg ++)
				if ((mid + strlen(buff) + 3)[gg] == ' ') break;
				else ss[gg] = (mid + strlen(buff) + 3)[gg];
			printf("%s", buff);
			int loc = 0;
			for (int ff = 0; ff < strlen(ss); ff ++)
				if (ss[ff] == '}') loc ++;
			while (loc --) mid = strchr(mid, '}') + 1;
			mid = strchr(mid, '}') + 2;
			for (int f = 0; f < n; f ++) 
				if (!strcmp(ss, name[f])) {
					printf("%s", vale[f] + 2);
					break;
				}
		}
		if (!count)
		printf("%s", mod[i]);
		else printf("%s", mid);
	}
	
	return 0;
}
