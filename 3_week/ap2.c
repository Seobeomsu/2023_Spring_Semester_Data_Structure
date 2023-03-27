#include <stdio.h>
#include <stdlib.h>
void main()
{
  int list[5];   // 배열의갯수 5개짜리 list
  int *plist[5]; // 배열의갯수 5개짜리 포인터 plist
  list[0] = 10;
  list[1] = 11;
  plist[0] = (int *)malloc(sizeof(int)); // plist를 4바이트로 동적배열선언
  printf("list[0] \t= %d\n", list[0]);   // list[0]의값 10 출력
  printf("list \t\t= %p\n", list);       // list배열의 시작주소값출력
  printf("&list[0] \t= %p\n", &list[0]); // list[0]의 주소값출력 위와동일
  printf("list + 0 \t= %p\n", list + 0); // list배열의 시작주소값 + 0 출력
  printf("list + 1 \t= %p\n", list + 1); // list배열의 시작주소값 + 4(int의 byte)*1
  printf("list + 2 \t= %p\n", list + 2); // list배열의 시작주소값 + 4(int의 byte)*2
  printf("list + 3 \t= %p\n", list + 3); // list배열의 시작주소값 + 4(int의 byte)*3
  printf("list + 4 \t= %p\n", list + 4); // list배열의 시작주소값 + 4(int의 byte)*4
  printf("&list[4] \t= %p\n", &list[4]); // list[4]부분의 시작주소값 출력
  free(plist[0]);                        // 동적배열 반환
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
}