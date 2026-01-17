#include <stdio.h>
void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
    printf("a=%d,b=%d\n",*a,*b);
}
int main(){
    int m=5;
    int n=6;
    swap(&m,&n);
    printf("m=%d,n=%d",m,n);
    return 0;
}