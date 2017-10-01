#include<stdio.h>
int main(void)
{double a,b,c,d,e,f,x,y;
printf("ax+by=c.\n");
printf("dx+ey=f.\n");
printf("please input a,b,c,d,e,f.\n");
scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
if(a*e-d*b==0)
{printf("NONONONONONO");
return 0;
}
x=(c*e-b*f)/(a*e-b*d);
y=(a*f-c*d)/(a*e-b*d);
printf("x=%lf.\ny=%lf",x,y);
return 0;
}

