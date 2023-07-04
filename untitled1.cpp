#include <stdio.h>
#include <math.h>
  int  main()
{
	float a,b,c,s,area;
	printf("请输入三边长 :");
	scanf("%f%f%f",&a,&b,&c);
	s=(a+b+c)/2;
	area=sqrt(s*(s-a)*(s-b)*(s-c));
	printf("%f\n",area);
}
