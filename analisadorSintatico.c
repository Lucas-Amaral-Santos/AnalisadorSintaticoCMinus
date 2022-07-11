#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum tokenType {
    EMPTY = 1,
    INT,
    VOID,
    ID,
    OPENPAREN,
    CLOSEPAREN,
    OPENCHAVES,
    CLOSECHAVES,
    OPENCOLCHETE,
    CLOSECOLCHETE,
    VIRGULA,
    PONTOVIRGULA,
    NUM
};
typedef struct
{
	char valor[50];
	enum tokenType tipo;
} Token;

static Token currToken;
int tokenPos = 0;

int program(Token * tokens);
int declarationList(Token * tokens);
int declarationListLinha(Token * tokens);
int declaration(Token * tokens);
int varDeclaration(Token * tokens);
int numVarDec(Token * tokens);
int typeSpec(Token * tokens);
int funDec(Token * tokens);
int paramList(Token * tokens);
int paramListLinha(Token * tokens);
int param(Token * tokens);
int params(Token * tokens);
int paramLinha(Token * tokens);
int compoundStmt(Token * tokens);
int localDec(Token * tokens);
int localDecLinha(Token * tokens);
int stmtList(Token * tokens);
int stmtListLinha(Token * tokens);
int stmt(Token * tokens);
int expStmt(Token * tokens);
int selecStmt(Token * tokens);
int elseStmt(Token * tokens);
int iterationStmt(Token * tokens);
int returnStmt(Token * tokens);
int returnExp(Token * tokens);
int expression(Token * tokens);
int var(Token * tokens);
int varExp(Token * tokens);
int simpleExp(Token * tokens);
int relop(Token * tokens);
int addExp(Token * tokens);
int addExpLinha(Token * tokens);
int addop(Token * tokens);
int term(Token * tokens);
int termLinha(Token * tokens);
int mulOp(Token * tokens);
int factor(Token * tokens);
int call(Token * tokens);
int args(Token * tokens);
int argList(Token * tokens);
int argListLinha(Token * tokens);

void consomeToken(Token* tokens){
    tokenPos++;
    currToken = tokens[tokenPos];
}
int program(Token * tokens){
    return declarationList(tokens);
}

int declarationList(Token* tokens){
    return declarationListLinha(tokens);
}

int declarationListLinha(Token* tokens){
    int i = declaration(tokens);
    while(currToken.tipo != EMPTY && i){

        i = declaration(tokens) && i;
        printf("TOKEN: %s", currToken.valor);
        consomeToken(tokens);
    }
    return i;
}

// int declaration(Token* tokens){
//     if(typeSpec(tokens)){
//         consomeToken(tokens);
//         if(currToken.tipo == ID){
//             consomeToken(tokens);
//             if(currToken.tipo == OPENPAREN){ // is functino
//                 // return 1; //funDec(tokens);
//                 if(params(tokens)){
//                     consomeToken(tokens);
//                     if(currToken.tipo == CLOSEPAREN){
//                         // compound-stmt
//                         return 1;
//                     }        
//                 }
//             } else {
//                 return 1; //numVarDec(tokens);
//             }
//         }
//     }
//     return 0;
// }

int declaration(Token * tokens){
    if(varDeclaration){
        return 1;
    }
    if(funDec){
        return 1;
    }
}

int varDeclaration(Token * tokens){
    if(typeSpec(tokens)){
        consomeToken(tokens);
        if(currToken.tipo == ID){
            consomeToken(tokens);
            if(numVarDec){
                if(currToken.tipo == PONTOVIRGULA){
                    consomeToken(tokens);
                }
            }
        }
    }   
}


int numVarDec(Token * tokens){
    if(currToken.tipo == OPENCOLCHETE){
        consomeToken(tokens);
        if(currToken.tipo == NUM){
            consomeToken(tokens);
            if(currToken.tipo == CLOSECOLCHETE){
                consomeToken(tokens);
                return 1;
                
            }
        }
    }   
    if(currToken.tipo == EMPTY){
        consomeToken(tokens);
        return 1;
                
    }           

}

