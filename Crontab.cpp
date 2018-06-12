#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>

char store[100], buff[100], *mid;
int border[5][2]; //year  month  day  hour  min
int min_c[21][60], hour_c[21][24], day_c[21][31], month_c[21][12], week_c[21][7];
char command[21][100];
int pum[100];
int aaa;

void fetch_f(int &year, int &month, int &day, int &hour, int &min) {
	int list_thin[5] = { 0 };
	int list_num[5][2] = {0, 4, 4, 2, 6, 2, 8, 2, 10, 2};
	for (int i = 0; i < 5; i ++) {
		strncpy(buff, store + list_num[i][0], list_num[i][1]);
		list_thin[i] = atoi(buff);
		memset(buff, 0, sizeof(buff));
	}
	year = list_thin[0], month = list_thin[1], day = list_thin[2], hour = list_thin[3], min = list_thin[4];
}

void fire(int count) {
	switch (count) {
		case 0:	for (int i = 0; i < aaa; i ++) min_c[count][i] = pum[i]; min_c[count][aaa] = -2; return;
		case 1:	for (int i = 0; i < aaa; i ++) hour_c[count][i] = pum[i]; hour_c[count][aaa] = -2; return;
		case 2: for (int i = 0; i < aaa; i ++) day_c[count][i] = pum[i]; day_c[count][aaa] = -2;return;
		case 3: for (int i = 0; i < aaa; i ++) month_c[count][i] = pum[i]; month_c[count][aaa] = -2;return;
		case 4: for (int i = 0; i < aaa; i ++) week_c[count][i] = pum[i]; week_c[count][aaa] = -2;return;
	}
}

void change() {
	for (int i = 0; i < strlen(buff); i ++)
		if (buff[i] >= 'A' && buff[i] <= 'Z')	buff[i] += 32;
}

void single_op(int flag, int count) {
	char list_mon[12][4] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "nov", "dec"};
	char list_week[7][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
	int last = 0, begin = 0;
	if (store[0] >= 'a' && store[0] <= 'z') {
		for (int i = 0; ; i ++)
			if (count == 3) {
				if (strcmp(list_mon[i], store)) {
					pum[aaa ++] = i + 1; begin = i + 1; break;
				}
			} else {
				if (strcmp(list_week[i], store)) {
					pum[aaa ++] = i; begin = i + 1; break;
				}
			} 
	} else begin = atoi(store); 
	if (flag) {
		if (mid[0] >= 'a' && mid[0] <= 'z') {
			for (int i = 0; ; i ++)
				if (count == 3) {
					if (strcmp(list_mon[i], mid)) {
						last = i + 1; break;
					}
				} else {
					if (strcmp(list_week[i], mid)) {
						last = i; break;
					}
				} 
		} else last = atoi(mid);
		for (int g = begin + 1; g <= last; g ++) 
			pum[aaa ++] = g;	
	} else pum[aaa ++] = atoi(store);
	memset(store, 0, sizeof(store));
	memset(buff, 0, sizeof(buff));
}

void row_op(int count) {
	int flag = 0;
	change();
	for (int i = 0; i < strlen(buff); i ++)
		if (buff[i] == '-') {
			flag = 1;
			break;
		}
	strcpy(store, buff);
	if (flag) {
		sscanf(buff, "%[^-]", store);
		mid = strchr(buff, '-') + 1;
	} 
	single_op(flag, count);
}

void command_input(int line, int count, char *str) {
	if (count == 5) {	scanf("%s", command[line]);	return;}
//	memset(mid, 0, sizeof(mid));
	char *Mid;
	strcpy(Mid, str);
	int num = 0;
	aaa = 0;
	memset(pum, 0, sizeof(pum));
//	scanf("%s", Mid);
	if (Mid[0] == '*') {
		pum[aaa ++] = -1;
		fire(count);
		return;
	}
	for (int i = 0; i < strlen(Mid); i ++)
		if (Mid[i] == ',') num ++;
		for (int i = 0; i < num; i ++) {
			sscanf(Mid, "%[^,]", buff);
			row_op(count);
			Mid = strchr(Mid, ',') + 1;
		}
		strcpy(buff, Mid);
		row_op(count);
	fire(count);
}

int main() {
	#ifdef DEBUG
	freopen("1.txt", "r", stdin);
	#endif
	int n;
	
	char *str, *btr, sss[100];
	scanf("%d", &n);
	for (int i = 0; i < 2; i ++) {
		i ? scanf("%s\n", store) : scanf("%s", store);
		fetch_f(border[0][i], border[1][i], border[2][i], border[3][i], border[4][i]);
	}
	for (int line = 0; line < n; line ++) {
		fgets(sss, 100, stdin);
		sss[strlen(sss) - 1] = '\0';
		btr = sss;
		for (int count = 0; count < 5; count ++) {
			strcpy(sss, btr);
			btr = strchr(btr, ' ') + 1;
			sscanf(sss, "%[^ ]", sss);
			command_input(line, count, sss);
		}
		command_input(line, 5, btr);
	}
	

	for (int i = 0; ; i ++) {
		if (month_c[0][i] == -2) break;
		printf("%d ", month_c[0][i]);
	}
	printf("\n");
	
	return 0;
}
