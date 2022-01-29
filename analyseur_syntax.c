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


sym sym_cour, sym_precPCV, sym_prec;

static int index =0;
static T_TAB_IDF TAB_IDFS[100];
int ExistInTab(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
            return 1;
    }
    return 0;
}
int isVar(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            if(TAB_IDFS[i].TIDF != TVAR)
            {
                if(TAB_IDFS[i].TIDF == TPROG)
                    return 0;
                else
                    return -1;
            }
            else
                return 1;
        }
    }
    return 0;
}
int isProgId(sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
        {
            if(TAB_IDFS[i].TIDF != TPROG)
                return 0;
            else
                return 1;
        }
    }
    return 0;
}

void ajouter(sym symbole,int type)
{
    strcpy(TAB_IDFS[index].NOM, symbole.nom);
    TAB_IDFS[index].TIDF = type;
    index++;
}
void ajouter_val(float val, sym symbole)
{
    for(int i=0; i<index; i++)
    {
        if(strcmp(symbole.nom, TAB_IDFS[i].NOM)==0)
            TAB_IDFS[i].value = val;
    }
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

static char* type[] = {"TCONSTINT", "TCONTSTRING", "TINT", "TSTRING"};
void printTAB_IDFS()
{
    int i=0;
    printf("Printing saved program id, consts and vars:\n");
    for(i = 0; i<index; i++)
    {
        printf("symbole: %s\t\ttype: %s\t\tvalue: %.1f\n", TAB_IDFS[i].NOM, type[TAB_IDFS[i].TIDF], TAB_IDFS[i].value);
    }
}


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

float value;
void set_value(float val)
{
    value = val;
}
void Test_Symbole (int token, int COD_ERR)
{
   printf("\nChecking sym cour: nom->%s  code->%s\n", sym_cour.nom, token_names[sym_cour.code]);
   while(sym_cour.code == COMM_TOKEN)
   {
       Sym_suiv();
   }
  if(sym_cour.code == token)
    {
        /*if(sym_cour.code == PROGRAM_TOKEN)
            sym_precPCV = sym_cour;
        else if(sym_cour.code == CONST_TOKEN)
            sym_precPCV = sym_cour;
        else if(sym_cour.code == VAR_TOKEN)
            sym_precPCV = sym_cour;

        else if(sym_cour.code == ID_TOKEN)
        {
            sym_prec = sym_cour;
        }
        else if(sym_cour.code == NUM_TOKEN)
        {
            value = atoi(sym_cour.nom);
        }
        */
        printf("Done. Next...\n");
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

void addID()
{
   /* if(strcmp(sym_precPCV.nom, "program")==0)
        ajouter(sym_prec, TPROG);

    else if(sym_precPCV.code == CONST_TOKEN)
    {
        ajouter(sym_prec, TCONST);
    }
     else if(sym_precPCV.code == VAR_TOKEN)
    {
        ajouter(sym_prec, TVAR);
    }*/
}

 // Starting code generation

void MAIN() //code generated
{
  //  printLexer();
    Test_Symbole(MAIN_TOKEN, ERR_MAIN);
    Test_Symbole(PO_TOKEN, ERR_PO);
    int args;
    do{
        args =0;
        switch(sym_cour.code)
        {
            case NULL_TOKEN:
                Test_Symbole(NULL_TOKEN, ERR_NULL);
                Test_Symbole(ID_TOKEN, ERR_ID);
                break;
            case TYNUM_TOKEN:
                Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
                Test_Symbole(ID_TOKEN, ERR_ID);
                break;
            case TYSTRING_TOKEN:
                Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
                Test_Symbole(ID_TOKEN, ERR_ID);
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
    //args
    Test_Symbole(PF_TOKEN, ERR_PF);
    Test_Symbole(DPT_TOKEN, ERR_DPT);
    switch(sym_cour.code)
    {
        case TYSTRING_TOKEN:
            Test_Symbole(TYSTRING_TOKEN, ERR_TYSTRING);
            break;
        case TYNUM_TOKEN:
            Test_Symbole(TYNUM_TOKEN, ERR_TYNUM);
            break;
        case NULL_TOKEN:
            Test_Symbole(NULL_TOKEN, ERR_NULL);
            break;
        default:
            Erreur(ERR);
    }
    Test_Symbole(AO_TOKEN, ERR_AO);
    DECLARE();
    INSTS();
    generer1(HLT);
    Test_Symbole(AF_TOKEN, ERR_AF);

    printf("\n------->Done :) \n");
  //  printf("\n_________________________\n");
 //   printTAB_IDFS(TAB_IDFS, index);
  //  printf("_________________________\n");
   // print_code();
      //SavePCodeToFile(FILE_SORTIE);
  //  printf("\nSaved in file \"result.rh\".   \n");
}

void DECLARE() //code generated
{
     CONSTS();
     NUMERIC();
     STRINGS();
    generer2(INT, offset);
}

void CONSTS() //code generated
{
    //const ID = NUM ; { ID = NUM ; } | e
    switch(sym_cour.code)
    {
        case CONST_TOKEN:
        {
            Test_Symbole(CONST_TOKEN,ERR_CONST);
            int typeID = -1;

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
            Test_Symbole(ID_TOKEN,ERR_ID); //sym_prec saved
            Test_Symbole(AFF_TOKEN,ERR_AFF);
            if(typeID==TYNUM_TOKEN)
                Test_Symbole(NUM_TOKEN,ERR_NUM); //value saved
            else{
                if(typeID == TYSTRING_TOKEN){
                    Test_Symbole(STRING_TOKEN, ERR_STRING);
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
                Test_Symbole(ID_TOKEN,ERR_ID); //sym_prec saved

                Test_Symbole(AFF_TOKEN,ERR_AFF);
                if(typeID==TYNUM_TOKEN)
                    Test_Symbole(NUM_TOKEN,ERR_NUM); //value saved
                else{
                    if(typeID == TYSTRING_TOKEN){
                        Test_Symbole(STRING_TOKEN, ERR_STRING);
                    }
                    else
                        Erreur(ERR);
                }
            }
            Test_Symbole(PV_TOKEN,ERR_PV);
            generer1(STO);
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
    // num ID [, ID ] ; | eps
    switch(sym_cour.code)
    {
        case TYNUM_TOKEN:
            {
                Test_Symbole(TYNUM_TOKEN,ERR_TYNUM);
                Test_Symbole(ID_TOKEN,ERR_ID);
                offset++;

                while(sym_cour.code == VIR_TOKEN)
                {
                    Test_Symbole(VIR_TOKEN, ERR_VIR);
                    Test_Symbole(ID_TOKEN,ERR_ID);
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
    // num ID [, ID ] ; | eps
    switch(sym_cour.code)
    {
        case TYSTRING_TOKEN:
        {
            Test_Symbole(TYSTRING_TOKEN,ERR_TYSTRING);
            Test_Symbole(ID_TOKEN,ERR_ID);
            offset++;

            while(sym_cour.code == VIR_TOKEN)
            {
                //Sym_suiv();
                Test_Symbole(VIR_TOKEN, ERR_VIR);
                Test_Symbole(ID_TOKEN,ERR_ID);
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

void INSTS() //code generated
{
    // begin  INST() { ; INST()} return [ ID | NULL ];
    Test_Symbole(BEGIN_TOKEN,ERR_BEGIN);
    INST();
    while(sym_cour.code == PV_TOKEN)
    {
        Test_Symbole(PV_TOKEN,ERR_PV); //Sym_suiv()
        if(sym_cour.code == RETURN_TOKEN)
            break;
        INST(); //génère son code
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

void IF() // code generated
{
    /*If ( COND() ) { INST() ; }
    [ else { INST () ; } |ELIF() ] */
    Test_Symbole(IF_TOKEN,ERR_IF);
    Test_Symbole(PO_TOKEN,ERR_PO);
    COND(); //genere son code
    Test_Symbole(PF_TOKEN,ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST(); //genere son code
    Test_Symbole(AF_TOKEN, ERR_AF);
    if(sym_cour.code == ELSE_TOKEN)
    {
        Sym_suiv();
        Test_Symbole(AO_TOKEN, ERR_AO);
        INST(); //genere son code
        Test_Symbole(PV_TOKEN, ERR_PV);
        Test_Symbole(AF_TOKEN, ERR_AF);
        //genererBZE(addr_cond,PC);
    }
    else if(sym_cour.code == ELIF_TOKEN)
    {
        ELIF(); //génère son code
    }
}

void ELIF()
{
    Test_Symbole(ELIF_TOKEN, ERR_ELIF);
    Test_Symbole(PO_TOKEN,ERR_PO);
    COND(); //genere son code
    Test_Symbole(PF_TOKEN,ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST(); //genere son code
    Test_Symbole(AF_TOKEN, ERR_AF);
    if(sym_cour.code == ELSE_TOKEN)
    {
        Sym_suiv();
        Test_Symbole(AO_TOKEN, ERR_AO);
        INST(); //genere son code
        Test_Symbole(PV_TOKEN, ERR_PV);
        Test_Symbole(AF_TOKEN, ERR_AF);
        //genererBZE(addr_cond,PC);
    }
    else if(sym_cour.code == ELIF_TOKEN)
    {
        ELIF(); //génère son code
    }
}

void AFFECT()
{
    // AFFEC ::= ID := EXPR
    Test_Symbole(ID_TOKEN, ERR_ID);
    Test_Symbole(AFF_TOKEN, ERR_AFF);
    if(sym_cour.code == STRING_TOKEN)
        Test_Symbole(STRING_TOKEN, ERR_STRING);
    else
        EXPR();
    //Test_Symbole(PV_TOKEN, ERR_PV);
}

void WHILE()
{
    // while( COND){ INST() } ;
    Test_Symbole(WHILE_TOKEN,ERR_WHILE);
    Test_Symbole(PO_TOKEN, ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN, ERR_PF);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST(); //génère son code
    Test_Symbole(PV_TOKEN, ERR_PV);
    Test_Symbole(AF_TOKEN, ERR_AF);
}

void DO_WHILE()
{
    Test_Symbole(DO_TOKEN,ERR_DO);
    Test_Symbole(AO_TOKEN, ERR_AO);
    INST(); //génère son code
    Test_Symbole(PV_TOKEN, ERR_PV);
    Test_Symbole(AF_TOKEN, ERR_AF);
    Test_Symbole(WHILE_TOKEN,ERR_WHILE);
    Test_Symbole(PO_TOKEN, ERR_PO);
    COND();
    Test_Symbole(PF_TOKEN, ERR_PF);
    //Test_Symbole(PV_TOKEN, ERR_PV);
}

void COND() // code generated
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

void INST() //code generated
{
    // INSTS | AFFEC | SI | TANTQUE | ECRIRE; | LIRE; | e
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
                SCAN(); //sym_cour = PV_TOKEN //génère son code
                break;
            }
        case PRINT_TOKEN:
            {
               PRINT();  //sym_cour = PV_TOKEN //génère son code
               break;
            }
        case PV_TOKEN:
            {
               //Test_Symbole(PV_TOKEN, ERR_PV);

               break;
            }
        default:
            {
               //Erreur(ERR_INST);
            }
    }
}

void EXPR() //code generated
{
    // TERM { [+ | -] TERM }
    int op;
    float valeur=0;
    TERM(); //recupère value //genere son code
   // valeur = value;

    while(sym_cour.code == PLUS_TOKEN || sym_cour.code == MINUS_TOKEN)
    {
        op = sym_cour.code;
        Sym_suiv();
        printf("Checked PLUS_TOKEN / Minus_token\n");

        TERM(); //recupère value //genere son code
        int val = value;
        switch(op)
        {
            case PLUS_TOKEN:
                op = ADD;
                valeur += val;
                break;
            case MINUS_TOKEN:
                op = SUB;
                valeur -= val;
                break;
        }
        generer1(op);
    }
   // set_value(valeur);
}

void TERM() // code generated
{
    // FACT { [* | /] FACT }
    int op;
    float valeur=0;
    FACT(); // get value //genere son code
    valeur = value;
    while(sym_cour.code == MULT_TOKEN || sym_cour.code == DIV_TOKEN)
    {
        op = sym_cour.code;
        Sym_suiv();
        //printf("Checked mult_token / div_token");
        FACT(); // get value //genere son code
        int val =value;
        switch(op)
        {
            case MULT_TOKEN:
                op = MUL;
              //  valeur = valeur * val;
                break;
            case DIV_TOKEN:
                op = DIV;
              /*  if(!val)
                    Erreur_sem(div_zero);
                valeur = valeur / val;*/
                break;
            case MOD_TOKEN:
                op = MOD;
               /* if(!val)
                    Erreur_sem(div_zero);
                valeur = valeur / val;*/
                break;
        }
        generer1(op);
    }
    set_value(valeur);
}

void get_value_id()
{
    /*for(int i=0; i<index; i++)
    {
        if(strcmp(sym_cour.nom, TAB_IDFS[i].NOM)==0)
        {
           // value = TAB_IDFS[i].value;
        }
    }*/
}

void FACT() //generate code
{
    // ID | NUM | ( EXPR )
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
                generer1(LDV);

                get_value_id();
                printf("value of %s is %f.\n", sym_prec.nom, value);
                */
                break;
            }
        case NUM_TOKEN:
            {
                Test_Symbole(NUM_TOKEN, ERR_NUM); //get value
               // generer2(LDI, value);
                break;
            }
        case PO_TOKEN:
            {
                //Sym_suiv();
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
     // Read(ID*,{ID}*);
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
     generer2(LDA, id_addr);
     generer1(INN);*/

     while(sym_cour.code== VIR_TOKEN){
        //Sym_suiv();
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
     //Test_Symbole(PV_TOKEN, ERR_PV);
     if(sym_cour.code != PV_TOKEN)
        Erreur(ERR_PV);
}

void PRINT()
{
     // write(ID*,{ID}*);
     Test_Symbole(PRINT_TOKEN, ERR_PRINT);
     Test_Symbole(PO_TOKEN, ERR_PO);
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
        //Sym_suiv();
        Test_Symbole(VIR_TOKEN, ERR_VIR);
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
     //Test_Symbole(PV_TOKEN, ERR_PV);
}


