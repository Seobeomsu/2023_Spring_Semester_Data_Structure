#include <stdio.h>
#define MAX_SIZE 100
float sum1(float list[], int);  // 함수들 원형 선언
float sum2(float *list, int);
float sum3(int n, float *list);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
  for(i=0; i < MAX_SIZE; i++) // maxsize까지 input[]배열에 값을 0,1,2 ,,, 99,100 입력
    input[i] = i;
  /* for checking call by reference */
  printf("--------------------------------------\n");
  printf(" sum1(input, MAX_SIZE) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);      // input 배열의 주소값 출력
  answer = sum1(input, MAX_SIZE);       // input 배열을 매개변수로 전달
  printf("The sum is: %f\n\n", answer); // sum1에서 리턴된 값 출력 4950
  printf("--------------------------------------\n");
  printf(" sum2(input, MAX_SIZE) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);      // input 배열의 주소값 출력
  answer = sum2(input, MAX_SIZE);       // input 배열을 매개변수로 전달
  printf("The sum is: %f\n\n", answer); //
  printf("--------------------------------------\n");
  printf(" sum3(MAX_SIZE, input) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);      // input 배열의 주소값 출력
  answer = sum3(MAX_SIZE, input);       // input 배열을 매개변수로 전달
  printf("The sum is: %f\n\n", answer); //
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
}

float sum1(float list[], int n) { // 매개변수를 call by reference 형식으로 받음 
  printf("list \t= %p\n", list);      
  // list는 메인에서복사된 input의 주소가 출력된다.
  printf("&list \t= %p\n\n", &list);
  // &list는 새로운공간에서 다시선언되었으므로 다른주소값이 출력된다.
  int i;
  float tempsum = 0;
  for(i = 0; i < n; i++)
    tempsum += list[i]; // 배열의 값들의 합을 구함 즉 시그마 100, 4950
  return tempsum; // return 하면서 reference 되었었으므로 list 변수 소멸
}
float sum2(float *list, int n) {
  printf("list \t= %p\n", list);      // call by value형식으로 input의 시작주소값을 받아옴
  printf("&list \t= %p\n\n", &list);  // list 배열의 시작주소값 출력
  int i;
  float tempsum = 0;
  for(i = 0; i < n; i++)
    tempsum += *(list + i);  // 배열의 값들의 합을 구함 즉 시그마 100, 4950
  return tempsum; // return 하여도 call by value형식으로 새로변수를 저장하여 list 변수의 자리는 살아있음
}
/* stack variable reuse test */
float sum3(int n, float *list) {
  printf("list\t= %p\n", list);       // list 배열의 시작주소를반환 input과동일
  printf("&list \t= %p\n\n", &list);  
  //call by value 형식으로 데이터를받아, list가 하나더 선언되어 주소값이 4만큼 증가함
  int i;
  float tempsum = 0;
  for(i = 0; i < n; i++)
    tempsum += *(list + i);  // 배열의 값들의 합을 구함 즉 시그마 100, 4950
  return tempsum;
}