typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *prox;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

class Huffman{
    public:
    //1ª parte ->
    void inicializaTabela(unsigned int tab[]);
    void preencheTabela(unsigned char text[], unsigned int tab[]);
    void imprimeTabela(unsigned int tab[]);

    //2ª parte ->
    void criarLista(Lista *lista);
    void inserirOrdenado(Lista *lista, No *no);
    void preencherLista(unsigned int tab[], Lista *lista);
    void imprimeLista(Lista *lista);

    //3ª parte ->
    No* removeNoInicio(Lista *lista);
    No* montaArvore(Lista *lista);
    void imprimeArvore(No *raiz, int tam);
    int alturaArvore(No *raiz);
    void limparArvore(No* no);
    
    //4ª parte -> 
    char** alocaDicionario(int colunas);
    void deleteDicionario(char** dicionario);
    void geraDicionario(char **dicionario, No *raiz, char *caminho, int colunas);
    void imprimeDicionario(char **dicionario);
    void salvaDicionario(char** dicionario);
    int calculaTamanhoString(char **dicionario, unsigned char *texto);
    char* codificar(char **dicionario, unsigned char *texto);
    char* decodificar(char texto[], No *raiz);

    No* arvore;
    Lista lista;
};