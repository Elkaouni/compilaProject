#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "headers/syntax.h"
#define _extern
#include "headers/file.h"
#undef _extern
#include "headers/codeGenerator.h"
#include "headers/semantique.h"
#include <math.h>

sym sym_cour, sym_precNS, sym_IDprec;

/*******************************************
   Defining the table where we'll store
      all our symbols with their types
*******************************************/
static int index =0;
static T_TAB_IDF TAB_IDFS[100];
static char* type[] = {"TCONSTNUM", "TCONSTSTRING", "TNUM", "TSTRING", "TNULL"};
void printTAB_IDFS()
{
    int i=0;
    printf("Printing saved constants and numeric/string variables:\n");
    for(i = 0; i<index; i++)
    {
        int TYPE = TAB_IDFS[i].TIDF;
        if(TYPE == TCONSTNUM ||  TYPE ==TNUM)
            printf("symbole: %s\t\ttype: %s\t\tvalue: %.2f \n", TAB_IDFS[i].NOM, type[TYPE], TAB_IDFS[i].i_value);
        else
            printf("symbole: %s\t\ttype: %s\t\tvalue: %s \n", TAB_IDFS[i].NOM, type[TYPE], TAB_IDFS[i].value);
    }
}

/*************************************
   Adding ID in table TAB_IDFS and
          its value resp
*************************************/
void ajouter(sym symbole,int type)
{
    strcpy(TAB_IDFS[index].NOM, symbole.nom);
    TAB_IDFS[index].TIDF = type;
    index++;
}
void ajouter_val(char*val, sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            strcpy(TAB_IDFS[i].value,val);
            printf("added : %s\n", TAB_IDFS[i].value);
            return;
        }
    }
    printf("ajouter_val: not found.\n");
}
void ajouter_i_val(float val, sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            TAB_IDFS[i].i_value = val;
            return;
        }
    }
    printf("ajouter_i_val: not found.\n");
}



