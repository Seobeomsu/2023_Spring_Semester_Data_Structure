#include <stdio.h>
#include <stdlib.h>

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
  int row, col;
  printf("Input row : ");
  scanf("%d", &row);
  printf("Input col : ");
  scanf("%d", &col);
  if (row <= 0 || col <= 0) {
    printf("Check the sizes of row and col!\n");
    return -1;
  }
  int **matrix_a = create_matrix(row, col);
  int **matrix_b = create_matrix(row, col);
  int **matrix_t = create_matrix(col, row);

  check_matrix(matrix_a);check_matrix(matrix_b);check_matrix(matrix_t);

  do {
    printf("-----------[SeoBeomsu][2019019014]-------------\n");
    printf(" Initialize Matrix  = z   Print Matrix     = p \n");
    printf(" Add Matrix         = a   Subtract Matrix  = s \n");
    printf(" Transpose matrix_a = t   Multiply Matrix  = m \n");
    printf(" Quit               = q \n");
    printf("-----------------------------------------------\n");
    printf("Command = ");
    scanf(" %c", &command);

    switch (command) {
      case 'z': case 'Z':
        printf("Initialize Matrix\n");
        printf("Get First Matrix\n");
        fill_data(matrix_a, row, col);
        printf("Get Second Matrix\n");
        fill_data(matrix_b, row, col);
        break;
      case 'p': case 'P':
        printf("Print Matrix\n");
        printf("Matrix A\n");
        print_matrix(matrix_a, row, col);
        printf("Matrix B\n");
        print_matrix(matrix_b, row, col);
        break;
      case 'a': case 'A':
        printf("Addition Matrix\n");
        addition_matrix(matrix_a, matrix_b, row, col);
        break;
      case 's': case 'S':
        printf("Subtraction Matrix\n");
        subtraction_matrix(matrix_a, matrix_b, row, col);
        break;
      case 't': case 'T':
        printf("Transpose Matrix_A\n");
        transpose_matrix(matrix_a, matrix_t, col, row);
        print_matrix(matrix_t,col,row);
        break;
      case 'm': case 'M':
        printf("Multiply Matrix\n");
        transpose_matrix(matrix_a, matrix_t, col, row);
        multiply_matrix(matrix_a, matrix_t, row, col);
        break;
      case 'q': case 'Q':
        printf("Quit Matrix\n");
        free_matrix(matrix_a,row,col);
        free_matrix(matrix_b,row,col);
        free_matrix(matrix_t,row,col);
        break;
      default:
        printf("\n----------------------    Re-Enter!    -----------------------\n");
        break;
    }
  }while(command != 'Q' && command != 'q');
  return 0;
}

int **create_matrix(int row, int col) {
  int **matrix = (int**)malloc(sizeof(int*) * row);

  for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col);
  }
  check_matrix(matrix);
  return matrix;
}

int fill_data(int **matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("array[%d][%d]=",i,j);
      scanf("%d",&matrix[i][j]);
    }
  }
  return 1;
}

void print_matrix(int **matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%4d", matrix[i][j]);
    }
      printf("\n");
  }
}

int addition_matrix(int **matrix_a, int **matrix_b, int row, int col) {

  int **matrix_sum = (int **)malloc(sizeof(int *) * row);     
  for (int i = 0; i < row; i++) {
    matrix_sum[i] = (int *)malloc(sizeof(int) * col);
    for (int j = 0; j < col; j++) {
      matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }     
  }
  check_matrix(matrix_sum);
  print_matrix(matrix_sum, row, col);   
  free_matrix(matrix_sum,row,col);
  return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col) {
  int **matrix_sub = (int **)malloc(sizeof(int *) * row); 
  for (int i = 0; i < row; i++) {
    matrix_sub[i] = (int *)malloc(sizeof(int) * col);
    for (int j = 0; j < col; j++) {
      matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    } 
  }
  print_matrix(matrix_sub, row, col);
  free_matrix(matrix_sub,row,col); 
  check_matrix(matrix_sub);
  return 1;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix_t[i][j] = matrix_a[j][i];
    } 
  }
  check_matrix(matrix_t);
  return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col) {
  int **mul_matrix = create_matrix(row,row);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < row; j++) {
      mul_matrix[i][j] = 0;              
      for(int k = 0; k < col; k++) { 
        mul_matrix[i][j] += matrix_a[i][k] * matrix_t[k][j];
      }
    }
  }
  print_matrix(mul_matrix, row, row);
  free_matrix(mul_matrix,row,col);
  check_matrix(matrix_a);
  check_matrix(matrix_t);
  return 1;
}

int free_matrix(int **matrix, int row, int col){
	for (int i= 0; i < row; i++) {
		free(matrix[i]);
	}
	free(matrix);
  return 1;
}

int check_matrix(int **matrix){
  if (matrix == NULL) { 
    printf("Error Matrix has data NULL\n");
    return -1;
  }
}