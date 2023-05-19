#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("------------[      [SeoBeomSu] [2019019014]      ]-----------\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	if (h == h->rlink){		//헤드밖에 없다면
		free(h);			//헤드 메모리 해제
		return 0;
	}
	
	listNode *p = h->rlink;	//위치 변환을 위한 노드
	listNode *q;			//메모리 해제를 위한 노드

	while (p->rlink != h) {
		q = p;				//각 노드를 이동시켜가며 메모리 해제
		p = p->rlink;
		free(q);
	}
	free(p);	//마지막 노드인 헤드까지 메모리 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	if (h == NULL) {		//헤드가 비어있다면
		printf("No Nodes!\n");	//오류 출력
		return -1;
	}

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	
	if (h->rlink == h) {			//헤드밖에 없다면
		h->rlink = node;			//헤드와 새로 만든 노드를 서로 연결
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}else{							//아니라면
		node->llink = h->llink;		//헤드의 왼쪽에 새로만든 노드를 연결
		node->rlink = h;
		h->llink->rlink = node;
		h ->llink = node;
	}
	

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h->rlink == h||h == NULL) {	//헤드밖에 없거나 헤드가 없다면
		printf("No Nodes!\n");		//노드가 없다고 출력
		return -1;
	}

	listNode *p = h->llink;

	p->llink->rlink = h;		//헤드의 왼쪽의 왼쪽노드를 헤드의 왼쪽에 연결
	h->llink = p->llink;

	free(p);					//헤드의 원래 왼쪽에 있던 노드는 메모리 해제


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	if (h == NULL) {					//헤드가 없다면 노드가 없다고 출력
		printf("No Nodes!\n");
		return -1;
	}
	
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->rlink == h) {	//헤드밖에 없다면
		h->rlink = node;	//헤드와 새로 생성한 노드를 연결
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}else{							//그게 아니라면
		h->rlink->llink = node;		//헤드와 앞 노드 사이에 입력 후
		node->rlink = h->rlink;		//링크 연결
		h->rlink = node;
		node->llink = h;
	}
	

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h->rlink == h||h == NULL) {	//헤드만 있거나 아무것도 없을 때
		printf("No Nodes!\n");		//노드가 없다고 출력
		return -1;
	}else{							//아니라면
		listNode *p = h->rlink;		//헤드를 다음다음 노드와 연결 후
		h->rlink = p->rlink;		//그 사이에 있던 노드 메모리 해제
		p->rlink->llink = h;
		free(p);
	}

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if (h == NULL) {				//헤드가 없다면 노드가 없다고 출력
		printf("No Nodes!\n");
		return -1;
	}
	
	listNode *p = h->rlink;	//다음노드
	listNode *n = h;		//이전노드
	listNode *m = h;		//현재노드

	h->llink = h->rlink; 	//헤드의 우측노드를 왼쪽으로 이동시킴

	while (p != h) {		//헤드가 나올 때까지
		n = m;				//역순으로 이동되어 현재 노드에서 끊어진 노드
		m = p;				//역순으로 이동시킬 노드
		p = p->rlink;		//이후에 붙일 노드
		m->rlink = n;		//좌우 링크를 바꿔줌
		m->llink = p;
	}

	h->rlink = m;		//헤드가 나오면 헤드의 우측링크를 마지막 노드와 연결

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h == NULL) {				//헤드가 없다면 노드가 없다고 출력
		printf("No Nodes!\n");
		return -1;
	}

	if (h->rlink == h) {		//헤드만 있다면 헤드와 새로만든 노드와 연결
		insertFirst(h,key);
		return 0;
	}

	listNode *p = h->rlink;

	while (p != h) {		//헤드가 나올 떄까지
		if (key <= p->key) {		//입력받은 값이 현재 값보다 작다면
			if (p == h->rlink){		//그 중 현재노드가 헤드 다음 노드라면
				insertFirst(h,key);	//헤드와 현재노드 사이에 새로만든 노드 입력
				return 0;
			}else{					//그 외의 경우
				p->llink->rlink = node;		//현재노드와 그 이전노드 사이에 새로만든 노드 입력
				node->llink = p->llink;		//후 좌우링크 연결
				p->llink = node;
				node->rlink = p;
				return 0;
			}
			
		}
		p = p->rlink;		//다음노드로 이동
	}

	insertLast(h,key);		//마지막까지 이동 된 경우 마지막에 입력

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if(h->rlink == h||h == NULL){		//헤드가 없거나 헤드만 있는경우
		printf("No Nodes!\n");			//노드가 없다고 출력
		return 0;
	}

	listNode *p = h->rlink;

	while (p != h){				//현재노드가 헤드가 될때까지
		if (p->key == key) {		//입력받은 값과 현재 값이 같을 경우
			if (p == h->rlink) {	//그 중에서도 현재노드가 헤드 다음 노드일 경우
				deleteFirst(h);		//첫 노드 삭제 함수 이용
				return 0;
			}else{					//그 외의 경우
				p->llink->rlink = p->rlink;	//현재노드의 좌우 링크를 연결시켜준 후
				p->rlink->llink = p->llink;
				free(p);		//현재노드 메모리 해제
				return 0;
			}
			
		}
		p = p->rlink;		//다음노드로 이동
	}
	
	printf("No key in Nodes!\n");		//마지막까지 찾지 못했다면 해당노드가 없다고 출력

	return 0;
}