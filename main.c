#include <stdio.h>
#include "two_primes_generation.h"  // Include the header file


int main (){

    int a=14;
    printf("Address of a: %p\n", &a);  // %p is used for printing addresses
    int *b;
    b = &a;
    *b = *b +10;
    printf("HELLO WORLD");

    checkinclude();

    return 0;



}
