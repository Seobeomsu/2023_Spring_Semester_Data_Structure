#include <stdio.h>

int main()
{
    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d\n", i);            //i의값 1234
    printf("address of i == %p\n", &i);         //i의 주소값
    printf("value of ptr == %p\n", ptr);        //ptr은 아직 초기화가안되었으므로 쓰레기값
    printf("address of ptr == %p\n", &ptr);     //ptr의 주소값 출력


    ptr = &i; /* ptr is now holding the address of i */ //ptr에 i의 주소값을 입력

    printf("\n[checking values after ptr = &i] \n");
    printf("value of i == %d\n", i);                    //i의값 1234
    printf("address of i == %p\n", &i);                 //i의 주소값
    printf("value of ptr == %p\n", ptr);                //ptr의 값, 즉 i의 주소값
    printf("address of ptr == %p\n", &ptr);             //ptr의 주소값 출력
    printf("value of *ptr == %d\n", *ptr);              //*ptr은 ptr의 값인 i의 주솟값이 가르키는 값을 출력 즉 i의값 출력과같다

    dptr = &ptr; /* dptr is now holding the address of ptr */       //dptr에 ptr의 주소값를 입력.

    printf("\n[checking values after dptr = &ptr] \n");
    printf("value of i == %d\n", i);                   //i의값 1234
    printf("address of i == %p\n", &i);                //i의 주소값
    printf("value of ptr == %p\n", ptr);               //ptr의 값, 즉 i의 주소값
    printf("address of ptr == %p\n", &ptr);            //ptr의 주소값 출력.
    printf("value of *ptr == %d\n", *ptr);             //*ptr은 ptr의 값인 i의 주솟값이 가르키는 값을 출력 즉 i의값 출력과같다
    printf("value of dptr == %p\n", dptr);             //dptr의 값 즉 ptr의 주소값
    printf("address of ptr == %p\n", &dptr);           //dptr의 주소값
    printf("value of *dptr == %p\n", *dptr);           //*dptr은 dptr가 가르키는 ptr의 값, 즉 i의 주소값 출력
    printf("value of **dptr == %d\n", **dptr);         //**dptr은 dptr가 가르키는 ptr로 이동 후 다시 ptr가 가르키는 값인 i의값을 출력

    *ptr = 7777; /* changing the value of *ptr */      //*ptr이 가르키는 i의값에 7777을 입력

    printf("\n[after *ptr = 7777] \n");
    printf("value of i == %d\n", i);                   //i의 값은 위에서 7777로 변경됨
    printf("value of *ptr == %d\n", *ptr);             //*ptr가 가르키는 값 i의 값인 7777이 출력
    printf("value of **dptr == %d\n", **dptr);         //**dptr -> *(*dptr) -> *ptr -> i , i값 7777출력

    **dptr = 8888; /* changing the value of **dptr */  //**dptr에 8888을 입력. **dptr은 *ptr을 가르키고 *ptr은 i를 가르키므로 I에 8888입력.

    printf("\n[after **dptr = 8888] \n");               
    printf("value of i == %d\n", i);                   //i에 입력한 8888출력.
    printf("value of *ptr == %d\n", *ptr);             //*ptr은 i를 가르키므로 8888출력.
    printf("value of **dptr == %d\n", **dptr);         //**dptr -> *(*dptr) -> *ptr -> i , i값 7777출력

    printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
    
    return 0;
}