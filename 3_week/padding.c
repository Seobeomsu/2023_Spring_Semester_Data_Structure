#include <stdio.h>
struct student
{
  char lastName[13]; /* 13 bytes */
  int studentId;     /* 4 bytes */
  short grade;       /* 2 bytes */
};
int main()
{
  struct student pst;
  printf("size of student = %ld\n", sizeof(struct student));
  // 구조체의 바이트합은 19byte 이지만 4byte씩 으로 padding 추가하므로
  // 16+4+4 = 24byte가 된다.
  printf("size of int = %ld\n", sizeof(int));  // int 형은 4byte
  printf("size of short = %ld\n", sizeof(short)); // short 형은 2byte
  printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
  return 0;printf("\n[-----[SeoBeomsu][2019019014]-----]\n");
}