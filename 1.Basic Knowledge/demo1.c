#include <stdio.h>
#include <string.h>
int main(){
    int a[]={1,2,3,4,5};
    for (int i = 0; i <sizeof(a)/sizeof(a[0]); i++)
    {
        printf("%d\n",a[i]);
    }
    printf("%zu\n",sizeof(a));
    printf("%zu\n",sizeof(a[0]));
    int len=sizeof(a)/sizeof(a[0]);
    printf("数组的长度是:%d\n",len);
}