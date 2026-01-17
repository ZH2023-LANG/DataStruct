#include <stdio.h>
int main(){
    int a; //声明一个整型变量
    int *p; //声明一个指针变量，该指针指向一个int类型值的内存地址
    a=5;
    p=&a;
    printf("a的地址为:%p,a的值为:%d\n",&a,a);
    printf("p的地址为:%p,p的值为:%p\n",&p,p);
}