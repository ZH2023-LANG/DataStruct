// 结构体与指针
#include <stdio.h>
struct point
{
    int x;
    int y;
};

int main(){
    struct point p;
    p.x=1;
    p.y=2;
    
    struct point *pp;
    pp=&p;
    (*pp).x=2;
    (*pp).y=1;
    printf("x=%d,y=%d\n",p.x,p.y);
    printf("x=%d,y=%d\n",pp->x,pp->y);
}