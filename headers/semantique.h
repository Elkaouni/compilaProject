typedef struct
{
    int code; //token
    char nom[20];
}sym;

typedef enum {
    TPROG,
    TCONST,
    TVAR
} TSYM; //type symbole

typedef struct {
    char NOM[20];
    TSYM TIDF;
    float value;
} T_TAB_IDF;







int isNotDoubleDec(sym symbole, T_TAB_IDF* TAB_IDFS, int index)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            printf("ATTENTION DOUBLE DECLARATION  de %s!",symbole.nom);
            return 0;

        }
    }
    return 1;
}
int isDeclared(sym symbole, T_TAB_IDF* TAB_IDFS, int index)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            return 1;
        }
    }
    printf("ATTENTION %s non déclaré!",symbole.nom);
    return 0;
}
int isConstAFF(sym symbole, T_TAB_IDF* TAB_IDFS, int index)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            switch(TAB_IDFS[i].TIDF)
            {
            case TVAR:
                {
                    return 1;
                }
            case TPROG:
            case TCONST:
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int checkIDProg(sym symbole, T_TAB_IDF* TAB_IDFS, int index)
{
    int i=0;
    for(i=0; i<index; i++)
    {
        if(TAB_IDFS[i].TIDF== TPROG)
        {
            if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
            {
                return -1; //erruer
            }
        }
    }
    return 1;
}


