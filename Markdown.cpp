#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int const maxn = 102;
char store[maxn][maxn];

void solve(char *Mid) {
	if (Mid[0] == '#') {
		int num = 0, j;
		for (j = 0; j < strlen(Mid); j ++)
			if (Mid[j] == '#') num ++;
			else break;
		for ( ; j < strlen(Mid); j ++)
			if (Mid[j] != ' ') break;
			 
		Mid[strlen(Mid) - 1] = '\0';
		printf("<h%d>", num);
		
		int count1 = 0, count2 = 0, qian[maxn], hou[maxn];
		char text[maxn] = { 0 };
		char link[maxn] = { 0 };
		int mark = j;
		char *p = strchr(Mid, '[') + 1;
		int flag1 = 0;
		if (p != NULL) {
			for (int i = mark; i < strlen(Mid); i ++) {
				if (Mid[i] == '[') qian[count1 ++] = i;
				if (Mid[i] == ')') hou[count2 ++] = i;
			}
			flag1 = 1;	
		}
		int loc = 0;
		int ss = 0, ss1 = 0;
		int count = 0;
		for (int i = mark; i < strlen(Mid); i ++) {
			
			if (!flag1) {
				if (Mid[i] == '_') {
					ss ? printf("</em>") : printf("<em>");
					ss = !ss;
				} else 
					printf("%c", Mid[i]);
			} else {
				if (loc < count1 && i >= qian[loc] && i <= hou[loc]) {
					i = hou[loc];
					int g;
					for (g = qian[loc] + 1; ; g ++) {
						if (Mid[g] == ']') break;
						text[count ++] = Mid[g];
					}
					count = 0;
					for (g = g + 2; g < hou[loc]; g ++) 
						link[count ++] = Mid[g];
						
					printf("<a href=\"%s\">", link);
					for (int h = 0; h < strlen(text); h ++)
						if (text[h] == '_') {
							ss1 ? printf("</em>") : printf("<em>");
							ss1 = !ss1;
						} else 
							printf("%c", text[h]);
					printf("</a>");
					loc ++;
					count = 0;
					memset(text, 0, maxn);
					memset(link, 0, maxn);
				} else {
					if (Mid[i] == '_') {
						ss ? printf("</em>") : printf("<em>");
						ss = !ss;
					} else 
						printf("%c", Mid[i]);
					
				}
				
			}
		}
		
		if (num > 6) num = 6;
		printf("</h%d>\n", num);
	}
	else {
		Mid[strlen(Mid) - 1] = '\0';
		int count1 = 0, count2 = 0, qian[maxn], hou[maxn];
		char text[maxn] = { 0 };
		char link[maxn] = { 0 };
		int mark = 0;
		for (mark = 0; mark < strlen(Mid); mark ++)
			if (Mid[mark] != ' ' && Mid[mark] != '*') 
				break;
		char *p = strchr(Mid, '[') + 1;
		int flag = 0;
		if (p != NULL) {
			for (int i = mark; i < strlen(Mid); i ++) {
				if (Mid[i] == '[') qian[count1 ++] = i;
				if (Mid[i] == ')') hou[count2 ++] = i;
			}
			flag = 1;	
		}
		int loc = 0;
		int ss = 0, ss1 = 0;
		int count = 0;
		for (int i = mark; i < strlen(Mid); i ++) {
			
			if (!flag) {
				if (Mid[i] == '_') {
					ss ? printf("</em>") : printf("<em>");
					ss = !ss;
				} else 
					printf("%c", Mid[i]);
			} else {
				if (loc < count1 && i >= qian[loc] && i <= hou[loc]) {
					i = hou[loc];
					int g;
					for (g = qian[loc] + 1; ; g ++) {
						if (Mid[g] == ']') break;
						text[count ++] = Mid[g];
					}
					count = 0;
					for (g = g + 2; g < hou[loc]; g ++) 
						link[count ++] = Mid[g];
						
					printf("<a href=\"%s\">", link);

					for (int h = 0; h < strlen(text); h ++)
						if (text[h] == '_') {
							ss1 ? printf("</em>") : printf("<em>");
							ss1 = !ss1;
						} else 
							printf("%c", text[h]);
					printf("</a>");
					loc ++;
					count = 0;
					memset(text, 0, maxn);
					memset(link, 0, maxn);
				} else {
					if (Mid[i] == '_') {
						ss ? printf("</em>") : printf("<em>");
						ss = !ss;
					} else 
						printf("%c", Mid[i]);
					
				}
				
			}
		}
	}
	return;
}

int main() {
	
	#ifdef DEBUG
	freopen("²âÊÔ.txt", "r", stdin);
	#endif
	char mid[maxn];
	int count = 0;
	int xian = 0;
	while (fgets(mid, sizeof(mid), stdin)) {
		if (strlen(mid) != 1) {
			xian = 0;
			strcpy(store[count ++], mid);
			continue;
		}
		else if (xian) continue;
		
		xian = 1;
		if (count == 1 && store[0][0] == '#') 
			solve(store[0]);
		else if (count >= 1 && store[0][0] == '*') {
			printf("<ul>\n");
			for (int i = 0; i < count; i ++){
				printf("<li>");
				solve(store[i]);
				printf("</li>\n");
			}
			printf("</ul>\n");		
		}
		else {
			printf("<p>");
			for (int i = 0; i < count; i ++) {
				solve(store[i]);
				i <= count - 2 ? printf("\n") : i = i;
			}
			printf("</p>\n");
		}										
		
			
		for (int i = 0; i < count; i ++)
			memset(store[i], 0, maxn);
		count = 0;
	}
	
	if (count == 1 && store[0][0] == '#') 
		solve(store[0]);
	else if (count >= 1 && store[0][0] == '*') {
		printf("<ul>\n");
		for (int i = 0; i < count; i ++){
			printf("<li>");
			solve(store[i]);
			printf("</li>\n");
		}
		printf("</ul>\n");		
	}
	else {
		printf("<p>");
		for (int i = 0; i < count; i ++) {
			solve(store[i]);
			i <= count - 2 ? printf("\n") : i = i;
		}
		printf("</p>\n");
	}
	return 0;
}
