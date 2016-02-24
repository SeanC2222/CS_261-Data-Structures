/* CS261- Assignment 1 - Q.2*/
/* Name: Sean Mulholland
 * Date: 4/11/2015
 * Solution description: This program declares 3 integers, passes 2 values as
 * pointers and one as an integer to a function foo() that doubles the first's
 * value, halves the second, and assigns the copy of the integer to the sum
 * of the first and second int*'s. foo() returns the value of c, and then the
 * return value is output and the value of the third integer is output to
 * illustrate the difference between passing as a pointer vs. passing a copy.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a *= 2;
    
    /*Set b to half its original value*/
    *b /= 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5, y = 6, z = 7;
    
    /*Print the values of x, y and z*/
    printf("x = %i, y = %i, z = %i\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int retVal = foo(&x,&y,z);
    
    /*Print the value returned by foo*/
    printf("Return Value: %i\n", retVal);
    
    /*Print the values of x, y and z again*/
    printf("x = %i, y = %i, z = %i\n", x, y, z);

    /*Is the return value different than the value of z?  Why?*/
    	/* Yes, because z isn't passed as a pointer. It makes a new variable c
    	 * and assigns it the value of z and returns that value. z will always
    	 * be its original value unless the code is changed.
    	 */
    return 0;
}
    
    
