#include<stdio.h>
#include<stdlib.h>
void main()
{
  int **x; // 더블 포인터 x
  printf("sizeof(x) = %lu\n", sizeof(x));       // int형이므로 4바이트 x에는 x*의 주소가들어감 
  printf("sizeof(*x) = %lu\n", sizeof(*x));     // *x는 **x의 주소가 입력되어있음 4바이트
  printf("sizeof(**x) = %lu\n", sizeof(**x));   // 포인터는 int 형 변수

  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
}