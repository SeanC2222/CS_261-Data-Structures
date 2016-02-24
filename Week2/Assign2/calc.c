#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	TYPE a = topDynArr(stack);
	popDynArr(stack);
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = b + a;
	pushDynArr(stack, b);
	return;
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	TYPE a = topDynArr(stack);
	popDynArr(stack);
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b -= a;
	pushDynArr(stack, b);
	return;
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	TYPE a = topDynArr(stack);
	popDynArr(stack);
	TYPE b = topDynArr(stack);
	popDynArr(stack);

	assert(a != 0);

	b /= a;
	pushDynArr(stack, b);
	return;
}

void multiply(struct DynArr *stack)
{
	TYPE a = topDynArr(stack);
	popDynArr(stack);
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b *= a;
	pushDynArr(stack, b);
	return;
}

void power(struct DynArr *stack)
{
	TYPE a = topDynArr(stack);
	popDynArr(stack);
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = pow(b, a);
	pushDynArr(stack, b);
	return;
}

void squaring(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = pow(b, 2);
	pushDynArr(stack, b);
	return;
}

void cubing(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = pow(b, 3);
	pushDynArr(stack, b);
	return;
}

void absoluteValue(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	if (b < 0){
		b = -b;
	}
	pushDynArr(stack, b);
	return;
}

void squareRoot(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = sqrt(b);
	pushDynArr(stack, b);
	return;
}

void exponential(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = exp(b);
	pushDynArr(stack, b);
	return;
}

void naturalLog(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = log(b);
	pushDynArr(stack, b);
	return;
}

void logTen(struct DynArr *stack)
{
	TYPE b = topDynArr(stack);
	popDynArr(stack);
	b = log10(b);
	pushDynArr(stack, b);
	return;
}
double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			multiply(stack);
		else if(strcmp(s, "^") == 0)
			power(stack);
		else if(strcmp(s, "^2") == 0)
			squaring(stack);
		else if(strcmp(s, "^3") == 0)
			cubing(stack);
		else if(strcmp(s, "abs") == 0)
			absoluteValue(stack);
		else if(strcmp(s, "sqrt") == 0)
			squareRoot(stack);
		else if(strcmp(s, "exp") == 0)
			exponential(stack);
		else if(strcmp(s, "ln") == 0)
			naturalLog(stack);
		else if(strcmp(s, "log") == 0)
			logTen(stack);
		else 
		{

			double* getNum = malloc(sizeof(double));
			if(strcmp(s, "pi") == 0){
				pushDynArr(stack, 3.14159265);
			} else if (strcmp(s, "e") == 0){
				pushDynArr(stack, 2.7182818);
			} else if (isNumber(s, getNum)){
				pushDynArr(stack, *getNum);
			} else {
				assert(isNumber(s, getNum));
				pushDynArr(stack, *getNum);
			}

			free(getNum);
		}
	}	//end for 
	assert(sizeDynArr(stack) == 1);
	for (int i = 0; i < sizeDynArr(stack);i++){
		result = topDynArr(stack);
		popDynArr(stack);
		printf("Result of Calculation: %f", result);
	}
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
