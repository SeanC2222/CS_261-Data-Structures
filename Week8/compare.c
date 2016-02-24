#include <stdlib.h>
#include "dynamicArray.h"
#include "type.h"

int compare(TYPE left, TYPE right){

   struct Task* one = (struct Task*)left;
   struct Task* two = (struct Task*)right;

   if(one->priority > two->priority){
      return 1;
   } else if (one->priority < two->priority){
      return -1;
   } else {
      return 0;
   }
}

