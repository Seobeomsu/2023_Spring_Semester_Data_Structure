#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void){
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n------------[SeoBeomsu][2019019014]------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	return 1;
}

QueueType *createQueue(){
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ){
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement(){
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

/* complete the function */
int isEmpty(QueueType *cQ) {
	int first, end;
	first = cQ->front % MAX_QUEUE_SIZE;		//first와 end 변수에 front와 rear를 최대크기로 나눈 나머지를 넣는다
	end = cQ->rear % MAX_QUEUE_SIZE;
	if (first == end) {										// 아무것도 들어있지 않으면 front와 rear가 같아져  Que는 비어있다
		printf("Circular Queue is empty!");
		return 0;		//비어있다면 0 출력
	}else{
		return 1;		//비어있지 않다면 1 출력
	}
}

/* complete the function */
int isFull(QueueType *cQ) {
	int first, end;
	first = cQ->front % MAX_QUEUE_SIZE;			// end에 rear + 1을 최대크기로 나눈 이유는 최대로 차있을 때 
	end = (cQ->rear +1) % MAX_QUEUE_SIZE;		// 원형 큐의 처음을 구별하기 위해 빈곳으로 놔두기 때문에
	if (first == end) {											// +1을 해서 빈 곳을 임의로 채운다
		printf("Circular Queue is full!");
		return 0;		// 다차면 0리턴
	}else{
		return 1;		// 다안차면 1리턴
	}
}

/* complete the function */
void enQueue(QueueType *cQ, element item) {
	if(!isFull(cQ)) {		//꽉 차있다면 0을 출력받고 !로 인해 1로 바뀜
		return;
	}else{				//현재 rear에 값이 있으므로 +1을 해서 다음칸을 가리키고
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //1을 더했을 때 오버플로우가 생기지않게 나눠줌
		cQ->queue[cQ->rear] = item;		//그 가리킨 곳에 입력받은 값을 입력
	}
	return;
}

/* complete the function */
void deQueue(QueueType *cQ) {		//큐에서 front 앞의 값을 지울 때 변수 item인 필요X
	if(!isEmpty(cQ)) {		//비어 있다면 0 출력받고 !로 인해 1로 바뀜
		return;
	}else{								//비어 있지 않다면 실행
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //1을 더했을 때 오버플로우가 생기지않게 나눠줌
		cQ->queue[cQ->front] = NULL;									//front앞에 있는 숫자를 지운다
	}
	return;
}


void printQ(QueueType *cQ){ // Que 출력
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ){ // Que의 내용들 출력
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++){
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}