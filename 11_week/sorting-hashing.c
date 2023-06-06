#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);
/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);
/* array a에 대한 hash table을 만든다. */
int hashing(int *a, int **ht);
/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main(){
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("---------------[      [SeoBeomSu] [2019019014]      ]-----------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a){
	int *temp = NULL;

	if(*a == NULL) { // array가 NULL일경우 메모리할당
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp; // 할당된 메모리주소를 복사하여 temp에 저장 , main함수에서 array를 조작할수있게해줌
	} else
		temp = *a;
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 랜덤값을 배열에 저장
		temp[i] = rand() % MAX_ARRAY_SIZE;
	return 0;
}

int freeArray(int *a){ // 배열의 메모리반환
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a){ // 배열을 순서대로 출력
	if (a == NULL) { // initialize 되지않으면 출력
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 값이존재하면 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a){ // 선택정렬
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열의 원래값 출력
	for (i = 0; i < MAX_ARRAY_SIZE; i++){ // 정렬을 위한반복
		minindex = i; //최소값의 위치
		min = a[i]; //최소값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++){ // 비교값 반복
			if (min > a[j]){ // 현재의값이 최소값보다 크면
				min = a[j]; // 현재의값을 저장
				minindex = j; // 현재값 키 저장
			}
		}
		a[minindex] = a[i]; //최소값으로 지정된위치에 정렬되기전 처음값을 입력
		a[i] = min; // 정렬되기전 맨 처음위치에 최소값 입력
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬후 값 출력
	return 0;
}

int insertionSort(int *a){ //삽입정렬
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬전의 값 출력
	for(i = 1; i < MAX_ARRAY_SIZE; i++){ //정렬반복
		t = a[i]; // t에 i번쨰의 값 저장
		j = i; //i번 반복하기위한 j
		while (a[j-1] > t && j > 0){  // 좌측값이 우측값보다 크다면
			a[j] = a[j-1]; // 좌측값을 우측에 입력
			j--; // 다음 j로
		}
		a[j] = t; // 더이상 크지않을때까지 비교하고 좌측값이 더 커진다면 현위치에서 i번쨰에 가져온값 입력
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된후의 배열 출력
	return 0;
}

int bubbleSort(int *a){ // 버블정렬
	int i, j, t;
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬이전의 배열 출력
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		for (j = 0; j < MAX_ARRAY_SIZE; j++){ // n^2만큼 반복
			if (a[j-1] > a[j]){ // 좌측값이 우측값보다 크다면
				t = a[j-1]; // 값을 서로 교환
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬후 배열 출력
	return 0;
}

int shellSort(int *a){ // 셀정렬
	int i, j, k, h, v;
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬이전의 배열 출력
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2){ // 반복마다 h의 값 1될때까지 절반으로 감소
		for (i = 0; i < h; i++){ // 반복될때마다 h-1까지 1씩 증가
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h){ // 반복마다 0부터 h까지 증가
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v){ // 선택정렬과 동일
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬후 배열 출력
	return 0;
}

int quickSort(int *a, int n){ // 퀵정렬
	int v, t;
	int i, j;
	if (n > 1){
		v = a[n-1]; // 피봇으로 지정
		i = -1;
		j = n - 1;
		while(1){
			while(a[++i] < v); // 피봇보다 큰값을 찾을때까지 증가
			while(a[--j] > v); // 피봇보다 작은값을 찾을때까지 감소
			if (i >= j) break; // 서로의 위치가 역전되면 종료
			t = a[i]; // 서로의 위치를 교환
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; // 피봇보다 큰값의 위치를 교환
		a[i] = a[n-1];
		a[n-1] = t;
		quickSort(a, i); // 교환된 피봇위치의 좌측 퀵정렬
		quickSort(a+i+1, n-i-1); // 교환된 피봇위치의 우측 퀵정렬
	}
	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht){
	int *hashtable = NULL;
	if(*ht == NULL) {  // hashtable이 NULL이면 메모리할당
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable; // 할당된 메모리 주소복사 main함수에서 조작가능
	} else {
		hashtable = *ht; // hashtable이 NULL이 아니면 재사용
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 해시테이블 초기화
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++){
		key = a[i]; // 배열에 저장된 순서대로 key에 입력
		hashcode = hashCode(key); // 최대크기로 나눈 나머지를 해시코드로 저장
		if (hashtable[hashcode] == -1){ // 해시테이블이 -1이면
			hashtable[hashcode] = key; // 해당테이블에 key 입력
		} else 	{ // 아닐경우
			index = hashcode; // index 변수에 hashcode입력
			while(hashtable[index] != -1){ // 해시테이블이 빌때까지
				index = (++index) % MAX_HASH_TABLE_SIZE; // index값을 늘려가며 찾는다
			}
			hashtable[index] = key; // 비어있는 해시테이블 발견시 그위치를 key에 입력
		}
	}
	return 0;
}

int search(int *ht, int key){
	int index = hashCode(key); // index에 key값 입력
	if(ht[index] == key) // 해당위치에 key가 있다면
		return index; // index 반환

	while(ht[++index] != key){ // 해시테이블에 키가있을때가지 반복
		index = index % MAX_HASH_TABLE_SIZE; //최대크기를 넘지않게 설정
	}
	return index; // 키 발견시 위치 반환
}


