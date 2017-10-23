#include<stdio.h>
#include<math.h>
#define N 10000
int main(){
    int a, b, c, f, n;  
    int i, j;
    int d[N];
    scanf("%d",&n);
    
    for( j = 0; j < n; j++ ){
        scanf("%d %d %d",&a,&b,&f);
        c = a / b;
        
        for( i = 1; i<= f + 1; i++ ){      	
            int yu;
            yu = a % b;
            d[i] = ( yu * 10 ) / b;
            a = yu * 10 % b;
        }
        
        if( d[f + 1] >= 5 ){
        	d[f]++;
		}
        printf("%d.",c);
        for( i = 1; i <= f; i++ ){
            printf("%d",d[i]);
        }
        printf("\n");
    }
    
    return 0;
}
