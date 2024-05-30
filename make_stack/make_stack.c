#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5


typedef int element;

typedef struct Stack {
    element data[MAX_STACK_SIZE];
    int top;
} Stack;

void error(char *msg)   //에러 출력 함수
{
    fprintf(stderr, "%s 오류입니다. ", msg);
    exit(1);
}

void init(Stack *s) //스택 초기화 함수
{
    s->top = -1;
}

int is_full(Stack *s)   //스택 포화 상태 검출
{
    return s->top == (MAX_STACK_SIZE - 1);
}

int is_empty(Stack *s)  //스택 공백 상태 검출
{
    return (s->top == -1);
}

void push(Stack *s, element value)  //스택에 value push
{
    if(is_full(s))
        error("스택 포화 상태이므로 push 불가능");
    
    s->data[++(s->top)] = value;
}

element pop(Stack *s)   //스택에 있는 최신 요소를 pop하는 함수
{
    if(is_empty(s))
        error("스택 공백 상태이므로 pop 불가능");
    
    return s->data[(s->top)--];
}

element peek(Stack *s)  //스택에 있는 최신 요소를 peek 하는 함수
{
    if(is_empty(s))
        error("스택 공백 상태이므로 peek 불가능");
    
    return s->data[(s->top)];
}

int main()
{
    Stack s;
    init(&s);   //스택 초기화
    for (int i=0; i<MAX_STACK_SIZE; i++)
    {
        printf("스택에 %d push 하겠습니다. \n", i);
        push(&s, i);
    }
    
    while(!is_empty(&s))
    {
        printf("스택 pop 하겠습니다\n");
        printf("pop된 요소 : %d\n", pop(&s));
    }
    

}