int typeSpec(Token* tokens){
    if(currToken.tipo == INT || currToken.tipo == VOID){
        return 1;
    }
    return 0;
}

int funDec(Token * tokens){
    if(currToken.tipo == OPENPAREN){
        consomeToken(tokens);
        int i = 1; //params(tokens);
        if(i) {
            consomeToken(tokens);
            if(currToken.tipo == CLOSEPAREN){
                return 1;
            }
        }
    }
    return 0;
}

int params(Token * tokens){
    if (paramList(tokens))
    {
        return 1;
    } 

    if (currToken.tipo == VOID){
        return 1;
    }
    
}


int paramList(Token * tokens){
    if (param(tokens)){
        consomeToken(tokens);
        if (paramListLinha(tokens))
        {
            return 1;
        }
    }
}

int paramListLinha(Token * tokens){
    if(param(tokens)){
        return 1;
    }

    if (currToken.tipo == VIRGULA){
        if(param(tokens)){
            consomeToken(tokens);
            if (paramListLinha(tokens)){
                return 1;
            }
        }
    }

    if(currToken.tipo == EMPTY){
        return 1;
    }

}

int param(Token * tokens){
    if (typeSpec(tokens)){
        if(currToken.tipo == ID){
            consomeToken(tokens);
            if (paramLinha){
                return 1;
            }
        }
    }
}

int paramLinha(Token * tokens){
    if(currToken.tipo == OPENCOLCHETE){
        consomeToken(tokens);
        if(currToken.tipo == CLOSECOLCHETE){
            consomeToken(tokens);
            return 1;
        }
    }

    if(currToken.tipo == EMPTY){
        consomeToken(tokens);
        return 1;
    }

}

int compoundStmt(Token * tokens){
    if(currToken.tipo == OPENCHAVES){
        consomeToken(tokens);
        if (localDec(tokens)){
            if(localDec(tokens)){
                if(stmtList){
                    if (currToken.tipo==CLOSECHAVES)
                    {
                        return 1;
                    }
                }
            }
        }
    }
}

int localDec(Token * tokens){
    if (localDecLinha)
    {
        return 1;
    }
}

int localDecLinha(Token * tokens){

    if(currToken.tipo == EMPTY){
        consomeToken(tokens);
        return 1
    }

    if (varDeclaration){
        if(localDecLinha){
            return 1;
        }
    }

}


int stmtList(Token * tokens){
    
    if (currToken.tipo == EMPTY)
    {
        return 1;
    }
    if (stmtListLinha)
    {
        return 1;
    }
}

int stmtListLinha(Token * tokens){
    if (currToken.tipo == EMPTY)
    {
        return 1;
    }

    if (stmt){
        if (stmtListLinha) {
            return 1;
        }
    }
}

int stmt(Token * tokens){
    
    if (expStmt)
    {
        return 1;
    }
    if (compoundStmt)
    {
        return 1;
    }
    if (selecStmt)
    {
        return 1;
    }
    if (iterationStmt)
    {
        return 1;
    }
    if (returnStmt)
    {
        return 1;
    }
}

int expStmt(Token * tokens){
    if (expression(tokens))
    {
        // PONTOVIRGULA
    }

    if(currToken.tipo == PONTOVIRGULA){
        consomeToken(tokens);
        return 1;
    }
}

int main(int argc, char *argv[ ]){

    printf("INIT\n\n");
    Token teste;
    strcpy( teste.valor, "int");
    teste.tipo = INT;
    Token empty;
    Token teste2;
    strcpy( teste2.valor, "main");
    teste2.tipo = ID;
    strcpy( empty.valor, "token");
    empty.tipo = EMPTY;

    Token* tokens = (Token*)malloc(10 * sizeof(Token));
    tokens[0] = teste;
    tokens[1] = teste2;
    tokens[2] = empty;
    currToken = tokens[0];
    printf("START TOKEN: %d %s\n", currToken.tipo, currToken.valor);
    printf("%d", program(tokens));

}


