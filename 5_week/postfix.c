#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */
int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */
int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main(){
	char command;
	do{
    printf("\n-------------------[SeoBeomsu][2019019014]-------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	return 1;
}

void postfixPush(char x){
    postfixStack[++postfixStackTop] = x;
}

char postfixPop(){
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x){
    evalStack[++evalStackTop] = x;
}

int evalPop(){
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix(){
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol){
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x){
	return getToken(x);
}

void charCat(char* c){ // 문자하나를 전달받아 postfixExp에 추가
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void toPostfix() { // stack을 이용하여 infixExp의 문자를 postfix로 변경, 변경하고 postfix의 내용을 postfixExp에 저장
	char *exp = infixExp; // infixExp의 문자 하나씩을 읽기위한 포인터
	char x; // 문자하나 임시저장하는 변수
	// exp를 증가시켜가면서, 문자를 읽고 postfix로 변경
	while(*exp != '\0') {       // 빈칸이 아니면 반복
		if(getPriority(*exp) == operand) {      // 현재 문자가 피연산자면
			x = *exp;       		// x에 입력 후
        	charCat(&x);    // postfixexp에 입력
		}
        else if(getPriority(*exp) == lparen) {  // 피연산자가 아니고 '('라면
        	postfixPush(*exp);      // postfixStack에 연산자 입력
        }
        else if(getPriority(*exp) == rparen) {  // 현재 문자가 ')'라면
        	while((x = postfixPop()) != '(') {  // postfixStack에서'('가 나올때 까지
        		charCat(&x);                    // postfixexp에 입력
        	}
        }
        else {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {// '('이후 postifsStack에 넣었던 연산자와 현재 문자 중 우선순위를 비교해서 이미 들어가 있는것이 우선순위가 높다면
            	x = postfixPop();   	// x에 이미 들어가 있던 연산자를 넣고
            	charCat(&x);       	 	// 그 연산자를 postfixexp에 넣음
            }                       // 현재 문자의 우선순위가 높을떄까지 반복한 후
            postfixPush(*exp);      // 현재 문자의 우선순위가 높아지면 postfixStack에 현재 문자를 넣음
        }
        exp++;      						    //다음 문자를 받기위해 자리이동
	}                  							  //모든 과정이 끝난 후
    while(postfixStackTop != -1) {  //postfixStack에 문자가 남아있다면
    	x = postfixPop();             //맨위에 있는 문자를 postfixStack에서 빼와서
    	charCat(&x);                  //postfixexp에 넣음
    }
}

void debug(){
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++){
		printf("%c  ", postfixStack[i]);
	}
	printf("\n");
}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';
	for(int i = 0; i < MAX_STACK_SIZE; i++){
		postfixStack[i] = '\0';
	}
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() {
    char *exp = postfixExp; //postfix 형식을 바꾼 식을 받는다.
    int x, y;
    while(*exp != '\0') {   //빈칸이 아니면 반복
		if(getPriority(*exp) == operand) {  //현재 문자가 연산자가 아닌 경우
			evalPush(*exp - '0');           //evalStack에 저장
		}                                   //'0'을 빼주는 이유는 유니코드 형식의 숫자에서 '0'을 빼면 해당 숫자가 정수로 나오기 때문
      else {
        x = evalPop();      //x와 y에 evalStack에 저장했던 숫자를 입력
        y = evalPop();
        switch(*exp){       //연산자에 대해서 각연산자 계산을한다.
          case '+' : 
            evalPush(y + x);    //x, y 순서가 아닌 y, x인 이유는
            break;              //evalStack에서 꺼내는 순서가 반대로 되었기 때문이다.
          case '-' :
            evalPush(y - x);    //evalPush를 하는 이유는 계산을 한 후
            break;;             //그 숫자에 대해서 다시 연산을 하기 때문
          case '/' :
            evalPush(y / x);
          	break;
          case '*' :
            evalPush(y * x);
            break;
          default:
            break;
        }
      }
    exp++;      //다음 문자를 확인
	}                               //*exp가 빈칸일 경우 반복문을 끝내고
  evalResult = evalPop(*exp);     //결과에 계산한 값을 대입
}
