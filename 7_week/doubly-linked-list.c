#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

// initailize는 매개변수를 이중포인터로
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main(){
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("-------------------[SeoBeomsu][2019019014]----------------------\n");
		printf("                     Doubly Linked  List                        \n");
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


int initialize(headNode** h) {	//이중포인터로 받아 직접 값을 바꿈
	if(*h != NULL)								//비어있지 않다면
		freeList(*h);						  	//노드 제거

	*h = (headNode*)malloc(sizeof(headNode));	//헤드노드 크기로 메모리 할당
	(*h)->first = NULL;						          	//첫 헤드는 NULL로 설정
	return 1;								                	//노드를 리턴하면 단일포인터로 받을 수 있다.
}

int freeList(headNode* h){
	listNode* p = h->first;		//현재노드 p를 헤드로 설정

	listNode* prev = NULL;		//이전노드를 NULL로 설정
	while(p != NULL) {	  		//현재노드가 비어있다면
		prev = p;			        	//이전노드를 현재노드로 바꾸고
		p = p->rlink;	       		//현재노드를 다음노드으로 바꾸고
		free(prev);			      	//이전노드 해제
	}
	free(h);				        	//마지막으로 헤드노드도 메모리해제

	return 0;
}


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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}


//list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드생성
	listNode* p = h->first;			//임시노드 p

	node->key = key;			    	//생성한 노드에 값 입력
	node->rlink = NULL;			  	//노드의 다음링크를 NULL로 지정
	node->llink = NULL;			  	//노드의 전링크를 NULL로 지정
	
	if(h->first == NULL){		  	//헤드노드가 비어있다면
		h->first = node;		    	//헤드노드를 새로 생성한 노드로 설정
		return 0;
	}

	while(p->rlink != NULL) {		//현재노드의 다음링크가 NULL이 될때까지 반복
		p = p->rlink;			      	//현재노드는 다음노드로 변경
	}
	
	p->rlink = node;		    		//현재노드의 다음노드를 생성한노드로
	node->llink = p;			    	//생성한노드의 전링크가 현재노드가 되게 설정

	return 0;
}

// list의 마지막 노드삭제
int deleteLast(headNode* h) {

	if(h->first == NULL){			//헤드노드가 비어있다면
		printf("No Nodes!\n");	//헤드노드를 새로 생성한 노드로 설정
		return 0;
	}
	listNode* p = h->first;		//현재노드

	if (p->rlink == NULL) {		//헤드였던 노드의 다음노드가 비어있다면
		h->first = NULL;			  //헤드가 노드가 되게 설정
	}

	while (p->rlink != NULL){	//현재노드의 다음링크가 NULL이 될때까지 반복
		p = p->rlink;		      	//현재노드는 다음노드로 변경
	}

	p->llink->rlink = NULL;		//현재노드의 이전노드의 다음링크를 NULL 로 지정
	free(p);						      //현재노드인 p 해제

	return 0;
}


// list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드 생성
	node->key = key;				//노드에 값 입력
	node->rlink = NULL;			//노드의 다음링크를 NULL로 지정
	node->llink = NULL;			//노드의 전링크를 NULL로 지정

	if(h->first == NULL){		//헤드가 비어있다면
		h->first = node;			//새로 생성한 노드가 헤드가 되게 설정
		return 0;
	}else{							    //헤드가 비어있지 않다면
		node->rlink = h->first; //생성한 노드의 다음링크를 헤드였던 노드를 지정
		h->first->llink = node; //헤드였던 노드의 전링크를 새로 생성한 노드로 지정
		h->first = node;		  //생성한 노드가 헤드가 되게 설정
		return 0;
	}
	
	return 0;
}

// list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {
	if (h->first == NULL) {			//헤드노드가 비어있다면
		printf("No Nodes!\n");		//노드없음 출력
		return 0;
	}
	

	listNode* p = h->first;			//임시노드 p 생성

	
	if (p->rlink != NULL) {			//현재노드의 다음링크가 NULL이 아니라면
		h->first = p->rlink;	  	//헤드를 현재노드의 다음링크로 설정
		p->rlink->llink = NULL;		//현재노드의 다음링크의 전 링크를 NULL로 설정
	}else{							        //현재노드의 다음링크가 NULL이라면
		h->first = NULL;			    //헤드가 NULL을 향하게 설정
	}
	
	free(p);					        	//노드 p 해제

	return 0;
}

