#include <stdio.h>
#include <string.h>
#include <time.h>

#define M_ASSOC(a,b)  a=b+2

struct carry {
	char corpus[75][10];
	char a;
	char associations[75][10];
	char assocdata[75][10];
	char verbs[75][10];
	char verbs_pt[75][10];
	char adjectives[75][10];
	char nouns[75][10];
	char pronouns[75][10];
	char pipes[75][10];
	char realnames[75][10];
	
	int vtot, ntot, atot, pntot, pitot, rtot, vptot, rntot;
	
	char upping[75][10];
	
}carry;

void appendchar(char *x, char y) {
    char z[2];
    z[0] = y;
    z[1] = 0;
    strcat(x, z);
}

struct carry enter_names(struct carry carrycorpus) {
	
	int inc = 1;
	char ch;
	const char *gch = "A";
	FILE *fp;
	fp = fopen("corpus.txt", "r"); 
	strcpy(carrycorpus.corpus[inc],"");
	while((ch = fgetc(fp)) != EOF){
	appendchar(carrycorpus.corpus[inc],ch);
	if (ch  == ' ')
	{
		inc++;
	}
	}
	return carrycorpus;
	
}

struct carry make_assoc(struct carry carrycorpus) {

	int inc = 1;
	const char *gch = "A";
	char ch;
	FILE *fp;
	fp = fopen("syntax.txt", "r"); 
	printf("%d",sizeof(carrycorpus.corpus));
	int arrayfreesp = 0;
	int goal = sizeof(carrycorpus.corpus)/ sizeof(carrycorpus.corpus[1]);
	for (int y = 0; y!=goal; y++)
	{
		if (strlen(carrycorpus.corpus[y]) > 1){
			arrayfreesp++;
		}
	}
	char open_s[400];
	int inc_inl = 0;
	int inc_inv, inc_inu = 0;
	int inc_ama = 0;
	int inc_amb = 0;
	int inc_amv = 0;
	int inc_amq = 0;
	int inc_ampt = 0;
	while((ch = fgetc(fp)) != EOF){
			
		if (ch == '#')
		{
			strcpy(carrycorpus.verbs[inc_inu],"");
			strcat(carrycorpus.verbs[inc_inu],carrycorpus.associations[inc_inl]);
			inc_inu++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'H';
			inc_inl++;
		}
		else if (ch == ',')
		{
			strcpy(carrycorpus.pipes[inc_ama],"");
			strcat(carrycorpus.pipes[inc_ama],carrycorpus.associations[inc_inl]);
			inc_ama++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'U';
			inc_inl++;
		}
		else if (ch == '$')
		{
			strcpy(carrycorpus.realnames[inc_amv],"");
			strcat(carrycorpus.realnames[inc_amv],carrycorpus.associations[inc_inl]);
			inc_amv++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'G';
			inc_inl++;
		}
		else if (ch == '"')
		{
			strcpy(carrycorpus.adjectives[inc_amq],"");
			strcat(carrycorpus.adjectives[inc_amq],carrycorpus.associations[inc_inl]);
			inc_amq++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'A';
			inc_inl++;
		}
		else if (ch == '*')
		{
			strcpy(carrycorpus.nouns[inc_amb],"");
			strcat(carrycorpus.nouns[inc_amb],carrycorpus.associations[inc_inl]);
			inc_amb++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'N';
			inc_inl++;
		}
		else if (ch == '_')
		{
			strcpy(carrycorpus.verbs_pt[inc_ampt],"");
			strcat(carrycorpus.verbs_pt[inc_ampt],carrycorpus.associations[inc_inl]);
			inc_ampt++;
			strcpy(carrycorpus.assocdata[inc_inl],"");
			carrycorpus.assocdata[inc_inl][0] = 'T';
			inc_inl++;
		}
		else
		{
			appendchar(carrycorpus.associations[inc_inl],ch);
		}
	}
	
	carrycorpus.vtot = inc_inu;
	carrycorpus.pitot = inc_ama;
	carrycorpus.rtot = inc_amv;
	carrycorpus.atot = inc_amq;
	carrycorpus.pntot = inc_amb;
	carrycorpus.vptot = inc_ampt;
	
	while((ch = fgetc(fp)) != EOF){

	}
	return carrycorpus;
}

struct carry dev_corpus(struct carry carrycorpus) {
	carrycorpus.a = 1;
	
	int z = sizeof(carrycorpus.corpus)/sizeof(carrycorpus.corpus[1]);
	int z2 = sizeof(carrycorpus.associations)/sizeof(carrycorpus.associations[1]);
	char *strterm = "\0";
	
	for (int yx = 0; yx != z2; yx++){
		strcpy(carrycorpus.associations[yx],strterm);
		strcpy(carrycorpus.verbs[yx],strterm);
		strcpy(carrycorpus.upping[yx],strterm);
	}
	
	carrycorpus = enter_names(carrycorpus);
	carrycorpus = make_assoc(carrycorpus);

	return carrycorpus;
} 

struct carry make_sentences(struct carry carrycorpus) {
	
	int ptr;
	srand (time(NULL));
	for (int y=0;y!=21;y++){
			ptr = rand()%carrycorpus.pitot;
			printf(" %s ",carrycorpus.pipes[ptr]);
			
			ptr = rand()%carrycorpus.atot;
			printf("%s, ",carrycorpus.adjectives[ptr]);
				
			ptr = rand()%carrycorpus.atot;
			printf("%s ",carrycorpus.adjectives[ptr]);
				
			ptr = rand()%carrycorpus.vtot;
			printf("%s ",carrycorpus.verbs[ptr]);	
				
			ptr = rand()%carrycorpus.vptot;
			printf("%s ",carrycorpus.verbs_pt[ptr]);
				
			ptr = rand()%carrycorpus.rtot;
			printf("%s",carrycorpus.realnames[ptr]);
			printf(".");
	}

	return carrycorpus;
	
}

	char corpus[75][10] = { "the", "quick", "brown", "fox", "jumps", "over"};
	char associations[75][10] = { "A", "B", "B", "C", "D", "E"};

int main() {
	int x = 8;
	int y = 8;
	
	struct carry carrycorpus;
	carrycorpus = dev_corpus(carrycorpus);
	make_sentences(carrycorpus);
	
	make_sentences(carrycorpus);
	
}