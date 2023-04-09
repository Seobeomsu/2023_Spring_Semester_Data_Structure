#include <stdio.h>
#include <stdlib.h>
// 함수들의 원형 선언
int **create_matrix(int row, int col);
int fill_data(int **matrix, int row, int col);
void print_matrix(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col);
int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col);
int free_matrix(int **matrix, int row, int col);
int check_matrix(int **matrix);

int main() {
  char command;
  int row, col; // row , col 입력받기
  printf("Input row : ");
  scanf("%d", &row);
  printf("Input col : ");
  scanf("%d", &col);
  if (row <= 0 || col <= 0) { // row, col 0아래의 숫자면 오류 출력
    printf("Check the sizes of row and col!\n");
    return -1;
  }
  int **matrix_a = create_matrix(row, col);
  int **matrix_b = create_matrix(row, col);
  int **matrix_t = create_matrix(col, row);

  check_matrix(matrix_a);check_matrix(matrix_b);check_matrix(matrix_t);

  do {
    printf("-----------[SeoBeomsu][2019019014]-------------\n");
    printf(" Initialize Matrix  = Z   Print Matrix     = P \n");
    printf(" Add Matrix         = A   Subtract Matrix  = S \n");
    printf(" Transpose matrix_a = T   Multiply Matrix  = M \n");
    printf(" Quit               = Q \n");
    printf("-----------------------------------------------\n");
    printf("Command = ");
    scanf("%c", &command);

    switch (command) {
      case 'z': case 'Z': // Z 입력시 배열 입력받기
        printf("Initialize Matrix\n");
        printf("Get First Matrix\n");
        fill_data(matrix_a, row, col);
        printf("Get Second Matrix\n");
        fill_data(matrix_b, row, col);
        break;
      case 'p': case 'P': // P 입력시 배열 출력
        printf("Print Matrix\n");
        printf("Matrix A\n");
        print_matrix(matrix_a, row, col);
        printf("Matrix B\n");
        print_matrix(matrix_b, row, col);
        break;
      case 'a': case 'A': // A 입력시 A,B 행렬 덧셈
        printf("Addition Matrix\n");
        addition_matrix(matrix_a, matrix_b, row, col);
        break;
      case 's': case 'S': // S 입력시 A,B 행렬 뺄셈
        printf("Subtraction Matrix\n");
        subtraction_matrix(matrix_a, matrix_b, row, col);
        break;
      case 't': case 'T': // T 입력시 A의 전치행렬 생성
        printf("Transpose Matrix_A\n");
        transpose_matrix(matrix_a, matrix_t, col, row);
        print_matrix(matrix_t,col,row);
        break;
      case 'm': case 'M': // M 입력시 A와 A의 전치행렬 T 곱셈
        printf("Multiply Matrix\n");
        transpose_matrix(matrix_a, matrix_t, col, row);
        multiply_matrix(matrix_a, matrix_t, row, col);
        break;
      case 'q': case 'Q': // Q 입력시 모든행렬의 메모리 해제
        printf("Quit Matrix\n");
        free_matrix(matrix_a,row,col);
        free_matrix(matrix_b,row,col);
        free_matrix(matrix_t,row,col);
        break;
      default:
        printf("\n------ ReEnter -------\n");
        break;
    }
  }while(command != 'Q' && command != 'q'); // Q 입력시 종료
  return 0;
}

int **create_matrix(int row, int col) { 
  int **matrix = (int**)malloc(sizeof(int*) * row); // 2차원 배열 주소*행 크기 선언
  for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col); // 첫번째 열의 주소를 각행에 입력
  }
  check_matrix(matrix); // 오류 검사
  return matrix; // matrix 반환
}

int fill_data(int **matrix, int row, int col) { // 일일이 데이터 입력받기
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("array[%d][%d]=",i,j);
      scanf("%d",&matrix[i][j]);
    }
  }
  return 1;
}

void print_matrix(int **matrix, int row, int col) { // 행렬 출력
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%4d", matrix[i][j]);
    }
      printf("\n");
  }
}

int addition_matrix(int **matrix_a, int **matrix_b, int row, int col) {

  int **matrix_sum = (int **)malloc(sizeof(int *) * row);//matrix sum 선언
  for (int i = 0; i < row; i++) {
    matrix_sum[i] = (int *)malloc(sizeof(int) * col);
    for (int j = 0; j < col; j++) {
      matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];//각자리에 덧셈해서 입력
    }     
  }
  check_matrix(matrix_sum);           // 오류 검사
  print_matrix(matrix_sum, row, col); // 출력
  free_matrix(matrix_sum,row,col);    // 사용한 동적배열 반환
  return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col) {
  int **matrix_sub = (int **)malloc(sizeof(int *) * row); // matrix sub 생성
  for (int i = 0; i < row; i++) {
    matrix_sub[i] = (int *)malloc(sizeof(int) * col);
    for (int j = 0; j < col; j++) {
      matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    } 
  }
  check_matrix(matrix_sub);           // 오류 검사
  print_matrix(matrix_sub, row, col); // 출력
  free_matrix(matrix_sub,row,col);    // 사용한 동적배열 반환
  return 1;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix_t[i][j] = matrix_a[j][i]; // 행과 열을 교환하여 데이터입력
    } 
  }
  check_matrix(matrix_t); // 오류검사
  return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col) {
  int **matrix_mul = create_matrix(row,row); // matrix mul 선언
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < row; j++) {
      matrix_mul[i][j] = 0;            // 초기갑 0 입력, 쓰레기값으로인한 오류 방지
      for(int k = 0; k < col; k++) {   // 행렬의 곱셈 실행
        matrix_mul[i][j] += matrix_a[i][k] * matrix_t[k][j]; 
      }
    }
  }
  check_matrix(matrix_mul);           // 오류 검사
  print_matrix(matrix_mul, row, row); // 출력
  free_matrix(matrix_mul,row,col);    // 사용한 동적배열 반환
  return 1;
}

int free_matrix(int **matrix, int row, int col){
	for (int i= 0; i < row; i++) {
		free(matrix[i]);  // 각열에 선언된 동적배열 반환
	}
	free(matrix);       // 위의 열을 선언했던 동적배열 반환
  return 1;
}

int check_matrix(int **matrix){
  if (matrix == NULL) { // matrix의 값이 NULL 인지 검사, NULL일 경우 오류 출력
    printf("Error Matrix has data NULL\n");
    return -1;
  }
}