#include <stdlib.h>
#include <stdio.h>
#include "headers/erreurs.h"

char* error_names[] = {"ERR", "ERR_MAIN", "ERR_TYSTRING", "ERR_CONST"  ,
		"ERR_TYNUM", "ERR_NULL" , "ERR_INTLIT" , "ERR_DECLARE",
		"ERR_END"  , "ERR_BEGIN", "ERR_RETURN" , "ERR_TRUE"   ,
        "ERR_FALSE", "ERR_IF"   , "ERR_ELSE"   , "ERR_ELIF"   ,
        "ERR_WHILE", "ERR_DO"   , "ERR_FOR"    , "ERR_SCAN"   ,
		"ERR_IN"   , "ERR_PRINT", "ERR_STRING" , "ERR_ID"     ,
		"ERR_NUM"  , "ERR_DESC" , "ERR_ASC"    ,

		"ERR_PV"   , "ERR_PT"   , "ERR_DPT"    , "ERR_VIR"   ,
		"ERR_AFF"  , "ERR_INF"  , "ERR_INFEG"  , "ERR_SUP"   ,
		"ERR_SUPEG", "ERR_DIFF" , "ERR_PO"     , "ERR_PF"    ,
		"ERR_PLUS" , "ERR_MINUS", "ERR_MULT"   , "ERR_MOD"   ,
		"ERR_EG"   , "ERR_DIV"  , "ERR_AO"     , "ERR_AF"    ,
		"ERR_CO"   , "ERR_CF"   , "ERR_COMM"   , "ERR_EOF"   ,
		"ERR_TOKEN"
        };


void Erreur(int cod_err)
{
        printf("\n### Error type: %s. Wrong tokens used. ###\n", error_names[cod_err]);
        exit(EXIT_FAILURE);
}


void Erreur_sem(int cod)
{
    printf("\n### Semantic error: ");
    switch(cod)
    {
        case not_declared:
            printf("ID wasn't previously declared.");
            break;
        case double_dec:
            printf("Beware of the double declaration.");
            break;
        case const_aff:
            printf("You tried to change the value of a CONST.");
            break;
        case div_zero:
            printf("You tried to divide by zero!");
            break;
        case mod_notInt:
            printf("Invalid operand %: You have a float!");
            break;
        case op_num_string:
            printf("You can't add/substract/divide/multiply/modulate a numeric type and a string.");
            break;
    }
    printf(" ###\n");
    exit(EXIT_FAILURE);
}
