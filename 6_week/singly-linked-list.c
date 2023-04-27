#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;
/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);
int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main(){
	char command;
	int key;
	headNode* headnode=NULL;
	do{
    printf("-------------------[SeoBeomsu][2019019014]----------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	return 1;
}

headNode* initialize(headNode* h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);
	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	// h와 연결된 listNode 메모리 해제 headNode도 해제되어야 함.
	listNode* p = h->first;
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

//list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;
	h->first = node;
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드 생성
	node->link = NULL;			//노드의 다음링크를 NULL로 설정
	node->key = key;				//노드에 값 입력
	if(h->first == NULL){		//헤드노드가 비어있다면
		h->first = node;			//헤드노드를 방금 생성한 노드로 설정
		return 0;
	}
	listNode* n = h->first;	//n과 m을 생성
	listNode* m = h->first;
	while (n != NULL) {			//헤드가 비어있지 않다면
		if(key <= n->key){		//key의 값이 현재 노드의 값보다 작다면
			if(n == h->first){	//헤드의 첫 노드의 key값이 입력받은 key의 값보다 작다면
				h->first = node;	//헤드를 새로 생성한 노드로 연결 후
				node->link = n;		//생성한 노드의 다음 링크로 원래 있던 노드로 연결
			}else{							//그 외에 경우
				node->link = n;		//생성한 노드의 다음링크를 현재노드로 설정 후
				m->link = node;		//현재 위치 이전에 있던 노드를 새로 생성한 노드로 링크되게 끔 설정한다.
			}
			return 0;
		}
		m = n;				//m을 n과 같은 노드로 설정 후
		n = n->link;	//n을 다음 노드로 변경
	}
	m->link = node;	//마지막까지 비교되지 않았을 때 마지막 노드의 다음을 새로 생성한 노드로 설정한다.
	return 0;
}

//list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));		//노드 생성
	listNode* n = h->first;
	listNode* m;
	node->link = NULL;				//생성한 노드의 다음 링크를 NULL로 설정
	node->key = key;					//생성한 노드에 key값을 입력
	if(h->first == NULL){			//헤드노드가 비어있다면
		h->first = node;				//헤드노드를 새로 생성한 노드로 설정
		return 0;
	}
	while (n != NULL) {				//n이 NULL일 때까지 반복
		m = n;									//m은 현재 n의 이전 노드
		n = n->link;
	}
	m->link = node;						//마지막 노드의 다음링크를 새로 생성한 노드로 설정
	return 0;
}

// list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {
	if(h->first == NULL){			//헤드노드가 비어있다면
		printf("No Node\n");		//노드가 없다고 출력 후 함수종료
		return 0;
	}
	listNode* n = h->first;			
	h->first = n->link;				//헤드노드를 현재 노드의 다음링크로 위치 후
	free(n);									//현재 노드 제거
	return 0;
}


// list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {
	if(h->first == NULL){			//헤드노드가 비어있다면
		printf("No Node\n");		//노드가 없다고 출력 후 함수 종료
		return 0;
	}
	listNode* n = h->first;		//n을 헤드노드와 같은 노드로 설정
	listNode* m = h->first;	
	while (n != NULL) {				//n이 NULL일 때까지 반복
		if(key == n->key){			//n의 key값과 입력받은 key의 값이 같을 때
			if(n == h->first){		//n이 헤드노드라면
				h->first = n->link;	//헤드노드의 다음노드를 헤드노드로 설정
			}else{								//n이 헤드노드가 아니라면
				m->link = n->link;	//이전 노드의 다음 노드를 현재 노드의 다음노드로 위치
			}
			free(n);							//그 후 현재 노드 제거
			return 0;
		}
		m = n;									//이전 노드를 현재노드로 변경 후
		n = n->link;						//현재노드를 다음 노드로 링크
	}
	printf("No key in Nodes\n");	//입력받은 키가 없다면 키가 없음 출력
	return 0;
}

// list의 마지막 노드 삭제
int deleteLast(headNode* h) {
	if(h->first == NULL){			//헤드노드가 비어있다면
		printf("No Node\n");		//노드 없음 출력
		return 0;
	}
	listNode* n = h->first;			//현재노드와 이전노드를 헤드노드와 같은 노드로 설정
	listNode* m = h->first;
	while (n->link != NULL) {		//현재노드의 다음노드가 비어있을때까지 반복
		m = n;										//이전노드를 현재 노드로 설정 후
		n = n->link;							//현재노드를 다음노드로 변경
	}
	m->link = NULL;							//이전노드의 링크를 NULL로 설정 후
	free(n);										//현재노드 제거
	return 0;
}


// 리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) {

	if(h->first == NULL){		//헤드노드가 비어있다면
		printf("No Node\n");	//노드없음 출력
		return 0;
	}

	listNode* n = h->first;	//다음노드
	listNode* m = NULL;			//현재노드
	listNode* l;						//이전노드

	while (n != NULL) {			//다음노드가 비어있을 때까지 반복
		l = m;								//이전 노드를 현재노드와 동일하게 변경
		m = n;								//현재 노드를 다음노드와 동일하게 변경
		n = n->link;					//다음 노드를 그 다음노드로 변경 후
		m->link = l;					//현재 노드를 이전노드로 링크
	}

	h->first = m;						//반복이 다 끝난 후 헤드노드를 현재노드로 설정
	return 0;
}

//리스트 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;
	printf("\n---PRINT\n");
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}
	p = h->first;
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}
	printf("  items = %d\n", i);
}
