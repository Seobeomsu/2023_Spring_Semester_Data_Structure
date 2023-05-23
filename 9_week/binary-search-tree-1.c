#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

int main(){
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------[      [SeoBeomSu] [2019019014]      ]----------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) { // 현재노드가 NULL이 아니면
		inorderTraversal(ptr->left);  // 맨 왼쪽으로가서 출력
		printf(" [%d] ", ptr->key);   // 맨왼쪽에서 한개씩 올라가며 출력
		inorderTraversal(ptr->right); // 한칸 올라갈때마다 오른쪽 노드에 있으면 출력
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) { // 현재노드가 NULL이 아니면
		printf(" [%d] ", ptr->key);     // 노드를 출력하면서
		preorderTraversal(ptr->left);   // 맨왼쪽으로 이동
		preorderTraversal(ptr->right);  // 왼쪽노드가 없으면 오른쪽노드가 있으면 출력
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) { // 현재노드가 NULL이 아니면
		postorderTraversal(ptr->left);    // 맨왼쪽으로 이동
		postorderTraversal(ptr->right);   // 왼쪽노드가 없으면 오른쪽으로 이동
		printf(" [%d] ", ptr->key);       // 오른쪽노드도 없으면 출력
	}
}


int insert(Node* head, int key){
	Node* newNode = (Node*)malloc(sizeof(Node));  // 노드생성
	newNode->key = key;       // 값입력
	newNode->left = NULL;     // 좌우 링크를 NULL로 설정
	newNode->right = NULL;

	if (head->left == NULL) { // 노드가 하나도 없다면
		head->left = newNode;   // 노드를 헤드와 연결
		return 1;
	}


	Node* ptr = head->left;   // 이동용 노드
	Node* parentNode = NULL;  // 값확인용 노드
  
	while(ptr != NULL) {  // 노드가 없을때까지

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // 키가있다면 값이있다고 출력 

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;   // 현재노드를 부모노드로 설정

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  // 입력받은값이 크면
			ptr = ptr->right; // 오른쪽으로 이동
		else
			ptr = ptr->left;  // 작을때 왼쪽으로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)       // 부모노드의 입력값과 비교함
		parentNode->left = newNode;   // 작으면 좌측노드 연결
	else
		parentNode->right = newNode;  // 크면 우측노드 연결
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL || head->left == NULL ) { // 헤드가없거나 노드가없으면
		printf("\n Nothing to delete!!\n"); // 노드없음 출력
		return -1;
	}

	Node* ptr = head->left;  // 현재노드
	Node* parentNode = head; // 현재노드의 부모노드

	while(ptr != NULL) { // 노드가 비어있을때까지

		if(ptr->key == key) { // 현재노드의값이 입력받은값과 같으면
			if(ptr->left == NULL && ptr->right == NULL) { // 노드의 좌우가 비어있다면

				/* root node case */
				if(parentNode == head)  // 현재의 부모노드가 헤드면
					head->left = NULL;    // 헤드에 NULL 입력

				/* left node case or right case*/
				if(parentNode->left == ptr) // 부모노드를 기준
					parentNode->left = NULL;  // 좌측에있으면 좌측을 NULL로 연결
				else
					parentNode->right = NULL; // 우측에있으면 우측을 NULL로 연결
				
        free(ptr); // 현재노드 초기화
			} else { // 비어있지 않을경우
				printf("the node [%d] is not a leaf \n", ptr->key);  // leaf 노드가 아니라고 출력
			}
			return 1;
		}
		/* keep the parent node */
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

	printf("Cannot find the node for key [%d]\n ", key); // 비교하고 같은값이없으면 키가 없다고 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key){
	if(ptr == NULL) // 현재노드가 비어있으면
		return NULL;  // NULL 반환

	if(ptr->key < key)  // 현재 노드의 값과 입력받은 값을 비교함
		ptr = searchRecursive(ptr->right, key); // 입력값이 크면 우측노드 이동
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);  // 입력값이 작으면 좌측노드 이동

	/* if ptr->key == key */
	return ptr; // 현재노드의 입력받은값이 같다면 현재노드 반환

}

Node* searchIterative(Node* head, int key){
	/* root node */
	Node* ptr = head->left; 

	while(ptr != NULL){ // 현재노드가 없을때까지 반복
		if(ptr->key == key) // 현재값과 입력값이같으면 
			return ptr;       // 현재노드 반환

		if(ptr->key < key){
      ptr = ptr->right; // 현재값과 비교해서 작다면 우측노드로 이동
    }else{
      ptr = ptr->left;  // 크다면 좌측노드로이동
    }  
	}

	return NULL;  // 그외에 입력받은 값을 못찾으면 NULL 반환
}

void freeNode(Node* ptr){
	if(ptr) { // 현재노드가 존재할때
		freeNode(ptr->left);  // 좌측으로 가서 반복
		freeNode(ptr->right); // 우측으로 가서 반복
		free(ptr);  // 현재 노드 메모리 반환
	}
}

int freeBST(Node* head){

	if(head->left == head){ // 헤드에 연결된 노드가있다면
		free(head); // 헤드의 메모리반환
		return 1;
	}

	Node* p = head->left; // 헤드의 다음노드를 임시노드로 설정

	freeNode(p);  // 헤드에 연결된 모든노드의 메모리반환
	free(head);   // 헤드 반환
	return 1;
}