#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>

int infor_f[8][2], infor_s[8][2];  //随从攻击力及生命
int boss[2] = {30, 30};          //boss 1 2生命 
int next_f[8], next_s[8];
int num_f, num_s;

int check() {
	if (boss[0] <= 0 && boss[1]) { printf("-1\n"); return -1;}
	if (boss[0] && boss[1] <= 0) { printf("1\n"); return 1;}
	if (boss[0] && boss[1]) return 0;
}

void out() {
	if (!check()) printf("0\n");
	printf("%d\n%d", boss[0], num_f);
	for (int i = next_f[0]; i != 0; i = next_f[i]) 
		printf(" %d", infor_f[i][1]);
	printf("\n%d\n%d", boss[1], num_s);
	for (int j = next_s[0]; j != 0; j = next_s[j])
		printf(" %d", infor_s[j][1]);
	printf("\n");
}

void summon(int flag) {
	int pos = 0, atta = 0, heal = 0;
	scanf("%d %d %d", &pos, &atta, &heal);
	flag ? num_s ++ : num_f ++;
	if (flag) { infor_s[num_s][0] = atta, infor_s[num_s][1] = heal;} 
	else { infor_f[num_f][0] = atta, infor_f[num_f][1] = heal;}
	if ((!flag && num_f == pos) || (flag && num_s == pos)) {
		if (flag) { next_s[num_s - 1] = pos;}
		else { next_f[num_f - 1] = pos;}
	} else {
		int loc = 0, count = 0;
		if (flag) { 
			for (int j = 0, count = 0; count < pos - 1; j = next_s[j], count ++)
				loc = next_s[j];
			int temp = next_s[loc];
			next_s[loc] = num_s; 
			next_s[num_s] = temp;
		}
		else {
			for (int j = 0, count = 0; count < pos - 1; j = next_f[j], count ++)
				loc = next_f[j]; 
			int temp = next_f[loc];
			next_f[loc] = num_f; 
			next_f[num_f] = temp;
		}
	}
}

void check_move() {
	if (num_f) {
		for (int i = next_f[0]; i != 0 && next_f[i]; i = next_f[i]) {
			if (infor_f[next_f[i]][1] <= 0) {
				next_f[i] = next_f[next_f[i]];
				num_f --;
				break;
			}
		}
		if (infor_f[next_f[0]][1] <= 0) { next_f[0] = next_f[next_f[0]]; num_f --;}
	} 
	if(!num_s) return;
	for (int j = next_s[0]; j != 0 && next_s[j] != 0; j = next_s[j]) {
		if (infor_s[next_s[j]][1] <= 0) {
			next_s[j] = next_s[next_s[j]];
			num_s --;
			break;
		}
	}
	if (infor_s[next_s[0]][1] <= 0) { next_s[0] = next_s[next_s[0]]; num_s --;}
}

void attack(int flag) {
	int att = 0, def = 0;
	scanf("%d %d", &att, &def);
	
	int ind_a, ind_d, count = 0;
	if (flag) {
		ind_a = next_s[0], ind_d = next_f[0];
		for (ind_a = next_s[0], count = 0; count < att - 1; ind_a = next_s[ind_a]) count ++;
		for (ind_d = next_f[0], count = 0; count < def - 1; ind_d = next_f[ind_d]) count ++;
		if (def == 0) {
			boss[0] -= infor_s[ind_a][0];
		} else {
			infor_f[ind_d][1] -= infor_s[ind_a][0];
			infor_s[ind_a][1] -= infor_f[ind_d][0];
		}
	} else {
		ind_a = next_f[0], ind_d = next_s[0];
		for (ind_a = next_f[0], count = 0; count < att - 1; ind_a = next_f[ind_a]) count ++;
		for (ind_d = next_s[0], count = 0; count < def - 1; ind_d = next_s[ind_d]) count ++;
		if (def == 0) {
			boss[1] -= infor_f[ind_a][0];
		} else {
			infor_f[ind_a][1] -= infor_s[ind_d][0];
			infor_s[ind_d][1] -= infor_f[ind_a][0];
		}
	}
	check_move();
}

int main() {
	#ifdef DEBUG
	freopen("a.txt", "r", stdin);
	#endif
	int n, flag = 0;
	char op[10];
	scanf("%d", &n);
	while (n --) {
		if (check()) break;
		scanf("%s", op);
		if (!strcmp(op, "end")) { flag = !flag; continue;}
		if (!strcmp(op, "summon")) summon(flag);
		if (!strcmp(op, "attack")) attack(flag);
	}
	out();
	return 0;
} 
