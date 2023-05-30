#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */
/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);
void printStack();

int main(){
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------[      [SeoBeomSu] [2019019014]      ]----------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		case 'p': case 'P':
			printStack();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // 이진트리 초기화
	// 트리가 비어있지않다면 트리의 연결된 모든 노드를 삭제한다
		if(*h != NULL)
		freeBST(*h);

	// head node 만들기
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// 루트
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;
	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr){
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

//textbook: p 224
void iterativeInorder(Node* node){
	for(;;){
		for(; node; node = node->left) //노드의 왼쪽으로 이동하면서 노드 저장
			push(node);
		node = pop(); // 노드를 입력받는다

		if(!node) break; // 노드가없다면 반복분 멈춤
		printf(" [%d] ", node->key); // 노드의 값을 출력

		node = node->right; // 노드의 우측으로 이동
	}
}

//textbook: p 225
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; // 노드가 없으면 함수종료 

	enQueue(ptr); // 노드를 큐에입력
	for(;;){
		ptr = deQueue(); // 큐에서 제일먼저 입력한 노드를 빼냄
		if(ptr) { // 노드가있다면
			printf(" [%d] ", ptr->key); // 노드의 값을 출력

			if(ptr->left) // 왼쪽노드가 있으면
				enQueue(ptr->left); // 왼쪽노드를 큐에 입력
			if(ptr->right) // 오른쪽 노드가 있으면
				enQueue(ptr->right); // 오른쪽 노드를 큐에입력
		}
		else // 노드가 없으면 반복 종료
			break;
	}
}

int insert(Node* head, int key){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	// head->left is the root 
	Node* ptr = head->left;
	Node* parentNode = NULL;
	while(ptr != NULL) {

		// if there is a node for the key, then just return
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key){
	if (head == NULL || head->left == NULL ) { // 헤드가없거나 노드가없으면 
		printf("\n Nothing to delete!!\n"); // 노드없다고 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; // 현재노드
	Node* parent = NULL; // 부모요소 저장공간
	Node* ptr = root; // 루트노드

	while((ptr != NULL)&&(ptr->key != key)) { // ptr이 값이있고 ptr의 key값과 다르면
		if(ptr->key != key) {
			parent = ptr;	// 부모노드 저장
			if(ptr->key > key) // ptr의 키값이 지금의 key값보다 크다면
				ptr = ptr->left; // ptr 왼쪽으로 이동
			else
				ptr = ptr->right; // ptr 오른쪽으로 이동
		}
	}

	// key값을 가지는 node가 존재하지 않을경우
	if(ptr == NULL){ // ptr에 값이존재하지 않으면
		printf("No node for key [%d]\n ", key); // node가 존재하지않는다고 출력
		return -1;
	}

	// case 1: the node which has to be removed is a leaf node
	if(ptr->left == NULL && ptr->right == NULL){ // ptr이 left, right 둘다없을때, 즉 리프노드일때
		if(parent != NULL) { // 부모요소가 존재할때
			if(parent->left == ptr) // ptr이 부모요소의 left라면
				parent->left = NULL; // left 초기화
			else	// ptr이 부모요소의 right라면
				parent->right = NULL; // right 초기화
		} else { // 부모요소가 NULL이면 root노드이므로 
			head->left = NULL; // 헤드를 초기화
		}
		free(ptr);
		return 1;
	}

	// if the node to be deleted has one child
	if ((ptr->left == NULL || ptr->right == NULL)){ // 둘중 하나가 비어있을경우
		Node* child;
		if (ptr->left != NULL) //ptr의 left가 존재하면
			child = ptr->left; // ptr의 left 내용을 child에 저장
		else // ptr의 right가 존재하면
			child = ptr->right; // ptr의 left 내용을 child에 저장

		if(parent != NULL){ // 부모노드가 존재할경우
			if(parent->left == ptr) // 부모의 왼쪽과 ptr이 일치할경우
				parent->left = child; // 왼쪽에 자식노드 연결
			else
				parent->right = child; // 아니면 오른쪽에 자식노드 연결
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			// 만약 부모가 NULL일경우
			root = child; // child는 root로 연결
		}

		free(ptr); // ptr 반환
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr; // ptr은 부모요소
	candidate = ptr->right; // ptr의 오른쪽노드 candidate 저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL){ // candidate의 왼쪽노드가 NULL이 아닐경우
		parent = candidate; // candidate를 parent로 올린다
		candidate = candidate->left; // candidated의 left를 candidate로 올린다.
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // 만약 parent의 right가 candidate일경우
		parent->right = candidate->right; // candidate의 right를 parent의 right에 저장
	else
		parent->left = candidate->right; // 아닐경우 candidate의 오른쪽을 parent의 왼쪽에 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // candidate의 key를 ptr key로 저장

	free(candidate); // candidate해제
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop(){
	if (top < 0) return NULL; //top이 0보다 작으면 NULL 반환
	return stack[top--]; //스택의 최근값을 반환 후 top의 값 1 감소
}

void push(Node* aNode){
	stack[++top] = aNode; //top에 1을 더하고 스택에 입력받은 노드 입력
}


void printStack(){
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top){ // 0부터 현재 스택에있는 값들 출력
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue(){
	if (front == rear) { // front와 rear가 같다면 NULL 반환
		printf("\n....Now Queue is empty!!\n" ); // Queue가 비었다고 출력
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // front에 front를 최대 큐 크기로 나눈 나머지를 입력
	return queue[front]; // 큐의 맨 처음값을 반환후 front값 1 증가
}

void enQueue(Node* aNode){
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear에 1을 더한값을 최대큐크기로 나눈값
	if (front == rear) { // rear와 front가 같다면
		printf("\n....Now Queue is full!!\n"); // 큐에 남은공간이없다고 출력
		return;
	}
	queue[rear] = aNode; // rear위치에있는 큐값 반환
}




