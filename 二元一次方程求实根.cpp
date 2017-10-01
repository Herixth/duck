#include<stdio.h>
#include<math.h>
void CalculateRealRoot(double a1,double b1,double c1);
int main(void)
{
	double a,b,c;
    printf("please input a:");
    scanf("%lf",&a);
    printf("please input b:");
    scanf("%lf",&b);
    printf("please input c:");
    scanf("%lf",&c);
    CalculateRealRoot(a,b,c);
    return 0;
}
void CalculateRealRoot(double a1,double b1,double c1)
{
	double delta,x1,x2;
	delta=b1*b1-4*a1*c1;
	if(delta<0)
	{
		printf("No Real Root.\n");
	}
	else
	{
		if(delta=0)
		{
			x1=-b1/(2*a1);
			x2=-b1/(2*a1);
			printf("x1=%lf,x2=%lf.\n",x1,x2);
		}
		else
		{
			x1=(-b1+sqrt(delta))/(2*a1);
			x2=(-b1-sqrt(delta))/(2*a1);
			printf("x1=%lf,x2=%lf.\n",x1,x2);
		}
	}
}
