/* CS261- Assignment 1 - Q. 0*/
/* Name: Sean Mulholland
 * Date: 4/9/2015
 * Solution description: This program prints information about an integer x
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
    /*Print the value pointed to by iptr*/
    printf("Value pointed to: %i\n", *iptr);
    /*Print the address pointed to by iptr*/
    printf("Address pointed to: %p\n", iptr);
    /*Print the address of iptr itself*/
    printf("Address of pointer: %p\n",&iptr);
    return;
}

int main(){
    
    /*declare an integer x*/
    int x = 0;
    /*print the address of x*/
    printf("Address of x: %p\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("Value of x: %i\n", x);
    return 0;
}
