#include <stdio.h>
#include <string.h>
struct book
{
    int isbn;
    char bookName[20];
    double price;
};

int main(){
    struct book b;
    b.isbn=767645;
    strcpy(b.bookName,"Java编程思想");
    b.price=45;
    return 0;
}
