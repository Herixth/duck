#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(){
	int n;
	char word[1004];
	scanf("%d\n", &n);
	fgets(word, 1004, stdin);
	char ans[1001][1001];
	word[strlen(word) - 1] = '\0';
	int col = 0, row = 0, k = 0;
	while(1){
		if(word[k] == '\0') break;
		ans[row][col] = word[k];
		k ++;
		row ++;
		if(row == n){
			col ++;
			row = 0;
		}
	}
	while(row != 0){
		ans[row][col] = ' ';
		row ++;
		if(row == n){
			col ++;
			row = 0;
		}
	}
		
	for(int i = 0; i < n; i ++){
		for(int j = col - 1; j >= 0; j --)
		printf("%c",ans[i][j]);
		printf("\n");
	}
	return 0;
}
