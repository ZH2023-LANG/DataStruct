#include <stdio.h>
#include <stdlib.h>

// int fibonacci(int n){
//     int last1=1;
//     int last2=1;
//     int result=0;
//     for(int i=3;i<=n;i++){
//         result=last1+last2;
//         last2=last1;
//         last1=result;
//     }
//     return result;
// }


int fibonacci(int n){
    if(n==1||n==2){
        return 1;
    }
    else{
        return fibonacci(n-1)+fibonacci(n-2);
    }
}

int main(){
    printf("%d",fibonacci(6));
    return 0;
}





