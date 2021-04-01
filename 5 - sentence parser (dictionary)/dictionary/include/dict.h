#include <stdlib.h>
#include <string.h>
#ifdef _WIN_32
#endif
#define EN_LANG 5
/*
	KEY
	---
	ARTICLE   || 'A'
	NOUN      || 'N'
	PRONOUN   || 'P'
	VERB      || 'V'
	ADJECTIVE || 'J'
	ADVERB    || 'D'
	POSITIONS || 'X'
*/
#define GRAMMAR_ARTICLE   'A'
#define GRAMMAR_NOUN      'N'
#define GRAMMAR_PRONOUN   'P'
#define GRAMMAR_VERB      'V'
#define GRAMMAR_ADJECTIVE 'J'
#define GRAMMAR_ADVERB 	  'D'
#define GRAMMAR_POSITIONS 'X'

#define SPECIALCASEFLAGS case('&'):case (';'):case ('#'):case ('='):

typedef struct dictionary_s * dictionary;

typedef struct phrasedat{
	char **phrase;
	char **phrase_t;
	char *flavor;
	int nwords,nword;
	int term;
}phrasedat;

typedef struct sentencedat{
	char **sentence;
	char **sentence_t;
	char *flavor;
	int swords,sword;
	int term;
}sentencedat;

// called once to populate a struct rootdict
void init_rootdict()	{	
	printf("\nhello");
}

phrasedat *dict_check(char *filename,phrasedat *ph_dat) {
	char ch, *alloc, dict_string[100], string_ch[2];
	int increm = 0;
	FILE *fp;
	ph_dat = malloc(sizeof(struct phrasedat*)*14);
	fp = fopen(filename, "r"); 
	ph_dat->nwords = 0; 
	while((ch = fgetc(fp)) != EOF){
		switch (ch)
		{
	//escape key, nl
			case ('\n'):
			break;
			SPECIALCASEFLAGS
				if (ch == ';')	{
					increm++;
					ph_dat->nwords++;
					ph_dat->phrase[increm] = calloc(12, sizeof(char*));
					strcpy(ph_dat->phrase[increm],dict_string);
					strcpy(dict_string,"");
				}
				if (ch == '#')	{
					increm++;
					ph_dat->phrase[increm] = calloc(12, sizeof(char*));
					strcpy(ph_dat->phrase[increm],dict_string);
					strcpy(dict_string,"");
				}
			break;
			default:
				string_ch[0] = ch;
				strcat(dict_string,string_ch);
			break;
		};
	}
	//sentence parser
	ch = 1;
	for (increm=increm; increm!=0; increm--)
	{
		if ( ph_dat->phrase[increm][0] == '%')
		{
			strcpy(ph_dat->phrase[increm],"");
		}
	}
	return ph_dat;
}

phrasedat *dict_cleanup(char *filename,phrasedat *ph_dat)
{
	char **phraseholding;
	char ch;
	int n,a;
	int c=1;
	ph_dat->phrase_t = malloc(sizeof(char **)*sizeof(ph_dat->phrase));
	for (n=1;n!=ph_dat->nwords+1;n++){
		a = strlen(ph_dat->phrase[n]);
		if (a >= 1)
		{
			ph_dat->phrase[c] = ph_dat->phrase[n];
			ch = ph_dat->phrase[c][0];
			switch (ch)
			{
				case GRAMMAR_ARTICLE:
				ph_dat->phrase_t[c] = "art";
				break;
				case GRAMMAR_ADJECTIVE:
				ph_dat->phrase_t[c] = "adj";
				break;
				case GRAMMAR_NOUN:
				ph_dat->phrase_t[c] = "nun";
				break;
				case GRAMMAR_PRONOUN:
				ph_dat->phrase_t[c] = "pun";
				break;
				case GRAMMAR_POSITIONS:
				ph_dat->phrase_t[c] = "pos";
				break;
				case GRAMMAR_VERB:
				ph_dat->phrase_t[c] = "ver";
				break;
			}
			ph_dat->phrase[c][0] = ' ';
			c++;
		}
	}
	for (n=c;n!=ph_dat->nwords+1;n++){
		ph_dat->phrase[n] = "";
	}
	return ph_dat;
}

//display words
phrasedat *disp_dictwords(phrasedat *ph_dat)
{
	int increm;
	for (increm=1; increm!=ph_dat->nwords+7; increm++)
	{
		if (ph_dat->phrase[increm] == "")
		{
			break;
		}
		printf("\nWORDS:->[%d] %s",increm,ph_dat->phrase[increm]);
	}
}

// this reads a dictionary and cleans up the output
phrasedat *read_dict(char *filename,phrasedat *ph_dat)
{
	ph_dat = dict_check(filename,ph_dat);
	ph_dat = dict_cleanup(filename,ph_dat);
	return ph_dat;
}

sentencedat *parse_sentence(char *string,sentencedat *sen_dat, phrasedat *ph_dat) {
	sen_dat = malloc(sizeof(string)*strlen(string));
	sen_dat->swords = 1;
	sen_dat->sentence = malloc(sizeof(string)*sizeof(string));
	int o,n,y = 1;
	char s[2];
		sen_dat->sentence[1] = calloc(12,sizeof(string));
		strcpy(sen_dat->sentence[1],"");
	for (int n=0;n!=strlen(string)-1;n++)
	{
			s[0] = string[n]; 
			if (string[n] != ' ')
				{
					strcat(sen_dat->sentence[y],s);
				}
			o++;
		if (string[n] == ' '){
			y++;
			sen_dat->sentence[y] = calloc(strlen(string),4);
			strcpy(sen_dat->sentence[y],"");
			sen_dat->swords++;
			o=1;
		}
	}
	return sen_dat;
}

sentencedat *searchdictfword(char *string,sentencedat *sen_dat, phrasedat *ph_dat) {
	int c,n,g = 1;
	for (int n=1;n!=sen_dat->swords+1;n++)
	{
		for (int p=1;p!=ph_dat->nwords+1;p++)
		{
			if (strstr(ph_dat->phrase[p],sen_dat->sentence[n]))
			{
				printf("\n%s, %s, [%d]",ph_dat->phrase[p],ph_dat->phrase_t[p],p);
			}
		}
	}
	return sen_dat;
}