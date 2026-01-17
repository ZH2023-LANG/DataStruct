#include <stdio.h>
int main(){
    int a[]={1,2,3,4,5};
    int *p;
    p=a;

    printf("%p\n",a);
    printf("%p\n",p);
    printf("%d\n",*p);
}