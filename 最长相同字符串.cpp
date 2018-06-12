#include<stdio.h>
#include<math.h>
#include<string.h>

int main(){
	char input[100][100];
	char record[100][100];
	int count[100] = {0};
	int length[100] = {0};
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i ++) {
		scanf("%s", input[i]);
		length[i] = strlen(input[i]);
		printf("%s  %d\n",input[i],length[i]);
	}
	
	
	
	return 0;
}