// 리스트의 링크를 역순으로 재배치
int invertList(headNode* h) {
	if(h->first == NULL){		//헤드노드가 비어있다면
		printf("No Node\n");	
		return 0;
	}

	listNode* p = h->first;	//다음노드
	listNode* m = NULL;		  //중간노드
	listNode* l;				    //이전노드

	while (p != NULL) {			//다음노드가 비어있을 때까지 반복
		l = m;		      			//이전 노드를 중간노드로 설정
		m = p;				      	//중간 노드를 다음노드로 설정
		p = p->rlink;		    	//다음 노드를 그 다음노드로 이동
		m->rlink = l;			    //중간노드의 다음링크를 이전노드로 변경
		m->llink = p;		    	//중간노드의 전 링크를 다음노드로 변경
	}

	h->first = m;				    //반복이 다 끝난 후 헤드노드를 현재노드로 설정


	return 0;
} 



// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드 생성
	node->key = key;		  //노드의 값 입력
	node->llink = NULL;		//노드의 전링크를 NULL로 설정
	node->rlink = NULL;		//노드의 다음링크를 NULL로 설정

	if(h->first == NULL){	//헤드노드가 비어있다면
		h->first = node;  	//헤드노드를 방금 생성한 노드로 설정
		return 0;
	}
	
	listNode* p = h->first;			//다음노드
	listNode* m = h->first;			//이전노드

	while (p != NULL) {
		if(key <= p->key){			  //key의 값이 현재 노드의 값보다 작다면
			if(p == h->first){	  	//헤드의 첫 노드의 key값이 입력받은 key의 값보다 작다면
				h->first = node;	    //헤드를 새로 생성한 노드로 연결 후
				node->rlink = p;	    //생성한 노드의 다음 링크로 원래 있던 노드로 연결
			}else{					        //그 외에 경우
				node->rlink = p;	    //생성한 노드의 다음링크를 현재노드로 설정
				node->llink = m;    	//생성한 노드의 전링크를 이전 노드로 설정
				p->llink = node;
				m->rlink = node;	    //현재 위치 이전에 있던 노드를 새로 생성한 노드로 링크되게 끔 설정한다.
			}
			return 0;
		}
		m = p;					        	//전 노드에 현재노드를 넣고
		p = p->rlink;			      	//현재노드는 그 다음노드로 이동
	}
	
m->rlink = node;				    	//이전노드의 다음링크를 생성한 노드로 설정
node->llink = m;				  	//생성한 노드의 전 링크를 이전노드로 설정

	return 0;
}


// list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {
	if(h->first == NULL){		//헤드노드가 비어있다면
		printf("No Node\n");	//노드가 없다고 출력 후 함수 종료
		return 0;
	}
	
	listNode* p = h->first;	//임시노드 p,m 생성
	listNode* m = h->first;

	while (p != NULL) {						    //p가 널이 될때까지 반복
		if (key == p->key) {				    //현재 노드의 값이 입력받은 값과 같을 때
			if (p == h->first) {		      //현재노드가 첫 노드일 때
				h->first = p->rlink;	    	//헤드를 현재노드의 다음노드로 지정
			}else if (p->rlink == NULL) {	//현재노드의 다음이 NULL일 때 
				m->rlink = NULL;		      	//전 노드의 다음노드를 NULL로 지정
			}else {							          //중간 일때
				m->rlink = p->rlink;	    	//전 노드의 다음링크를 다음노드로 지정
				p->rlink->llink = m;	    	//다음노드의 전링크를 전 노드로 지정
			}
			free(p);						          //노드 p를 해제
			return 0;
		}
		m = p;					//m을 현재노드로 설정 후
		p = p->rlink;		//p를 다음노드로 설정
	}
	printf("No key in Nodes\n");	//모두 끝나고 아무것도 없을 때 출력

	return 1;
}