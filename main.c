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

void AfficherToken(Token* token)
{
    printf(" %s          %s \n________________\n", token->value, token_names[token->type]);
}

void printList()
{
    int i;
    for(i=0; i<tailleList; i++){
            printf(" %s --> %s \t", list[i].nom, token_names[list[i].code]);
            if(i%4 ==0)
                printf("\n");
    }
}

int main(int argc, char *argv[])
{
	char* path = "C:\\Users\\user\\Desktop\\2A Ensias\\S3\\Projets\\compilateur\\compilateur\\tests\\exemple3.rh";
	/*if (argc != 2)
	{
		printf("You didn't choose any file. Please try again and don't forget to choose one.\n");
		exit(1);
	}*/

	if ((file = fopen(path, "r")) == NULL)
	{
		printf("ERROR! Could not open the file.\n");
		exit(1);
	}

	reading = ' ';
	while (!feof(file))
	{
		Token *token = Symb_suiv();
		//AfficherToken(token);
		saveTokenInList(token);
	}

	if(!init_lexer_token_list(list, tailleList))
        exit(0);

    printList();
    printf("\nStart\n");

	premier_sym();
	MAIN();

	printf("\n\nOfficially done.\n");
	return 1;
}
