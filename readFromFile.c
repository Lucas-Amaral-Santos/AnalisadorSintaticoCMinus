Token* readTokensFromFile(){
    FILE *arq;
	arq = fopen("tokens.txt", "rt");
    int n;
    fscanf(arq, "%d", &n);
    
    Token* tokens = (Token*)malloc(n * sizeof(Token));
    int i = 0;
    while (!feof(arq)){
        int tipo;
        char valor[50];
        Token token;
        fscanf(arq, "%d %s", &tipo, valor);
        printf("%d %s\n",tipo, valor);
        token.tipo = tipo;
        strcpy( token.valor, "main");
        tokens[i] = token;
        i++;
    }
    fclose(arq);
    return tokens;
}
