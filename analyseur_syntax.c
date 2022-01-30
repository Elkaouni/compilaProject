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

int isConstAFF(sym symbole)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            switch(TAB_IDFS[i].TIDF)
            {
            case TSTRING:
            case TNUM:
                {
                    return 0;
                }
            case TNULL:
            case TCONSTNUM:
            case TCONSTSTRING:
            default:
                {
                    return 1;
                }
            }
        }
    }
    return 1;
}


int ig_main_return_type;
int IDmatchMainReturnType(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            if( (TAB_IDFS[i].TIDF== TCONSTNUM || TAB_IDFS[i].TIDF==TNUM) &&
               ig_main_return_type== TYNUM_TOKEN)
                return 1;
            else if( (TAB_IDFS[i].TIDF== TCONSTSTRING || TAB_IDFS[i].TIDF==TSTRING) &&
               ig_main_return_type== TYSTRING_TOKEN)
                return 1;
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


/*************************************
   Using and Getting an ID's value from the table
*************************************/
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
void get_value_id(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            if(TAB_IDFS[i].TIDF == TCONSTSTRING || TAB_IDFS[i].TIDF == TSTRING)
                strcpy(gs_value,TAB_IDFS[i].value);
        }
    }
}

void get_i_value_id(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            if(TAB_IDFS[i].TIDF == TCONSTNUM || TAB_IDFS[i].TIDF == TNUM)
                set_i_value(TAB_IDFS[i].i_value);
        }
    }
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
            strcpy(gs_value, sym_cour.nom);
        }

        //printf("Done with nom->%s  code->%s\n", sym_cour.nom, token_names[sym_cour.code]);
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

void MAIN()
{
    /**Main ( [type arg [, type arg}] ) : [ num| string | NULL] {
        DECLARATIONS() ;
        INSTS() ;
        }**/
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
                if(!ExistInTab(sym_IDprec))
                    addID();
                else
                    Erreur_sem(double_dec);
                break;
            case TYSTRING_TOKEN:
                Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
                Test_Symbole(ID_TOKEN, ERR_ID);
                if(!ExistInTab(sym_IDprec))
                    addID();
                else
                    Erreur_sem(double_dec);
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
     /**
	CONSTS() ;
	NUMERIC() ;
	STRINGS() ;
**/
     CONSTS();
     NUMERIC();
     STRINGS();
}

