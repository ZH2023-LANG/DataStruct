#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100       // 栈最大容量
typedef int ElemType;     // 栈中元素类型，这里用 int

// ========== 栈结构定义 ==========
// data: 动态数组，用来存放栈元素
// top : 栈顶指针（下标），初始为 -1 表示空栈
typedef struct {
    ElemType *data;
    int top;
} Stack;

// ========== token 类型枚举 ==========
// 用来区分读到的是数字还是运算符等
typedef enum {
    LEFT_PARE, RIGHT_PARE,        // 左右括号（此程序没用到，但保留）
    ADD, SUB, MUL, DIV, MOD,      // + - * / %
    EOS, NUM                      // EOS 表示结束（'\0'），NUM 表示数字
} contentType;

// 这里是“后缀表达式(逆波兰式)”
// 表达式：8 2 / 2 + 5 6 * -
// 对应中缀大概是：((8/2)+2) - (5*6)
char expr[] = "82/2+56*-";

// ========== 初始化栈 ==========
// 申请 Stack 结构体空间 + data 数组空间
Stack* initStack() {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) return NULL;   // 申请失败返回 NULL

    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    if (s->data == NULL) {
        free(s);                  // data 申请失败，要释放 s
        return NULL;
    }

    s->top = -1;                  // top=-1 表示空栈
    return s;
}

// ========== 判空 ==========
// top == -1 说明栈为空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// ========== 入栈 ==========
// 入栈前先检查是否满栈
int push(Stack *s, ElemType e) {
    if (s->top >= MAXSIZE - 1) {  // top 超过最大下标说明满了
        printf("满了\n");
        return 0;
    }
    s->top++;                     // 栈顶指针上移
    s->data[s->top] = e;          // 存入数据
    return 1;
}

// ========== 出栈 ==========
// 弹出栈顶元素：把栈顶元素赋值给 *e，然后 top--
int pop(Stack *s, ElemType *e) {
    if (s->top == -1) {           // top=-1 表示空栈
        printf("空的\n");
        return 0;
    }
    *e = s->data[s->top];         // 取出栈顶元素
    s->top--;                     // 栈顶指针下移
    return 1;
}

// ========== 获取栈顶元素（不弹出）==========
int getTop(Stack *s, ElemType *e) {
    if (s->top == -1) {
        printf("空的\n");
        return 0;
    }
    *e = s->data[s->top];         // 只读取，不修改 top
    return 1;
}

// ========== 取 token：读取表达式中的一个字符并判断类型 ==========
// symbol: 输出当前读到的字符
// index : 输入/输出参数，表示当前读取位置，每次读完 index++
contentType getToken(char *symbol, int *index) {
    *symbol = expr[*index];       // 取当前字符
    *index = *index + 1;          // index 后移（指向下一个字符）

    // 判断读到的字符是什么类型
    switch (*symbol) {
        case '(': return LEFT_PARE;
        case ')': return RIGHT_PARE;
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '%': return MOD;
        case '\0': return EOS;    // 字符串结尾
        default:  return NUM;     // 默认认为是数字字符（0~9）
    }
}

// ========== 计算后缀表达式 ==========
// 后缀表达式规则：
// - 遇到数字：入栈
// - 遇到运算符：弹出两个数 op1, op2，计算 op1 (op) op2，再压回栈
int eval(Stack *s) {
    char symbol;                  // 当前读到的字符
    int op1, op2;                 // 用于保存两个操作数
    int index = 0;                // expr 字符串扫描下标
    contentType token;            // 当前 token 类型
    ElemType result;              // 最终结果

    token = getToken(&symbol, &index);   // 读取第一个 token

    while (token != EOS) {        // 直到遇到字符串结束符 '\0'
        if (token == NUM) {
            // 这里仅支持单个数字字符，例如 '8'
            // '8' - '0' = 8
            push(s, symbol - '0');
        } else {
            // 遇到运算符：需要弹出两个操作数
            // 注意：后缀表达式的顺序是：
            //   op1 op2 运算符
            // 所以栈弹出顺序是：
            //   第一次 pop 出来的是 op2
            //   第二次 pop 出来的是 op1
            pop(s, &op2);
            pop(s, &op1);

            // 根据运算符计算，然后把结果入栈
            switch (token) {
                case ADD: push(s, op1 + op2); break;
                case SUB: push(s, op1 - op2); break;
                case MUL: push(s, op1 * op2); break;
                case DIV: push(s, op1 / op2); break;  // 注意这里没做除0判断
                case MOD: push(s, op1 % op2); break;
                default: break;
            }
        }

        // 继续读取下一个 token
        token = getToken(&symbol, &index);
    }

    // 表达式扫描完，栈顶就是最终结果
    pop(s, &result);
    printf("result = %d\n", result);
    return result;
}

int main() {
    // 初始化栈
    Stack *s = initStack();
    if (s == NULL) {
        printf("initStack failed\n");
        return 1;
    }

    // 计算后缀表达式
    eval(s);

    // 释放内存，防止内存泄漏
    free(s->data);
    free(s);
    return 0;
}