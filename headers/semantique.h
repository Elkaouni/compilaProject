    typedef struct
{
    int code; //token
    char nom[20];
}sym;

typedef enum {
    TCONSTNUM,
    TCONSTSTRING,
    TNUM,
    TSTRING,
    TNULL
} TSYM; //type symbole

typedef struct {
    char NOM[20];
    TSYM TIDF;
    float i_value; //if value is numeric
    char value[100]; //if value is a string
} T_TAB_IDF;


