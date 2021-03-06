#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
   struct hashLink* pLink;
   struct hashLink* pLink2;

   for(int i = 0; i < ht->tableSize; i++){
      pLink = ht->table[i];
      while(pLink != NULL){
	 pLink2 = pLink;
	 pLink = pLink->next;
	 free(pLink2->key);
	 free(pLink2);
      }	 	 
   }

   free(ht->table);
   return;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}


void _insertNewTable(struct hashLink** table, int loc, struct hashLink* link){

   struct hashLink* pLink;

   if(table[loc] == NULL){
      table[loc] = link;
      
   } else {
      pLink = table[loc];
      while(pLink->next != NULL){
	 pLink = pLink->next;
      }
      pLink->next = link;
      
   }

   link->next = NULL;
   return;   
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{

   assert(ht != NULL);
   struct hashLink** newTable;
   newTable = (struct hashLink**)malloc(newTableSize * sizeof(struct hashLink*));

   for(int i = 0; i < newTableSize; i++){
      newTable[i] = NULL;
   }

   struct hashLink* pLink;
   struct hashLink* pLink2;
   int newCount = 0;

   for(int i = 0; i < ht->tableSize; i++){
      pLink = ht->table[i];
      if(pLink == NULL){
	 continue;
      } else {
	 while(pLink != NULL){
	    int newLoc = stringHash1(pLink->key) % newTableSize;
	    pLink2 = pLink->next;
	    _insertNewTable(newTable, newLoc, pLink);
	    pLink = pLink2;
	    newCount++;
	 }
      }
   }
    
   free(ht->table);
   ht->table = newTable;
   ht->tableSize = newTableSize;
   ht->count = newCount;

   return;
}


/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	assert(ht != NULL);

	int loc = stringHash1(k) % ht->tableSize;

	if(containsKey(ht, k)){
		struct hashLink* pLink = ht->table[loc];
	        while(strcmp(pLink->key, k)){
		     pLink = pLink->next;
	        }
		pLink->value = pLink->value + v;
 
	} else {

		struct hashLink* newLink = (struct hashLink*)malloc(sizeof(struct hashLink));
		newLink->key = (char*)malloc((1 + strlen(k)) * sizeof(char));
		strcpy(newLink->key, k);
		newLink->value = v;
		newLink->next = NULL;


	        struct hashLink* pLink = ht->table[loc];
	        if(pLink == NULL){
		   ht->table[loc] = newLink;
	        } else {
		   while(pLink->next != NULL){
			pLink = pLink->next;
		   } 
		   pLink->next = newLink;
	        }
	        ht->count++;
	}

	if(tableLoad(ht) >= LOAD_FACTOR_THRESHOLD){
		_setTableSize(ht, 2 * ht->tableSize);
	}


	return;
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	assert(ht != NULL);

	int loc = stringHash1(k);

	if(containsKey(ht, k)){
		struct hashLink* pLink = ht->table[loc];
		while(strcmp(pLink->key, k)){
			pLink = pLink->next;
		}
		ValueType* temp;
		temp = &(pLink->value);
		return temp;
	} else {
		return NULL;
	}
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	int loc = stringHash1(k) % ht->tableSize;

	struct hashLink* pLink = ht->table[loc];
        while(pLink != NULL && strcmp(pLink->key,k)){
	    pLink = pLink->next;
	}

	if(pLink == NULL){
	    return 0;
	} else {
	    return 1;
	}
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
   assert(ht != NULL);
   int loc = stringHash1(k) % ht->tableSize;
   if(containsKey(ht, k)){
      
      struct hashLink* pLink = ht->table[loc];
      struct hashLink* pLink2 = pLink;
      while(strcmp(pLink->key,k)){
	 pLink2 = pLink;
	 pLink = pLink->next;
      }

      if(pLink == pLink2){
	  ht->table[loc] = pLink->next;
      } else {
	  pLink2->next = pLink->next;
      }	 
      free(pLink->key);
      free(pLink);

   
   } else {
      //Do nothing	
   }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	return ht->tableSize;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	return ht->count;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	int emptyCount = 0;

	for(int i = 0; i < ht->tableSize; i++){
		if(ht->table[i] == NULL){
			emptyCount++;
		}
	}
	return emptyCount;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
   
	return ((float)ht->count / (float)ht->tableSize);
}

void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


