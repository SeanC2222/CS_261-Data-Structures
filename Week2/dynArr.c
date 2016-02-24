#include <stdio.h>
#include <assert.h>

int main() {

   int *a;
   int size;

   size = 10;
   a = malloc(size*sizeof(int));

   for (int i = 0; i < 10; i++){
      a[i] = 0;
   }

   int count = 0;

   while (count < 300){

      printf("Enter number %i :", count);
      scanf("%i", (a + count));
      count++;

      if (count == size){
	 int *temp;
	 temp = malloc(2*size*sizeof(int));
	 for (int i = 0; i < size; i++){
	    temp[i] = a[i];
	 }

	 free(a);
	 a = temp;
	 size = 2 * size;
      }
   }

   printf("The end.\n");

   for(int i = 0; i < size/2; i++){
      printf("%i\n", a[i]);
   }

   free(a);
   return 0;

}
