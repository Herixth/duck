#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

bool is_spe(int year) {
	return !(year % 400) || (!(year % 4) && (year % 100));
}

int year_week(int year) {
	long long sum = 2;
	for (int i = 1850; i < year; i ++) sum += 365 + is_spe(i);
	return sum % 7 ? sum % 7 : 7;
}

int month_week(int year, int month, int week_f) {
	int list[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	list[1] += is_spe(year);
	int sum = week_f;
	for (int i = 1; i < month; i ++)
		sum += list[i - 1];
	return sum % 7 ? sum % 7 : 7;
}

void print(int year, int week_f, int num, int week, int month) {
	int list[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	list[1] += is_spe(year);
	int loss = week_f > week ? 8 - week_f + week : week - week_f + 1;
	(num - 1) * 7 + loss <= list[month - 1] ? printf("%d/%02d/%02d", year, month, (num - 1) * 7 + loss) : printf("none");
	printf("\n");
}

int main() {
	int month, num, week, year_f, year_l;
	scanf("%d%d%d%d%d", &month, &num, &week, &year_f, &year_l);
	for (int year = year_f; year <= year_l; year ++)
		print(year, month_week(year, month, year_week(year)), num, week, month);
	return 0;
}
