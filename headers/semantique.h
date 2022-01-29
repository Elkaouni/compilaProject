typedef struct
{
    int code; //token
    char nom[20];
}sym;

typedef enum {
    TCONSTNUM,
    TCONTSTRING,
    TNUM,
    TSTRING,
    TNULL
} TSYM; //type symbole

typedef struct {
    char NOM[20];
    TSYM TIDF;
    float value;
} T_TAB_IDF;





int isNotDoubleDec(sym symbole, T_TAB_IDF* TAB_IDFS, int sizeTAB)
{
    int i=0;
    for(i=0; i<sizeTAB; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            printf("ATTENTION DOUBLE DECLARATION  of %s!",symbole.nom);
            return 0;
        }
    }
    return 1;
}
int isDeclared(sym symbole, T_TAB_IDF* TAB_IDFS, int sizeTAB)
{
    int i=0;
    for(i=0; i<sizeTAB; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            return 1;
        }
    }
    printf("ATTENTION %s not declared!",symbole.nom);
    return 0;
}
int isConstAFF(sym symbole, T_TAB_IDF* TAB_IDFS, int sizeTAB)
{
    int i=0;
    for(i=0; i<sizeTAB; i++)
    {
        if(strcmp(symbole.nom,TAB_IDFS[i].NOM)== 0)
        {
            switch(TAB_IDFS[i].TIDF)
            {
            case TSTRING:
            case TNUM:
                {
                    return 1;
                }
            case TNULL:
            case TCONSTNUM:
            case TCONSTSTRIN:
            default:
                {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int isNumericType(sym symbole, T_TAB_IDF* TAB_IDFS, int sizeTAB)
{
    int i=0;
    for(i=0; i<sizeTAB; i++)
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

int isStringType(sym symbole, T_TAB_IDF* TAB_IDFS, int sizeTAB)
{
    int i=0;
    for(i=0; i<sizeTAB; i++)
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

