#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(){
	int year, num;
	int month = 0, day = 0;
	int is_r;
	scanf("%d", &year);
	scanf("%d", &num);
	
	if(year % 100){
		if(year % 4)
		is_r = 0;
		else
		is_r = 1;
	}else{
		if(year % 400)
		is_r = 0;
		else
		is_r = 1;
	}
	
	int record[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0};
	record[1] += is_r;
	
	int sum = 0;
	for( ; month < 12; month ++){
		sum += record[month];
		if(sum > num)
		break;
	}
	sum -= record[month];
	day = num - sum;
	month ++;
	
	if(!day){
		month --;
		day = record[month - 1];
	}
//	if(num == 365)
//	if(is_r){
//		month = 12;
//		day = 30;
//	}else{
//		month = 12;
//		day = 31;
//	}
	
	printf("%d\n%d\n", month, day);
	
	return 0;
}
