//动态内存分配---字符串
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char *s;
    s=(char*)malloc(10);
    strcpy(s,"hello");
    printf("%s\n",s);
    // 释放内存
    free(s);
    s = NULL;
    return 0;
}