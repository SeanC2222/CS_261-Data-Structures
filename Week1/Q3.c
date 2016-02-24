/* CS261- Assignment 1 - Q.3*/
/* Name: Sean Mulholland
 * Date: 4/11/2015
 * Solution description: The program generates an array of random numbers
 * and outputs the random array then passes the array to a function sort()
 * that sorts the order of values. It then outputs the sorted values.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
     /*Sort the given array number, of length n*/
	int i = 0, j = n-1;
	int temp = 0;
	for(; i < j; i++){
		for(; j > i; j--){
			if (number[j] < number[i]){
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}
		j = n - 1;
	}

	return;
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int* nArray;
    nArray = malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
    time_t t;
    srand(time(&t));

    for(int i = 0; i < n; i++){
    	nArray[i] = rand() % 200;
    }

    /*Print the contents of the array.*/
    for(int i = 0; i < n; i++){
    	printf("index %i: %i\n", i, nArray[i]);
    }
    printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
    sort(nArray, n);
    
    /*Print the contents of the array.*/    
    for(int i = 0; i < n; i++){
    	printf("index %i: %i\n", i, nArray[i]);
    }
    
    return 0;
}