void CONSTS()
{
    /**const type ID= VAL [, type ID=VAL] ; | eps**/
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
            if(!ExistInTab(sym_IDprec))
                addID();
            else
                Erreur_sem(double_dec);
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
                if(!ExistInTab(sym_IDprec))
                    addID();
                else
                    Erreur_sem(double_dec);
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
    /**num ID [, ID ] ; | eps**/
    switch(sym_cour.code)
    {
        case TYNUM_TOKEN:
            {
                Test_Symbole(TYNUM_TOKEN,ERR_TYNUM);
                Test_Symbole(ID_TOKEN,ERR_ID);
                if(!ExistInTab(sym_IDprec))
                    addID();
                else
                    Erreur_sem(double_dec);
                offset++;

                while(sym_cour.code == VIR_TOKEN)
                {
                    Test_Symbole(VIR_TOKEN, ERR_VIR);
                    Test_Symbole(ID_TOKEN,ERR_ID);
                    if(!ExistInTab(sym_IDprec))
                        addID();
                    else
                        Erreur_sem(double_dec);
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
    /**string ID [, ID ] ; |eps**/
    switch(sym_cour.code)
    {
        case TYSTRING_TOKEN:
        {
            Test_Symbole(TYSTRING_TOKEN,ERR_TYSTRING);
            Test_Symbole(ID_TOKEN,ERR_ID);
            if(!ExistInTab(sym_IDprec))
                addID();
            else
                Erreur_sem(double_dec);
            offset++;

            while(sym_cour.code == VIR_TOKEN)
            {
                Test_Symbole(VIR_TOKEN, ERR_VIR);
                Test_Symbole(ID_TOKEN,ERR_ID);
                if(!ExistInTab(sym_IDprec))
                    addID();
                else
                    Erreur_sem(double_dec);
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
    /** begin
    INST() { ; INST()}
    return [ ID | NUM | NULL | eps ];``**/
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
        if(!ExistInTab(sym_IDprec))
            Erreur_sem(not_declared);
        if(!IDmatchMainReturnType(sym_cour))
            Erreur_sem(return_type);
        if(isStringType(sym_cour))
        {
            get_value_id(sym_cour);
            printf("\nFunction returned: %s = %s\n", sym_cour.nom, gs_value);
        }
        else
        {
            get_i_value_id(sym_cour);
            printf("\nFunction returned: %s = %.2f\n", sym_cour.nom, gi_value);
        }

        Sym_suiv();
    }
    else if(sym_cour.code == NUM_TOKEN){
        if(ig_main_return_type== TYNUM_TOKEN)
        {
            printf("\nFunction returned %s.\n", sym_cour.nom);
            Sym_suiv();
        }
        else
            Erreur_sem(return_type);
    }
    else if(sym_cour.code == STRING_TOKEN){
        if(ig_main_return_type== TYSTRING_TOKEN)
        {
            printf("\nFunction returned %s.\n", sym_cour.nom);
            Sym_suiv();
        }
        else
            Erreur_sem(return_type);
    }
    else if(sym_cour.code == NULL_TOKEN){
        if(ig_main_return_type== NULL_TOKEN)
        {
            printf("\nFunction returned null.\n");
            Sym_suiv();
        }
        else
            Erreur_sem(return_type);
    }
    else if(sym_cour.code == PV_TOKEN){
        if(ig_main_return_type== NULL_TOKEN)
        {
            printf("\nFunction returned null.\n");
        }
        else
            Erreur_sem(return_type);
    }
    Test_Symbole(PV_TOKEN, ERR_PV);
}

void IF()
{
    /** If ( COND() ) { INST() ; }
    [ else { INST () ; } | ELIF() ]***/
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
    /**elif ( COND() ) { INST() }
    [ else { INST();} |ELIF() ]**/
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
    /** ID = EXPR() | CONCAT() ;**/
    Test_Symbole(ID_TOKEN, ERR_ID);
    if(!ExistInTab(sym_IDprec))
        Erreur_sem(not_declared);
    if(isConstAFF(sym_IDprec))
        Erreur_sem(const_aff);

    sym symbole = sym_IDprec;
    Test_Symbole(AFF_TOKEN, ERR_AFF);
    if(isStringType(sym_IDprec))
    {
        CONCAT();
        ajouter_val(gs_value, symbole);
    }
    else if(isNumericType(sym_IDprec))
    {
        EXPR();
        ajouter_i_val(gi_value, symbole);
    }
    else
        Erreur_sem(op_num_string);
}


void WHILE()
{
    /** while( COND){ INST() } ;**/
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
    /**do{ INST ()} while(COND() ) ;**/
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
    /**EXPR RELOP EXPR | true | false**/
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
    /**INSTS() | AFFEC |IF |WHILE |DO_WHILE |FOR | SCAN |PRINT |eps**/
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
    /**TERM [ ADDOP TERM]**/
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
    /** words()  + words() **/
    int op;
    char phrase1[100];
    //Test_Symbole(STRING_TOKEN, ERR_STRING);
    WORDS();
    strcpy(phrase1, gs_value);
    while(sym_cour.code == PLUS_TOKEN)
    {
        Sym_suiv();
        //Test_Symbole(STRING_TOKEN, ERR_STRING);
        WORDS();
        strcat(phrase1, gs_value);
    }
    strcpy(gs_value, phrase1);
}


void WORDS()
{
    /**ID | STRING **/
    switch(sym_cour.code)
    {
        case ID_TOKEN:
            {
                Test_Symbole(ID_TOKEN, ERR_ID);
                if(!ExistInTab(sym_IDprec))
                    Erreur_sem(not_declared);
                if(!isStringType(sym_IDprec))
                    Erreur_sem(op_num_string);
                get_value_id(sym_IDprec);
                break;
            }
        case STRING_TOKEN:
            {
                Test_Symbole(STRING_TOKEN, ERR_STRING);
                break;
            }
        default:
            Erreur(ERR);
    }
}

void TERM()
{
    /**FACT [ MULOP FACT]**/
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

void FACT()
{
    /**ID | NUM | (EXPR)**/
    switch(sym_cour.code)
    {
        case ID_TOKEN:
            {
                Test_Symbole(ID_TOKEN, ERR_ID);
                if(!ExistInTab(sym_IDprec))
                    Erreur_sem(not_declared);
                if(!isNumericType(sym_IDprec))
                    Erreur_sem(op_num_string);
                get_i_value_id(sym_IDprec);
                break;
            }
        case NUM_TOKEN:
            {
                Test_Symbole(NUM_TOKEN, ERR_NUM);
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
    /**for ID in EXPR : EXPR [desc | asc]  { INST (); }**/
    Test_Symbole(FOR_TOKEN, ERR_FOR);
    Test_Symbole(ID_TOKEN, ERR_ID);
    if(!ExistInTab(sym_IDprec))
        Erreur_sem(not_declared);
    if(isConstAFF(sym_IDprec))
        Erreur_sem(const_aff);
    if(!isNumericType(sym_IDprec))
        Erreur_sem(op_num_string);

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
     /**scan( id [ , id]) ;**/
     Test_Symbole(SCAN_TOKEN, ERR_SCAN);
     Test_Symbole(PO_TOKEN, ERR_PO);
     Test_Symbole(ID_TOKEN, ERR_ID);
     if(!ExistInTab(sym_IDprec))
        Erreur_sem(not_declared);
     if(isConstAFF(sym_IDprec))
        Erreur_sem(const_aff);

     while(sym_cour.code== VIR_TOKEN)
     {
        Test_Symbole(VIR_TOKEN, ERR_VIR);
        Test_Symbole(ID_TOKEN, ERR_ID);
        if(!ExistInTab(sym_IDprec))
            Erreur_sem(not_declared);
        if(isConstAFF(sym_IDprec))
            Erreur_sem(const_aff);
     }
     Test_Symbole(PF_TOKEN, ERR_PF);
     if(sym_cour.code != PV_TOKEN)
        Erreur(ERR_PV);
}

void PRINT()
{
     /**print(EXPR|CONCAT [,EXPR|CONCAT])**/
     Test_Symbole(PRINT_TOKEN, ERR_PRINT);
     Test_Symbole(PO_TOKEN, ERR_PO);
     if(sym_cour.code == STRING_TOKEN)
        CONCAT();
     else
        EXPR();

     while(sym_cour.code== VIR_TOKEN){
        Test_Symbole(VIR_TOKEN, ERR_VIR);
        if(sym_cour.code == STRING_TOKEN || isStringType(sym_cour))
            CONCAT();
         else
            EXPR();
     }
     Test_Symbole(PF_TOKEN, ERR_PF);
     if(sym_cour.code != PV_TOKEN)
        Erreur(ERR_PV);
}


