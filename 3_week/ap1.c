#include <stdio.h>
#include <stdlib.h>

void main()
{
  int list[5]; // list형 배열선언
  int *plist[5] = {
      NULL, // 포인터형 plist 배열선언후 각자리에 NULL값 입력
  };
  plist[0] = (int *)malloc(sizeof(int)); // 동적배열 plist[] 선언
  list[0] = 1; 
  list[1] = 100;
  *plist[0] = 200;
  printf("list[0] = %d\n", list[0]);    //list[0]의값 반환
  printf("&list[0] = %p\n", &list[0]);  //list[0]의 주소값 반환
  printf("list = %p\n", list);          //list 배열의 시작주소반환 즉 &list[0]
  printf("&list = %p\n", &list);        //list 배열의 시작주소 반환
  printf("----------------------------------------\n\n");
  printf("list[1] = %d\n", list[1]);        //list[1]의값 100 출력ㅊ
  printf("&list[1] = %p\n", &list[1]);      //list[1]의 주소 출력
  printf("*(list+1) = %d\n", *(list + 1));  
  //list->&list[0],&list+1->&list[1],*(&list+1)->list[1]->100
  printf("list+1 = %p\n", list + 1);        //list+1 -> &list[1]-> list[1]의 주솟값 출력
  printf("----------------------------------------\n\n");
  printf("*plist[0] = %d\n", *plist[0]);    //plist[0]의 주소에 들어간값 200 출력
  printf("&plist[0] = %p\n", &plist[0]);    //plist[0]의 주소값출력
  printf("&plist = %p\n", &plist);          //plist[0]의 주소값출력
  printf("plist = %p\n", plist);            //plist[0]의 주소값출력
  printf("plist[0] = %p\n", plist[0]);      //plist[0]은 200의 값이들어가있는 주소값 출력
  printf("plist[1] = %p\n", plist[1]);      //plist[1]~plist[4]는 NULL값이들어가있기에 0으로 출력됨
  printf("plist[2] = %p\n", plist[2]);
  printf("plist[3] = %p\n", plist[3]);
  printf("plist[4] = %p\n", plist[4]);
  free(plist[0]); // 동적배열 반환
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
}