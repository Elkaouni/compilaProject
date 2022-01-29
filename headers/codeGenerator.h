typedef struct
{
    int inst;
    int val;
} pcode;

typedef enum{
    ADD, SUB, MUL, DIV, MOD, CCT,
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
    HLT
} _codeJeu;
char *code_jeu[]={"ADD", "SUB", "MUL", "DIV","MOD", "CCT", "EQL",
                "NEQ", "GTR", "LSS", "GEQ", "LEQ",
                "PRN", "INN", "INT", "LDI", "LDA",
                "LDV", "STO",  "BRN", "BZE", "HLT"
                    };


pcode generated_code[100];
int PC=0;
int offset=0;

void generer1(int inst)
{
    if(PC == 100)
        exit(EXIT_FAILURE);
    generated_code[PC].inst = inst;
    PC++;
}

void generer2(int inst, int val)
{
    if(PC == 100)
        exit(EXIT_FAILURE);
    generated_code[PC].inst= inst;
    generated_code[PC].val = val;
    PC = PC+1;

}

void genererBZE(int addr_cond, int addr_inst)
{
    if(generated_code[addr_cond].inst == BZE)
    {
        generated_code[addr_cond].val = addr_inst;
    }
    else
    {
        printf("\n ###ERR BZE: ERROR while generating code for cond. ###\n");
        exit(EXIT_FAILURE);
    }
}

void print_code()
{
    printf("\n");
    printf("        ############################\n");
    printf("        #      Generated Code      #\n");
    printf("        ############################\n\n");
    for(int i=0; i<PC; i++)
    {
        char *inst= code_jeu[generated_code[i].inst];
        printf("%s\t", inst);

        if(strcmp(inst, "INT")==0 || strcmp(inst, "LDI")==0
           || strcmp(inst, "LDA")==0 || strcmp(inst, "BRN")==0
           || strcmp(inst, "BZE")==0)
        {
             printf("%d", generated_code[i].val);
        }
    }
    printf("\n");
    printf("        ##################\n");
    printf("        #      END       #\n");
    printf("        ##################\n\n");

}

void SaveInstToFile(FILE *file_sortie,int INST, int val)
{
     switch(INST)
     {
         case LDA: fprintf(file_sortie, "%s \t %d \n", "LDA", val); break;
         case LDI: fprintf(file_sortie, "%s \t %d \n", "LDI", val); break;
         case INT: fprintf(file_sortie, "%s \t %d \n", "INT", val); break;
         case BZE: fprintf(file_sortie, "%s \t %d \n", "BZE", val); break;
         case BRN: fprintf(file_sortie, "%s \t %d \n", "BRN", val); break;
         case LDV: fprintf(file_sortie, "%s \n", "LDV"); break;
         case CCT: fprintf(file_sortie, "%s \n", "CCT"); break;
         case ADD: fprintf(file_sortie, "%s \n", "ADD"); break;
         case SUB: fprintf(file_sortie, "%s \n", "SUB"); break;
         case MUL: fprintf(file_sortie, "%s \n", "MUL"); break;
         case DIV: fprintf(file_sortie, "%s \n", "DIV"); break;
         case MOD: fprintf(file_sortie, "%s \n", "MOD"); break;
         case LEQ: fprintf(file_sortie, "%s \n", "LEQ"); break;
         case GEQ: fprintf(file_sortie, "%s \n", "GEQ"); break;
         case NEQ: fprintf(file_sortie, "%s \n", "NEQ"); break;
         case LSS: fprintf(file_sortie, "%s \n", "LSS"); break;
         case GTR: fprintf(file_sortie, "%s \n", "GTR"); break;
         case HLT: fprintf(file_sortie, "%s \n", "HLT"); break;
         case STO: fprintf(file_sortie, "%s \n", "STO"); break;
         case INN: fprintf(file_sortie, "%s \n", "INN"); break;
         case PRN: fprintf(file_sortie, "%s \n", "PRN"); break;
         default:
             printf("\n### Interpretor: Error found in the generated code. ###\n");
             exit(EXIT_FAILURE);
     }
 }

/* change path according to whre you want to save*/
void SavePCodeToFile(FILE *file_sortie) {
    int i;
    char*path=".\\test_result.rh";
    file_sortie=fopen(path, "w+" );
    if(file_sortie == NULL){
        printf("File not found.\n");
        exit(0);
    }

    for (i=0; i<PC; i++) {
            SaveInstToFile(file_sortie, generated_code[i].inst, generated_code[i].val);
    }
    fclose(file_sortie);
}


