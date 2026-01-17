#include <stdio.h>
int main(){
    int a=5;
    int *p=&a;
    printf("%d\n",*p);
    *p=100;
    printf("%d\n",a);
}