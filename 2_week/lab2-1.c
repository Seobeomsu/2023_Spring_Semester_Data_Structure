#include <stdio.h>

int main()
{   // char,integer,float,double 형 변수선언
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    printf("Size of char: %ld byte\n",sizeof(charType));        //charType은 char형이므로 1바이트
    printf("Size of int: %ld bytes\n",sizeof(integerType));     //integerType은 integer형이므로 4바이트
    printf("Size of float: %ld bytes\n",sizeof(floatType));     //floatType은 float형이므로 4바이트
    printf("Size of double: %ld bytes\n",sizeof(doubleType));   //doubleType은 double형이므로 8바이트

    printf("-----------------------------------------\n");

    printf("Size of char: %ld byte\n",sizeof(char));            //char은 1바이트
    printf("Size of int: %ld bytes\n",sizeof(int));             //int은 4바이트
    printf("Size of float: %ld bytes\n",sizeof(float));         //float은 4바이트
    printf("Size of double: %ld bytes\n",sizeof(double));       //double은 8바이트

    printf("-----------------------------------------\n");

    printf("Size of char*: %ld byte\n",sizeof(char*));          //포인터의 선언에는 4바이트가 필요하다.
    printf("Size of int*: %ld bytes\n",sizeof(int*));           //아래의 내용들은 포인터이므로 4바이트가 출력된다.
    printf("Size of float*: %ld bytes\n",sizeof(float*));
    printf("Size of double*: %ld bytes\n",sizeof(double*));

    printf("\n[-----[SeoBeomsu][2019019014]-----]\n");

    return 0;
}