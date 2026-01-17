#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct 
{
    ElemType *data;
    int top;
}Stack;

typedef enum{
    LEFT_PARE,RIGHT_PARE,
    ADD,SUB,MUL,DIV,MOD,
    EOS,NUM
}contentType;

char expr[]="x/(i-j)*y";

Stack* initStack(){
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    s->top=-1;
    return s;
}

int isEmpty(Stack *s){
    return s->top==-1;
}

int push(Stack *s,ElemType e){
    if(s->top>=MAXSIZE-1){
        printf("满了\n");
        return 0;
    }
    s->top++;
    s->data[s->top]=e;
    return 1;
}

int pop(Stack *s,ElemType *e){
    if(s->top==-1){
        printf("空的\n");
        return 0;
    }
    *e=s->data[s->top];
    s->top--;
    return 1;
}

int getTop(Stack *s,ElemType *e){
    if(s->top==-1){
        printf("空的\n");
        return 0;
    }
    *e=s->data[s->top];
    return 1;
}

contentType getToken(char *symbol,int *index){
    *symbol=expr[*index];
    *index=*index+1;
    switch (*symbol)
    {
    case '(':return LEFT_PARE;
    case ')':return RIGHT_PARE;
    case '+':return ADD;
    case '-':return SUB;
    case '*':return MUL;
    case '/':return DIV;
    case '%':return MOD;
    case '\0':return EOS;
    default:return NUM;
    }
}

int print_token(contentType token){
    switch (token)
    {
    case ADD:
        printf("+");
        break;
    case SUB:
        printf("-");
        break;
    case MUL:
        printf("*");
        break;
    case DIV:
        printf("/");
        break;
    case MOD:
        printf("%%");
        break;
    default:
        return 0;
    }
    return 1;
}

void postfix(Stack *s){
    int in_stack[]={0,19,12,12,13,13,13,0};
    int out_stack[]={20,19,12,12,13,13,13,0};
    contentType token;
    int index=0;
    char symbol;
    ElemType e;
    s->data[0]=EOS;
    s->top=0;
    token=getToken(&symbol,&index);
    while (token!=EOS)
    {
        if(token==NUM){
            printf("%c",symbol);
        }
        else if (token == RIGHT_PARE){
            while (s->data[s->top]!=LEFT_PARE)
            {
                pop(s,&e);
                print_token((contentType)e);
            }
            pop(s,&e);
        }
        else{
            while (in_stack[s->data[s->top]]>=out_stack[token])
            {
                pop(s,&e);
                print_token((contentType)e);
            }
            push(s,token);
        }
        token=getToken(&symbol,&index);
    }
    while (!isEmpty(s)&&s->data[s->top]!=EOS)
    {
        pop(s,&e);
        print_token((contentType)e);
    }
    printf("\n");
}


int main(){
    Stack *s=initStack();
    printf("中缀表达式：%s\n",expr);
    printf("后缀表达式:");
    postfix(s);
    free(s->data);
    free(s);
}





















