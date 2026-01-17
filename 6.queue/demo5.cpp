#include <stdio.h>
typedef enum weekday{
    mon=1,tue,wed,thu,fri,sat,sun
}Weekday;

int main(){
    Weekday a;
    a=mon;
    Weekday b;
    b=tue;
    printf("%d\n",a);  //输出：1
    printf("%d\n",b);  //输出：2
    Weekday c;
    c=sat; 
    printf("%d\n",c);
}

