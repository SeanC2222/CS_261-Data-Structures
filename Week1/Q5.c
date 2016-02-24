/* CS261- Assignment 1 - Q.5*/
/* Name: Sean Mulholland
 * Date: 4/11/2015
 * Solution description: This program reads in a user input single "word"
 * and converts that word to "Sticky Caps" (alternating letter case). It
 * then outputs the sticky caps version of the word to the user.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	int trigger = 1;

	char* letter;
	letter = word;
	while(*letter != '\0'){
		if (islower(*letter) && trigger){
			*letter = toUpperCase(*letter);

		} else if (isupper(*letter) && !trigger){
			*letter = toLowerCase(*letter);

		}
		if (trigger){
			trigger = 0;
		} else {
			trigger = 1;
		}
		letter++;
	}
	return;
}

int main(){
    /*Read word from the keyboard using scanf*/
	char* word;
	int wordSize = 50; //50 char max
	word = malloc(wordSize * sizeof(char));
	for(int i = 0; i < wordSize; i++){
		word[i] = '\0';
	}
	printf("Please enter a word: ");
	scanf("%s", word);

    /*Call sticky*/
    sticky(word);
    
    /*Print the new word*/
    printf("Sticky Caps: %s", word);
    return 0;
}
