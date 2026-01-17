#include <stdio.h>
#include <string.h>
typedef struct student
{
    int number;
    char name[10];
}stu;

int main(){
    stu s;
    strcpy(s.name,"zxy");
    s.number=11;
    printf("%d\n",s.number);
    printf("%s\n",s.name);
}