#include <stdio.h>
#include <string.h>
typedef struct point
{
    int x;
    int y;    
}Point;
Point swap(int a,int b){
    Point p;
    p.x=a;
    p.y=b;
    return p;
}
int main(){
    Point point=swap(1,2);
    printf("%d,%d",point.x,point.y);
}