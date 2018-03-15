#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int mo[1000][1000];
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	
	for(int i = 0; i < n; i ++)
	for(int j = 0; j < m; j ++)
	scanf("%d", &mo[i][j]);
	
	for(int u = m - 1; u >= 0; u --){
		for(int h = 0; h < n; h ++)
		printf("%d ",mo[h][u]);
		printf("\n");
	}
	
	
	return 0;
}
