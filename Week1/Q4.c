/* CS261- Assignment 1 - Q.4*/
/* Name: Sean Mulholland
 * Date: 4/11/2015
 * Solution description: This program generates an array of students randomly
 * (with unique ID's) with random scores. The array of students is then output,
 * sorted by their scores from low to high, then output after the sorting.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
	int i = 0, j = n-1;
	struct student temp;
	for(; i < j; i++){
		for(; j > i; j--){
			if (students[j].score < students[i].score){
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
		j = n - 1;
	}

}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;
    
    /*Allocate memory for n students using malloc.*/
    struct student* nStudents;
    nStudents = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    time_t t;
    srand(time(&t));
    
	int *count;
	count = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++){
		count[i] = 0;
	}
	int temp;
	for(int i = 0; i < n; i++){
		while(i < n){
			temp = rand() % (n + 1);
			if (count[temp] == 0){
				nStudents[i].id = temp + 1;
				nStudents[i].score = rand() % 101;
				count[temp]++;
				break;
			} else {
				continue;
			}
		}
	}
	free(count);

    /*Print the contents of the array of n students.*/
    for(int i = 0; i < n; i++){
    	printf("Student %i: %i\n", nStudents[i].id, nStudents[i].score);
    }
    printf("\n");

    /*Pass this array along with n to the sort() function*/
    sort(nStudents, n);
    
    /*Print the contents of the array of n students.*/
    for(int i = 0; i < n; i++){
    	printf("Student %i: %i\n", nStudents[i].id, nStudents[i].score);
    }

    return 0;
}
