#include <stdio.h>
int main()
{
// 변수 i 와 변수 i의 포인터 선언
int i, *p;
//i에 10 대입.
i = 10;
printf("value of i = %d\n", i);
//i의 주솟값 = 10
printf("address of i = %p\n", &i);
//p의 값은 입력되지않아 0으로 되있는상태.
printf("value of p = %p\n", p);
//p의 주솟값
printf("address of p = %p\n", &p);
//p에 변수 i의 주솟값 입력
p = &i;
printf("\n\n----- after p = &i ------------\n\n");
//p의 값은 i의 주솟값
printf("value of p = %p\n", p);
//p의 주솟값 위와 동일
printf("address of p = %p\n", &p);
//포인터p의 값 즉 p의 값이 나타내는 주소의 값 10
printf("dereferencing *p = %d\n", *p);
return 0;
}
