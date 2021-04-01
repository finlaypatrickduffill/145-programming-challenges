#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dict.h>

char string[200];
char yh;

int main () {
	
	// make a structure for the dictionary, and a structure for the sentence
	phrasedat *ph_dat, *rootdict;
	sentencedat *sentence;
	
	// read a dictionary file to parse the sentence with
	if (ph_dat = read_dict("dict.dict",ph_dat))
	{
		printf("reading dict.dict...\n");
	}
	// errors
	if (ph_dat != NULL)
	{
		printf("read dict.dict successfully.\n");
	}
	// display words in phrase data
	printf("\n");
	fgets(string,199,stdin);
	
	sentence = parse_sentence(string,sentence,ph_dat);
	
	// search dictionary and approximate words in sentence
	searchdictfword(string,sentence,ph_dat);
	
	// point to the context of a sentence (link grammar)?
	
	getch(yh);
	return 0;
	
}