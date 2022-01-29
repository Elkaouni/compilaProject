typedef struct{
    enum{
        ERR,
        ERR_MAIN,
		ERR_TYSTRING,
		ERR_CONST  ,
		ERR_TYNUM  ,
		ERR_NULL   ,
		ERR_INTLIT ,
		ERR_DECLARE,
		ERR_END   ,
		ERR_BEGIN ,
		ERR_RETURN,
        ERR_TRUE  ,
        ERR_FALSE ,
        ERR_IF    ,
        ERR_ELSE  ,
        ERR_ELIF  ,
        ERR_WHILE ,
        ERR_DO    ,
        ERR_FOR   ,
		ERR_SCAN  ,
		ERR_IN    ,
		ERR_PRINT ,
		ERR_STRING,
		ERR_ID    ,
		ERR_NUM   ,
		ERR_DESC  ,
        ERR_ASC   ,

		ERR_PV   ,
		ERR_PT   ,
		ERR_DPT  ,
		ERR_VIR  ,
		ERR_AFF  ,
		ERR_INF  ,
		ERR_INFEG,
		ERR_SUP  ,
		ERR_SUPEG,
		ERR_DIFF ,
		ERR_PO   ,
		ERR_PF   ,
		ERR_PLUS ,
		ERR_MINUS,
		ERR_MULT ,
		ERR_MOD  ,
		ERR_EG   ,
		ERR_DIV  ,
		ERR_AO  ,
		ERR_AF   ,
		ERR_CO   ,
		ERR_CF   ,
		ERR_COMM ,
		ERR_EOF  ,
		ERR_TOKEN
    } error_type;
} Erreurs;

enum{
    not_declared,
    double_dec,
    const_aff,
    div_zero,
    prog_id
}err_sem;

void Erreur(int cod_err);
void Erreur_sem(int cod);

