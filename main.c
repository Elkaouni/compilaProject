#include <stdio.h>
#include <stdlib.h>
#include "headers/syntax.h"
#define _extern
#include "headers/file.h"
#undef _extern



typedef struct
{
    int code; //token
    char nom[20];
}sym;

sym list[1000];
sym symbole;
int tailleList = 0;

void saveTokenInList(Token* token)
{
    symbole.code = token->type;
    //printf("Saving: %s ...\n", token->value);
    strcpy(symbole.nom,token->value);
    list[tailleList]= symbole;
    tailleList++;
}

int start =0;
void AfficherToken(Token* token)
{
    if(!start)
		{
		    printf("\n#######################          #####################\n");
		      printf("##   Mots/Symboles   ##          ##      Token      ##\n");
		      printf("#######################          #####################\n");
		    start++;
		}
    printf(" %s\t\t\t\t%s\n", token->value, token_names[token->type]);
    printf("________________________________________________________________\n");
}

void printList()
{
    int i;
    for(i=0; i<tailleList; i++){
        printf(" %s --> %s \n", list[i].nom, token_names[list[i].code]);
    }
}

int main(int argc, char *argv[])
{
	printf("##################################################################################\n");
	printf("##################  Welcome to the simulation of our compiler.  ##################\n");
    printf("##################################################################################\n");
	printf("##                                                                              ##\n");
    printf("##  Information regarding our grammar is in the report submitted with the code. ##\n");
    printf("##  We recommend using one of our example files in the test folder.             ##\n");
	printf("##                                                                              ##\n");
    printf("##################################################################################\n");
    printf("\nPress Enter to start the lexical analysis of your inserted file.");
    getchar();
	if (argc != 2)
	{
		printf("You didn't choose any file. Please try again and don't forget to choose one.\n");
		getchar();
		exit(1);
	}

	if ((file = fopen(argv[1], "r")) == NULL)
	{
		printf("ERROR! Could not open the file.\n");
		getchar();
		exit(1);
	}

	reading = ' ';
	while (!feof(file))
	{
		Token *token = Symb_suiv();
		AfficherToken(token);
		saveTokenInList(token);
	}
	if(!init_lexer_token_list(list, tailleList))
        exit(0);

    printf("    ######################################\n");
    printf("    #            Lexer: Done.            #\n");
    printf("    ######################################\n\n");
    //printList();

    printf("\nPress Enter to start launch the PARSER.");
    getchar();
    printf("    ######################################################\n");
    printf("    #  Parser: Starting syntax and semantic analysis...  #\n");
    printf("    ######################################################\n");
    premier_sym();
	MAIN();

	printf("           ############################### \n");
    printf("           #  Done analyzing the file.   #\n");
    printf("           #  Compiler is shutting down  #\n");
    printf("           ############################### \n");

    getchar();
	return 1;
}
