# Projet Compilation S3
(lexer and parser done. Next is semantic analysis and code generator.)
Dans le cadre du projet de compilation de S3, nous avons décider de proposer un nouveau language inspiré de Pascal, C et Java. C'est un language assez simple vue le temps alloué au projet. Ci-dessous notre grammaire.

# Grammaire du language PasC-mini
## 1.1. Les types existants
- Const
- Num (numeric)
- String
- NULL
- Commentaire

## 1.2. Mots-clé et tokens
<table>
<tr><th>Mots-clé et tokens </th><th>Symboles spéciaux et tokens</th></tr>
<tr><td>

 | **MOTS CLES**	 | **TOKENS** | 
 | --- | --- |	
 | const | CONST_TOKEN | 
 | num | TYNUM_TOKEN | 
 | string | TYSTRING_TOKEN | 
 | NULL | NULL_TOKEN | 
 | main | MAIN_TOKEN | 
 | begin | BEGING_TOKEN | 
 | return | RET_TOKEN_TOKEN | 
 | if | IF_TOKEN_TOKEN | 
 | else | ELSE_TOKEN | 
 | elif | ELIF_TOKEN | 
 | while | WHILE_TOKEN | 
 | do | DO_TOKEN | 
 | for | FOR_TOKEN | 
 | in | IN_TOKEN | 
 | desc | DESC_TOKEN | 
 | asc | ASC_TOKEN | 
 | scan | SCAN_TOKEN | 
 | print | PRINT_TOKEN | 
 | true | TRUE_TOKEN | 
 | false | FALSE_TOKEN | 

</td><td>

 | SYMBOLES SPECIAUX | 	TOKENS| 
 | --- | --- |	
 | ;	 | PV_TOKEN | 
 | .	 | PT_TOKEN | 
 | :	 | DPT_TOKEN | 
 | +	 | PLUS_TOKEN | 
 | -	 | MOINS_TOKEN | 
 | *	 | MULT_TOKEN | 
 | /	 | DIV_TOKEN | 
 | %	 | MOD_TOKEN | 
 | ,	 | VIR_TOKEN | 
 | =	 | AFF_TOKEN | 
 | ==	 | EG_TOKEN | 
 | <	 | INF_TOKEN | 
 | <=	 | INFEG_TOKEN | 
 | >	 | SUP_TOKEN | 
 | >=	 | SUPEG_TOKEN | 
 | (	 | PO_TOKEN | 
 | )	 | PF_TOKEN | 
 | !=	 | DIFF_TOKEN | 
 | {	 | AO_TOKEN | 
 | }	 | AF_TOKEN | 
 | /*	 | CO_TOKEN | 
 | */	 | CF_TOKEN | 
 | " | 	QUOTE_TOKEN | 
 | EOF | 	EOF_TOKEN | 


</td></tr> </table>

### 1.1.1. Les terminaux
a~z	A~Z  =	+	-	*	/	%	{}	<>	()	,	;	:

### 1.1.2. Les non-terminaux
#### Fonstion main
Il s’agit de la fonction principale. Tout traitement ou commentaire doit se faire à l’intérieur du main.
On précise le type de retour numerique (num), un string ou rien (null).
La fonction main:
```
Main ( [type arg [, type arg}] ) : [ num| string | NULL] {
DECLARATIONS() ;
INSTS() ;
}
```
#### type
```
num | string
```
  
#### DECLARATIONS() 
```

	CONSTS() ;
	NUMERIC() ;
	STRINGS() ;

```
#### CONSTS()
```
const type ID= VAL [, type ID=VAL] ; | eps
```
#### NUMERIC()
```
num ID [, ID ] ; | eps
```
#### STRINGS()
```
string ID [, ID ] ; |eps
```
#### INSTS()
```
begin 
INST() { ; INST()}
return [ ID | NUM | NULL | eps ];```
```
#### INST()
```
INSTS() | AFFEC |IF |WHILE |DO_WHILE |FOR | SCAN |PRINT |eps```
```
#### AFFEC 
```
ID = EXPR() | CONCAT() ;
```
#### CONCAT 
```
WORDS() + WORDS() ;
```
#### WORDS 
```
ID | STRING 
```
#### IF 
```
If ( COND() ) { INST() ; }
[ else { INST () ; } | ELIF() ]
```
#### ELIF()
```
elif ( COND() ) { INST() }
[ else { INST();} |ELIF() ]
```
#### WHILE
```
while( COND){ INST() } ;
```
#### DO_WHILE
```
do{ INST ()} while(COND() ) ;
```
#### FOR
```
for ID in EXPR : EXPR [desc | asc]  { INST (); }
```
#### SCAN
```
scan( id [ , id]) ;
```
#### PRINT 
```
print(EXPR|CONCAT [,EXPR|CONCAT])
```
#### COND
```
EXPR RELOP EXPR | true | false
```
#### RELOP 
```
== | != | < |<= | > | >=
```
#### EXPR 
```
TERM [ ADDOP TERM]
```
#### ADOPP 
```
+ | -
```
#### TERM 
```
FACT [ MULOP FACT]
```
#### MULOP 
```
* | / | %
```
#### FACT 
```
ID | NUM | (EXPR)```
```
#### ID
```
Letter [letter|number ]
```
#### NUM 
```
[ - ] Number [number ]
```

#### NUMBER
```
0|…|9
```

#### Letter
```
A|..|Z|a|..|z
```

## 1.3. Règles de sémantiques

1.	Toutes les déclarations dans CONSTS, NUMS and STRINGS
2.	Les arguments de la fonctions main sont considéré comme déjà déclaré sans valeur initiale. Ils sont soit de type num, soit de type string.
3.	Une constante doit être soit de type num ou string. 
4.	Il est possible de concatener deux strings. (la taille maximale des strings est fixé est 100 pour ce petit compilateur)
5.	Une constante ne peut pas changer de valeur.
6.	PAS DE DOUBLE DECLARATIONS 
7.	Apres BEGIN, tous les symboles doivent être déjà déclarés 
8.	Le traitement doit se faire à l’intérieur de la fonction main.
9.	Il est nécessaire de préciser le type du retour de la fonction main ; num, string ou NULL. Si la fonction ne retourne rien, utiliser NULL. Il faut s'assurer que le type valeur retournée corrspond à ce qu'a été précisé au préalable.
10.	Les commentaires ne doivent pas être interprétés.
11.	Un commentaire peut être écrit n’importe où.
12.	On peut pas faire des opérations entre un string et un entier.
13.	Si la fonction ne retourne rien, on peut diectement utiliser **return;**
14.	Pour les conditions, **true** et **false** sont équivalent à **1** et **0** resp.

# 2. Génération du code
Ci dessous les instrcutions pour la génération du p-code:
*ADD, SUB, MUL, DIV, MOD, CCT,
    EQL, NEQ, GTR, LSS, GEQ, LEQ,
    PRN,
    INN,
    INT,
    LDI,
    LDA,
    LDV,
    STO,
    BRN,
    BZE,
    HLT*
