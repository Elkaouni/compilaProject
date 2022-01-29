static char* token_names[] = { "MAIN_TOKEN", "TYSTRING_TOKEN",
		"CONST_TOKEN"  , "TYNUM_TOKEN" , "NULL_TOKEN"  , "INTLIT_TOKEN",
		"DECLARE_TOKEN", "END_TOKEN"   , "BEGIN_TOKEN" , "RETURN_TOKEN",
        "TRUE_TOKEN"   , "FALSE_TOKEN" , "IF_TOKEN"    , "ELSE_TOKEN"  ,
        "ELIF_TOKEN"   , "WHILE_TOKEN" , "DO_TOKEN"    , "FOR_TOKEN"   ,
		"SCAN_TOKEN"   , "IN_TOKEN"    , "PRINT_TOKEN" , "STRING_TOKEN",
		"ID_TOKEN"     , "NUM_TOKEN"   , "DESC_TOKEN"  , "ASC_TOKEN"   ,

		"PV_TOKEN"     , "PT_TOKEN"    , "DPT_TOKEN"   , "VIR_TOKEN"   ,
		"AFF_TOKEN"    , "INF_TOKEN"   , "INFEG_TOKEN" , "SUP_TOKEN"   ,
		"SUPEG_TOKEN"  , "DIFF_TOKEN"  , "PO_TOKEN"    , "PF_TOKEN"    ,
		"PLUS_TOKEN"   , "MINUS_TOKEN" , "MULT_TOKEN"  , "MOD_TOKEN"   ,
		"EG_TOKEN"     , "DIV_TOKEN"   , "AO_TOKEN"    , "AF_TOKEN"    ,
		"CO_TOKEN"     , "CF_TOKEN"    , "COMM_TPKEN"  , "EOF_TOKEN"   ,
		"ERR_TOKEN"
    };

typedef struct
{
	enum
	{
		MAIN_TOKEN  ,

		TYSTRING_TOKEN,
		CONST_TOKEN ,
		TYNUM_TOKEN ,
		NULL_TOKEN  ,

		INTLIT_TOKEN,
		DECLARE_TOKEN ,
		END_TOKEN   ,
		BEGIN_TOKEN ,
		RETURN_TOKEN,
        TRUE_TOKEN  ,
        FALSE_TOKEN ,
        IF_TOKEN    ,
        ELSE_TOKEN  ,
        ELIF_TOKEN  ,
        WHILE_TOKEN ,
        DO_TOKEN    ,
        FOR_TOKEN   ,
		SCAN_TOKEN  ,
		IN_TOKEN    ,
		PRINT_TOKEN ,
		STRING_TOKEN,
		ID_TOKEN    ,
		NUM_TOKEN   ,
		DESC_TOKEN  ,
        ASC_TOKEN   ,

		PV_TOKEN    , // ;
		PT_TOKEN    , // .
		DPT_TOKEN   , // :
		VIR_TOKEN   , // ,
		AFF_TOKEN   , // =
		INF_TOKEN   , // <
		INFEG_TOKEN , // <=
		SUP_TOKEN   , // >
		SUPEG_TOKEN , // >=
		DIFF_TOKEN  , // !=
		PO_TOKEN    , // (
		PF_TOKEN    , // )
		PLUS_TOKEN  , // +
		MINUS_TOKEN , // -
		MULT_TOKEN  , // *
		MOD_TOKEN   , // %
		EG_TOKEN    , // ==
		DIV_TOKEN   , // /
		AO_TOKEN    , // {
		AF_TOKEN    , // }
		CO_TOKEN    , // /*
		CF_TOKEN    , // */
		COMM_TOKEN  ,
		EOF_TOKEN
	} type;
	char *value;
} Token;

Token *token_init(int type, char *value);
