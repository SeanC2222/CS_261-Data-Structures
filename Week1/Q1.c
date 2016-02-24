/* CS261- Assignment 1 - Q.1*/
/* Name: Sean Mulholland
 * Date: 4/9/15
 * Solution description: This program dynamically allocates an array of student
 * structs, and assigns them an unique random ID (1-10), and each ID gets a
 * random score. The scores are then output, and some basic stats are output
 * (min, max, average). The memory is then freed and the program exits.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUMSTUDS 10 //Number of Students to Manipulate

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* newArr;
     newArr = malloc(NUMSTUDS * sizeof(struct student));
     /*return the pointer*/
     return newArr;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int *count;
	count = malloc(NUMSTUDS * sizeof(int));
	for(int i = 0; i < NUMSTUDS; i++){
		count[i] = 0;
	}
	int temp;
	for(int i = 0; i < NUMSTUDS; i++){
		while(i < NUMSTUDS){
			temp = rand() % (NUMSTUDS + 1);
			if (count[temp] == 0){
				students[i].id = temp + 1;
				students[i].score = rand() % 101;
				count[temp]++;
				break;
			} else {
				continue;
			}
		}
	}
	free(count);
	return;
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
               ...
              ID10 score10*/
	for(int i = 0; i < NUMSTUDS; i++){
		printf("%i %i\n", students[i].id, students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int max = 0;
	int min = 101;
	float sum = 0;

	for(int i = 0; i < NUMSTUDS; i++){
		if (students[i].score > max){
			max = students[i].score;
		}
		if (students[i].score < min){
			min = students[i].score;
		}
		sum += students[i].score;
    }
	printf("Minimum score: %i\n", min);
	printf("Maximum score: %i\n", max);
	printf("Average score: %.1f\n", sum / NUMSTUDS);
	return;
}

void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
	if (stud != NULL){
		free(stud);
	}
	return;
}

int main(){
    struct student* stud = NULL;

    time_t curTime;
    srand(time(&curTime));

    /*call allocate*/
    stud = allocate();

    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    stud = NULL;
    return 0;
}
