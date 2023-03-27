#include <stdio.h>
void print_one(int *ptr, int rows); // 프린트함수 원형 선언
int main()
{
  int one[] = {0, 1, 2, 3, 4}; // 값 0,1,2,3,4 인 크기 5짜리 배열 one 선언
  printf("one = %p\n", one);          //one 배열의 시작주소값 출력
  printf("&one = %p\n", &one);        //one 배열의 시작주소값 출력
  printf("&one[0] = %p\n", &one[0]);  //one[0] 주소값 출력
  printf("\n");
  printf("------------------------------------\n");
  printf(" print_one(&one[0], 5) \n"); 
  printf("------------------------------------\n");
  print_one(&one[0], 5);    // print_one 함수에 &one[0]의 주소값과 배열크기를 매개변수로 전달
  printf("------------------------------------\n");
  printf(" print_one(one, 5) \n");
  printf("------------------------------------\n");
  print_one(one, 5);        // print_one 함수에 one 배열의 시작주소값과 배열크기를 매개변수로 전달
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
  return 0;
}
void print_one(int *ptr, int rows)
{ /* print out a one-dimensional array using a pointer */
  int i;
  printf("Address \t Contents\n");
  for (i = 0; i < rows; i++) // rows 즉 배열크기만큼 반복
    printf("%p \t %5d\n", ptr + i, *(ptr + i)); 
    // ptr은 매개변수로받아온 주소값, *(ptr +i)는 그 주소의 값을출력
    // ptr + i 에서 i는 인트형값이므로 주소값에 더해지면 4만큼 증가
    // 즉 위는 배열을 for 문으로 프린트하는것과 같다.
    // 0,1,2,3,4 출력
  printf("\n");
}