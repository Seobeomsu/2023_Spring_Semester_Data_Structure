#include <stdio.h>
struct student1 // 구조체 student1 선언
{
  char lastName;
  int studentId;
  char grade;
};
typedef struct // 구조체  student2 선언
{
  char lastName;
  int studentId;
  char grade;
} student2;
int main()
{
  struct student1 st1 = {'A', 100, 'A'};
  // typedef 사용한것이아니므로 struct를 붙여서 stdent1 구조의 변수 st1 선언 데이터입력
  printf("st1.lastName = %c\n", st1.lastName);    // st1 변수의 lastName 변수출력
  printf("st1.studentId = %d\n", st1.studentId);  // st1 변수의 studentId 변수출력
  printf("st1.grade = %c\n", st1.grade);          // st1 변수의 grade 변수 출력
  student2 st2 = {'B', 200, 'B'};
  // typedef를 사용했기에 구조체이름만 적고 st2변수 선언후 데이터 입력
  printf("\nst2.lastName = %c\n", st2.lastName);  // st2 변수의 lastName 변수 출력 
  printf("st2.studentId = %d\n", st2.studentId);  // st2 변수의 studentId 변수 출력
  printf("st2.grade = %c\n", st2.grade);          // st2 변수의 grade 변수 출력
  student2 st3; //stduent2 구조의 변수 st3 선언
  st3 = st2;    //st3 변수에 st2의 데이터들 입력
  printf("\nst3.lastName = %c\n", st3.lastName);  // st2의 값들을 st3에 입력했으므로 위의 내용과 동일하게 출력됨
  printf("st3.studentId = %d\n", st3.studentId);
  printf("st3.grade = %c\n", st3.grade);
  /* equality test */
  if (st3.lastName == st2.lastName||st3.studentId == st2.studentId||st3.grade == st2.grade)
  // st3 == st2 가 작동하지않아 일일이 내부의 요소들을 한개씩 비교해주어야한다.
    printf("equal\n");
  else
    printf("not equal\n");
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
  return 0;
}