/*************************************/
/** semantic verification functions **/
/*************************************/
int ExistInTab(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
            return 1;
    }
    return 0;
}
int isNumericType(sym symbole)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            switch(TAB_IDFS[i].TIDF)
            {
            case TNUM:
            case TCONSTNUM:
                {
                    return 1;
                }
            default:
                {
                    return 0;
                }
            }
        }
    }
    return 0;
}
int isStringType(sym symbole)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            switch(TAB_IDFS[i].TIDF)
            {
            case TSTRING:
            case TCONSTSTRING:
                {
                    return 1;
                }
            default:
                {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int get_adresse(sym id)
{
    for(int j = 0; j<index; j++)
    {
        if(strcmp(id.nom, TAB_IDFS[j].NOM)==0)
        {
            return j;
        }
    }
    return -1;
}

/**********************************
     Recuperating lexer's result
**********************************/
sym lexer_toxens[100];
int taille;
int init_lexer_token_list(sym* list_source, int size_source)
{
   if(size_source> 100)
        return 0;
   int i=0;
   for(i=0; i<size_source; i++)
   {
       lexer_toxens[i] = list_source[i];
       if(lexer_toxens[i].code == INTLIT_TOKEN)
       {
           lexer_toxens[i].code = NUM_TOKEN;
       }
   }
   taille = size_source;
   return 1;
}



/**********************************
         Starting Parser
**********************************/
int t=1;
void premier_sym()
{
    sym_cour = lexer_toxens[0];
}
void Sym_suiv()
{
    if(t==taille)
        return;
    sym_cour.code = lexer_toxens[t].code;
    strcpy(sym_cour.nom, lexer_toxens[t].nom);
    t++;
}
void printLexer()
{
    printf("_________________________________\n");
    printf("CHECKING THE LEXER LIST:");
    for(int i=0; i<taille; i++)
    {
        printf("nom: %s code: %s ||\t\t", lexer_toxens[i].nom, token_names[lexer_toxens[i].code]);
        if(i%3 ==0)
                printf("\n");
    }
    printf("DONE CHECKING. NOW LET'S START.\n");
    printf("_________________________________\n");
}


char gs_value[100];
float gi_value;
void set_i_value(float val)
{
    gi_value = val;
}
void set_value(char *val)
{
    strcpy(gs_value, val);
}
void Test_Symbole (int token, int COD_ERR)
{
   while(sym_cour.code == COMM_TOKEN)
   {
       Sym_suiv();
   }
   if(sym_cour.code == token)
    {
        if(sym_cour.code == TYNUM_TOKEN)
            sym_precNS = sym_cour;
        else if(sym_cour.code == TYSTRING_TOKEN)
            sym_precNS = sym_cour;

        else if(sym_cour.code == ID_TOKEN)
        {
            sym_IDprec = sym_cour;
        }
        else if(sym_cour.code == NUM_TOKEN)
        {
            gi_value = atoi(sym_cour.nom);
        }
        else if(sym_cour.code == STRING_TOKEN)
        {
            printf("We have the string: %s\n", sym_cour.nom);
            strcpy(gs_value, sym_cour.nom);
        }

      //  printf("Done with nom->%s  code->%s\n", sym_cour.nom, token_names[sym_cour.code]);
        do{
            Sym_suiv();
        }while(sym_cour.code == COMM_TOKEN);

    }
    else
    {
       // printLexer();
        Erreur(COD_ERR);
    }
}

int gi_isCst=0;
void addID()
{
    if(gi_isCst==1)
    {
       if(sym_precNS.code == TYNUM_TOKEN)
        {
            ajouter(sym_IDprec, TCONSTNUM);
            return;
        }
         else if(sym_precNS.code == TYSTRING_TOKEN)
        {
            ajouter(sym_IDprec, TCONSTSTRING);
            return;
        }
    }
    else if(gi_isCst==0)
     {
       if(sym_precNS.code == TYNUM_TOKEN)
        {
            ajouter(sym_IDprec, TNUM);
            return;
        }
         else if(sym_precNS.code == TYSTRING_TOKEN)
        {
            ajouter(sym_IDprec, TSTRING);
            return;
        }
    }
    printf("addid: not found.\n");
}

int ig_main_return_type;
void MAIN()
{
    Test_Symbole(MAIN_TOKEN, ERR_MAIN);
    Test_Symbole(PO_TOKEN, ERR_PO);
    int args;
    do{
        args =0;
        switch(sym_cour.code)
        {
            case TYNUM_TOKEN:
                Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
                Test_Symbole(ID_TOKEN, ERR_ID);
                addID();
                break;
            case TYSTRING_TOKEN:
                Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
                Test_Symbole(ID_TOKEN, ERR_ID);
                addID();
                break;
            default:
                break;
        }
        if(sym_cour.code == VIR_TOKEN)
        {
            args = 1;
            Test_Symbole(VIR_TOKEN, ERR_VIR);
        }
    }while(args);

    Test_Symbole(PF_TOKEN, ERR_PF);
    Test_Symbole(DPT_TOKEN, ERR_DPT);
    switch(sym_cour.code)
    {
        case TYSTRING_TOKEN:
            Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
            ig_main_return_type = TYSTRING_TOKEN;
            break;
        case TYNUM_TOKEN:
            Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
            ig_main_return_type = TYNUM_TOKEN;
            break;
        case NULL_TOKEN:
            Test_Symbole(NULL_TOKEN, ERR_NULL);
            ig_main_return_type = NULL_TOKEN;
            break;
        default:
            Erreur(ERR);
    }
    Test_Symbole(AO_TOKEN, ERR_AO);
    DECLARE();
    INSTS();
    generer1(HLT);
    Test_Symbole(AF_TOKEN, ERR_AF);

    printf("\n    ###########################################################\n");
    printf("    #  Parser: Done. Printing saved constants and variables.  #\n");
    printf("    ###########################################################\n");
    printTAB_IDFS(TAB_IDFS, index);
    printf("\n\n");
    printf("                       ##################\n");
    printf("                       #      DONE      #\n");
    printf("                       ##################\n");
   /*printf("\nPress Enter to print the generated P-Code.");
    getchar();
    print_code();
    printf("\n\n");
    printf("    #############################################\n");
    printf("    #     P-Code will be saved in a file...     #\n");
    printf("    #############################################\n");
    SavePCodeToFile(FILE_SORTIE);
    printf("\n");
    printf("    ##################################################### \n");
    printf("    #      Successfully saved in file \"test_result.rh\".      #\n");
    printf("    ##################################################### \n\n\n\n");
*/
}

void DECLARE()
{
     CONSTS();
     NUMERIC();
     STRINGS();
    generer2(INT, offset);
}

void CONSTS()
{
    switch(sym_cour.code)
    {
        case CONST_TOKEN:
        {
            gi_isCst=1;
            Test_Symbole(CONST_TOKEN,ERR_CONST);
            int typeID = -1;

            switch(sym_cour.code) //type de la cst
            {
                case TYSTRING_TOKEN:
                    typeID = TYSTRING_TOKEN;
                    Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
                    break;
                case TYNUM_TOKEN:
                    typeID=TYNUM_TOKEN;
                    Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
                    break;
                default:
                    Erreur(ERR);
            }
            Test_Symbole(ID_TOKEN,ERR_ID);
            addID();
            Test_Symbole(AFF_TOKEN,ERR_AFF);
            if(typeID==TYNUM_TOKEN)
            {
                Test_Symbole(NUM_TOKEN,ERR_NUM);
                ajouter_i_val(gi_value, sym_IDprec);
            }
            else{
                if(typeID == TYSTRING_TOKEN){
                    Test_Symbole(STRING_TOKEN, ERR_STRING);
                    ajouter_val(gs_value, sym_IDprec);
                }
                else
                    Erreur(ERR);
            }
            while(sym_cour.code== VIR_TOKEN)
            {
                Test_Symbole(VIR_TOKEN, ERR_VIR);;
                switch(sym_cour.code) //type de la cst
                {
                    case TYSTRING_TOKEN:
                        typeID=TYSTRING_TOKEN;
                        Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
                        break;
                    case TYNUM_TOKEN:
                        typeID=TYNUM_TOKEN;
                        Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
                        break;
                    default:
                        Erreur(ERR);
                }
                Test_Symbole(ID_TOKEN,ERR_ID);
                addID();
                Test_Symbole(AFF_TOKEN,ERR_AFF);
                if(typeID==TYNUM_TOKEN)
                {
                    Test_Symbole(NUM_TOKEN,ERR_NUM);
                    ajouter_i_val(gi_value, sym_IDprec);
                }
                else{
                    if(typeID == TYSTRING_TOKEN){
                        Test_Symbole(STRING_TOKEN, ERR_STRING);
                        ajouter_val(gs_value, sym_IDprec);
                    }
                    else
                        Erreur(ERR);
                }

            }
            Test_Symbole(PV_TOKEN,ERR_PV);
            generer1(STO);
            gi_isCst=0;
        }
        case TYNUM_TOKEN:
            break;
        case TYSTRING_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(ERR_CONST);
    }
}

void NUMERIC()
{
    switch(sym_cour.code)
    {
        case TYNUM_TOKEN:
            {
                Test_Symbole(TYNUM_TOKEN,ERR_TYNUM);
                Test_Symbole(ID_TOKEN,ERR_ID);
                addID();
                offset++;

                while(sym_cour.code == VIR_TOKEN)
                {
                    Test_Symbole(VIR_TOKEN, ERR_VIR);
                    Test_Symbole(ID_TOKEN,ERR_ID);
                    addID();
                    offset++;
                }
                Test_Symbole(PV_TOKEN,ERR_PV);
            }
        case CONST_TOKEN:
            CONSTS();
            break;
        case TYSTRING_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(ERR_TYNUM);
    }

}

void STRINGS()
{
    switch(sym_cour.code)
    {
        case TYSTRING_TOKEN:
        {
            Test_Symbole(TYSTRING_TOKEN,ERR_TYSTRING);
            Test_Symbole(ID_TOKEN,ERR_ID);
            addID();
            offset++;

            while(sym_cour.code == VIR_TOKEN)
            {
                Test_Symbole(VIR_TOKEN, ERR_VIR);
                Test_Symbole(ID_TOKEN,ERR_ID);
                addID();
                offset++;
            }
            Test_Symbole(PV_TOKEN,ERR_PV);
        }
            case CONST_TOKEN:
                CONSTS();
                break;
            case TYNUM_TOKEN:
                NUMERIC();
                break;
            case BEGIN_TOKEN:
                break;
            default:
                Erreur(ERR_TYSTRING);
    }
}

void INSTS()
{
    Test_Symbole(BEGIN_TOKEN,ERR_BEGIN);
    INST();
    while(sym_cour.code == PV_TOKEN)
    {
        Test_Symbole(PV_TOKEN,ERR_PV);
        if(sym_cour.code == RETURN_TOKEN)
            break;
        INST();
    }
    Test_Symbole(RETURN_TOKEN,ERR_RETURN);
    if(sym_cour.code == ID_TOKEN){
        printf("\nFunction returned: %s = value\n", sym_cour.nom); //check if retour type is same as id
        Sym_suiv();
    }
    else if(sym_cour.code == NUM_TOKEN){
        printf("\nFunction returned %s.\n", sym_cour.nom);
        Sym_suiv();
    }
    else if(sym_cour.code == NULL_TOKEN){
        printf("\nFunction returned null.\n");
        Sym_suiv();
    }
    else if(sym_cour.code == PV_TOKEN){
        printf("\nFunction returned null.\n");
    }
    Test_Symbole(PV_TOKEN, ERR_PV);
}

void IF()
{
    Test_Symbole(IF_TOKEN,ERR_IF);
    Test_Symbole(PO_TOKEN,ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN,ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST();
    Test_Symbole(AF_TOKEN, ERR_AF);
    if(sym_cour.code == ELSE_TOKEN)
    {
        Sym_suiv();
        Test_Symbole(AO_TOKEN, ERR_AO);
        INST();
        Test_Symbole(PV_TOKEN, ERR_PV);
        Test_Symbole(AF_TOKEN, ERR_AF);
    }
    else if(sym_cour.code == ELIF_TOKEN)
    {
        ELIF();
    }
}

void ELIF()
{
    Test_Symbole(ELIF_TOKEN, ERR_ELIF);
    Test_Symbole(PO_TOKEN,ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN,ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST();
    Test_Symbole(AF_TOKEN, ERR_AF);
    if(sym_cour.code == ELSE_TOKEN)
    {
        Sym_suiv();
        Test_Symbole(AO_TOKEN, ERR_AO);
        INST();
        Test_Symbole(PV_TOKEN, ERR_PV);
        Test_Symbole(AF_TOKEN, ERR_AF);
    }
    else if(sym_cour.code == ELIF_TOKEN)
    {
        ELIF();
    }
}

void AFFECT()
{
    Test_Symbole(ID_TOKEN, ERR_ID);
    sym symbole = sym_IDprec;
    Test_Symbole(AFF_TOKEN, ERR_AFF);
    if(sym_cour.code == STRING_TOKEN)
    {
        CONCAT();
        ajouter_val(gs_value, sym_IDprec);
    }
    else
    {
        EXPR();
        ajouter_i_val(gi_value, symbole);
    }

}


void WHILE()
{
    Test_Symbole(WHILE_TOKEN,ERR_WHILE);
    Test_Symbole(PO_TOKEN, ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN, ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST();
    Test_Symbole(PV_TOKEN, ERR_PV);
    Test_Symbole(AF_TOKEN, ERR_AF);
}

void DO_WHILE()
{
    Test_Symbole(DO_TOKEN,ERR_DO);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST();
    Test_Symbole(PV_TOKEN, ERR_PV);
    Test_Symbole(AF_TOKEN, ERR_AF);
    Test_Symbole(WHILE_TOKEN,ERR_WHILE);
    Test_Symbole(PO_TOKEN, ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN, ERR_PF);
}

void COND()
{
    int op, c_token;
    switch(sym_cour.code)
    {
        case TRUE_TOKEN:
            Test_Symbole(TRUE_TOKEN, ERR_TRUE);
            break;
        case FALSE_TOKEN:
            Test_Symbole(FALSE_TOKEN, ERR_FALSE);
            break;
        default:
            {
                EXPR();
                switch(sym_cour.code)
                {
                    case EG_TOKEN:
                        {
                            c_token = EG_TOKEN;
                            op = EQL;
                            break;
                        }
                    case DIFF_TOKEN:
                        {
                            c_token = DIFF_TOKEN;
                            op = NEQ;
                            break;
                        }
                    case INF_TOKEN:
                        {
                            c_token = INF_TOKEN;
                            op= LSS;
                            break;
                        }
                    case SUP_TOKEN:
                        {
                            c_token = SUP_TOKEN;
                            op = GTR;
                            break;
                        }
                    case INFEG_TOKEN:
                        {
                            c_token = INFEG_TOKEN;
                            op = LEQ;
                            break;
                        }
                    case SUPEG_TOKEN:
                        {
                            c_token = SUPEG_TOKEN;
                            op = GEQ;
                            break;
                        }
                    default:
                        {
                            c_token = -1;
                        }
                }
                Test_Symbole (c_token, ERR);
                EXPR();
            }
    }
}

void INST()
{
    switch(sym_cour.code)
    {
        case BEGIN_TOKEN:
            {
                INSTS();
                break;
            }
        case ID_TOKEN:
            {
                AFFECT();
                break;
            }
        case IF_TOKEN:
            {
                IF();
                break;
            }
        case WHILE_TOKEN:
            {
                WHILE();
                break;
            }
        case DO_TOKEN:
            {
                DO_WHILE();
                break;
            }
         case FOR_TOKEN:
            {
                FOR();
                break;
            }
        case SCAN_TOKEN:
            {
                SCAN();
                break;
            }
        case PRINT_TOKEN:
            {
               PRINT();
               break;
            }
        case PV_TOKEN:
            {
               break;
            }
        default:
            {
               //Erreur(ERR_INST);
            }
    }
}

void EXPR()
{
    int op;
    float val1=0;
    TERM();
    val1 = gi_value;

    while(sym_cour.code == PLUS_TOKEN || sym_cour.code == MINUS_TOKEN)
    {
        op = sym_cour.code;
        Sym_suiv();
        TERM();
        int val2 = gi_value;
        switch(op)
        {
            case PLUS_TOKEN:
                op = ADD;
                val1 += val2;
                break;
            case MINUS_TOKEN:
                op = SUB;
                val1 -= val2;
                break;
        }
        generer1(op);
    }
    set_i_value(val1);
}

void CONCAT()
{
    /** string + string **/
    int op;
    char phrase1[100];
    Test_Symbole(STRING_TOKEN, ERR_STRING);
    strcpy(phrase1, gs_value);
    while(sym_cour.code == PLUS_TOKEN)
    {
        op = sym_cour.code;
        Sym_suiv();
        Test_Symbole(STRING_TOKEN, ERR_STRING);
        op = CCT;
        strcat(phrase1, gs_value);
    }
    generer1(op);
    strcpy(gs_value, phrase1);
}


void TERM()
{
    int op;
    float valeur=0;
    FACT();
    valeur = gi_value;
    while(sym_cour.code == MULT_TOKEN || sym_cour.code == DIV_TOKEN || sym_cour.code == MOD_TOKEN)
    {
        op = sym_cour.code;
        Sym_suiv();
        FACT();
        int val = gi_value;
        switch(op)
        {
            case MULT_TOKEN:
                op = MUL;
                valeur = valeur * val;
                break;
            case DIV_TOKEN:
                op = DIV;
                if(!val)
                    Erreur_sem(div_zero);
                valeur = valeur / val;
                break;
            case MOD_TOKEN:
                op = MOD;
                if(roundf(valeur) == valeur) //valeur is an integer
                    valeur = (int)valeur%val;
                else
                    Erreur_sem(mod_notInt);
                break;
        }
        generer1(op);
    }
    set_i_value(valeur);
}

void get_i_value_id()
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(sym_cour.nom, TAB_IDFS[i].NOM)==0)
        {
            gi_value = TAB_IDFS[i].i_value;
        }
    }
}

void FACT()
{
    switch(sym_cour.code)
    {
        case ID_TOKEN:
            {
                Test_Symbole(ID_TOKEN, ERR_ID);
                /*if(!ExistInTab(sym_prec))
                    Erreur_sem(not_declared);
                if(isProgId(sym_prec))
                    Erreur_sem(prog_id);

                int id_addr = get_adresse(sym_prec);
                if(id_addr == -1)
                {
                    printf("\n### Error while generating code: Couldn't find id. ###\n");
                    exit(EXIT_FAILURE);
                }
                generer2(LDA, id_addr);
                generer1(LDV);*/

                get_i_value_id();
                printf("i_value of %s is %f.\n", sym_IDprec.nom, gi_value);
                break;
            }
        case NUM_TOKEN:
            {
                Test_Symbole(NUM_TOKEN, ERR_NUM);
                generer2(LDI, gi_value);
                break;
            }
        case PO_TOKEN:
            {
                Test_Symbole(PO_TOKEN, ERR_PO);
                EXPR();
                Test_Symbole(PF_TOKEN, ERR_PF);
            }
        default:
            {
                Erreur(ERR);
            }
    }
}

void FOR()
{
    Test_Symbole(FOR_TOKEN, ERR_FOR);
    Test_Symbole(ID_TOKEN, ERR_ID);
    /*if(!ExistInTab(sym_prec))
        Erreur_sem(not_declared);
    int err = isVar(sym_prec);
    if(err ==0)
            Erreur_sem(const_aff);
    else if(err == -1)
            Erreur_sem(prog_id);
*/
    Test_Symbole(IN_TOKEN, ERR_IN);
    Test_Symbole(NUM_TOKEN, ERR_NUM);
    Test_Symbole(DPT_TOKEN, ERR_DPT);
    Test_Symbole(NUM_TOKEN, ERR_NUM);
    switch(sym_cour.code)
    {
        case DESC_TOKEN:
            Test_Symbole(DESC_TOKEN, ERR_DESC);
            break;
        case ASC_TOKEN:
            Test_Symbole(ASC_TOKEN, ERR_ASC);
            break;
        default:
            Erreur(ERR);
    }
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST();
    Test_Symbole(PV_TOKEN, ERR_PV);
    Test_Symbole(AF_TOKEN, ERR_AF);
}


void SCAN()
{
     Test_Symbole(SCAN_TOKEN, ERR_SCAN);
     Test_Symbole(PO_TOKEN, ERR_PO);
     Test_Symbole(ID_TOKEN, ERR_ID);
     /*if(!ExistInTab(sym_prec))
        Erreur_sem(not_declared);
     int err = isVar(sym_prec);
     if(err ==0)
        Erreur_sem(const_aff);
     else if(err == -1)
        Erreur_sem(prog_id);

     int id_addr = get_adresse(sym_prec);
     if(id_addr == -1)
     {
         printf("\n### Error while generating code: Couldn't find id. ###\n");
         exit(EXIT_FAILURE);
     }
     generer2(LDA, id_addr);*/
     generer1(INN);

     while(sym_cour.code== VIR_TOKEN){
        Test_Symbole(VIR_TOKEN, ERR_VIR);
        Test_Symbole(ID_TOKEN, ERR_ID);
       /* if(!ExistInTab(sym_prec))
            Erreur_sem(not_declared);
        int err = isVar(sym_prec);
        if(err ==0)
                Erreur_sem(const_aff);
        else if(err == -1)
                Erreur_sem(prog_id);

        int id_addr = get_adresse(sym_prec);
        if(id_addr == -1)
        {
            printf("\n### Error while generating code: Couldn't find id. ###\n");
            exit(EXIT_FAILURE);
        }
        generer2(LDA, id_addr);
        generer1(INN);*/
     }
     Test_Symbole(PF_TOKEN, ERR_PF);
     if(sym_cour.code != PV_TOKEN)
        Erreur(ERR_PV);
}

void PRINT()
{
     Test_Symbole(PRINT_TOKEN, ERR_PRINT);
     Test_Symbole(PO_TOKEN, ERR_PO);
     if(sym_cour.code == STRING_TOKEN)
        CONCAT();
     else
        EXPR();
     /*if(!ExistInTab(sym_prec))
        Erreur_sem(not_declared);

     int id_addr = get_adresse(sym_prec);
     if(id_addr == -1)
     {
         printf("\n### Error while generating code: Couldn't find id. ###\n");
         exit(EXIT_FAILURE);
     }
     generer2(LDA, id_addr);
     generer1(LDV);
     generer1(PRN);*/

     while(sym_cour.code== VIR_TOKEN){
        Test_Symbole(VIR_TOKEN, ERR_VIR);
        if(sym_cour.code == STRING_TOKEN)
            CONCAT();
         else
            EXPR();
        /*if(!ExistInTab(sym_prec))
            Erreur_sem(not_declared);
        if(isProgId(sym_prec))
            Erreur_sem(prog_id);

        int id_addr = get_adresse(sym_prec);
         if(id_addr == -1)
         {
             printf("\n### Error while generating code: Couldn't find id. ###\n");
             exit(EXIT_FAILURE);
         }
         generer2(LDA, id_addr);
         generer1(LDV);
         generer1(PRN);*/
     }
     Test_Symbole(PF_TOKEN, ERR_PF);
     if(sym_cour.code != PV_TOKEN)
        Erreur(ERR_PV);
}


