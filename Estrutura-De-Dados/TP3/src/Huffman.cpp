#include "../include/Huffman.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define TAM 256

void Huffman::inicializaTabela(unsigned int tab[]){
    for(int i=0;i<TAM;i++){
        tab[i]=0;
    }
}

void Huffman::preencheTabela(unsigned char text[], unsigned int tab[]){
    int i=0;
    while(text[i] != '\0'){
        tab[text[i]]++;
        i++;
    }
}

void Huffman::imprimeTabela(unsigned int tab[]){
    cout << "TABELA DE FREQUÊNCIA: " << endl;
    for(int i=0;i<TAM;i++){
        if(tab[i]>0){
            printf("\t%d = %d = %c\n", i, tab[i], i);
            // char c = (char)i;
            // cout << "\t" << i << " = " << tab[i] << " = " << c << endl;
        }
    }
}

void Huffman::criarLista(Lista *lista){
    lista->inicio = nullptr;
    lista->tam = 0;
}

void Huffman::inserirOrdenado(Lista *lista, No *no){

    No *aux;
    //lista está vazia?
    if(lista->inicio == nullptr){
        lista->inicio = no;
        lista->tam++;
    }
    //elemento a inserir com maior frequencia que o inicio
    else if(no->frequencia < lista->inicio->frequencia){
        no->prox = lista->inicio;
        lista->inicio = no;
        lista->tam++;
    }
    //inserção no meio/final
    else{
        aux = lista->inicio;
        while(aux->prox != nullptr && aux->prox->frequencia <= no->frequencia){
            aux = aux->prox;
        }
        no->prox = aux->prox;
        aux->prox = no;
        lista->tam++;
    }
}

void Huffman::preencherLista(unsigned int tab[], Lista *lista){
    No *novo;
    for(int i=0;i<TAM;i++){
        //pegando apenas os elementos que possuem frequência diferente de 0 na tabela
        if(tab[i]>0){
            novo = new No;
            //alocação ocorreu corretamente?
            if(novo){
                novo->caracter = (char)i;
                novo->frequencia = tab[i];
                novo->dir = nullptr;
                novo->esq = nullptr;
                novo->prox = nullptr;

                inserirOrdenado(lista, novo);
            }
            else{
                cout << "Ocorreu um erro de alocação no preenchimento da Lista." << endl;
                break;
            }
        }
    }
}

void Huffman::imprimeLista(Lista *lista){
    No *aux = lista->inicio;

    cout << "\n\tLista Ordenada: Tamanho: " << lista->tam << endl;
    while(aux){
        cout << "\tCaracter: " << aux->caracter << " Frequência: " << aux->frequencia << endl;
        aux = aux->prox;
    }
}

//3ª parte -> montagem da árvore de Huffman

No* Huffman::removeNoInicio(Lista *lista){
    No *aux = nullptr;

    //verifica se a lista está vazia
    if(lista->inicio != nullptr){
        aux = lista->inicio;
        lista->inicio = aux->prox;
        aux->prox = nullptr;
        lista->tam--;
    }
    else{
        cout << "Lista está vazia." << endl;
    }

    return aux;
}

No* Huffman::montaArvore(Lista *lista){

    No *primeiro, *segundo, *novo;

    //fazer o processo até sobrar 1 na lista, que será a raiz da árvore
    while(lista->tam > 1){
        primeiro = removeNoInicio(lista);
        segundo = removeNoInicio(lista);
        novo = new No;

        //verifico se alocou corretamente
        if(novo){
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->prox = nullptr;

            inserirOrdenado(lista, novo);
        }
        else{
            cout << "Ocorreu um erro de alocação na montagem da árvore." << endl;
            break;
        }
    }

    return lista->inicio;
}

void Huffman::imprimeArvore(No *raiz, int tam){
    //verifico se é um nó folha para imprimir suas informações
    if(raiz->esq == nullptr && raiz->dir ==nullptr){
        cout << "\tFolha: " << raiz->caracter << "\tAltura: " << tam << endl;
    }
    else{
        imprimeArvore(raiz->esq, tam+1);
        imprimeArvore(raiz->dir, tam+1);
    }
}

//4ª parte - > montagem do dicionário

int Huffman::alturaArvore(No *raiz){
    int esq, dir;
    if(raiz==nullptr){
        return -1;
    }
    else{
        esq = alturaArvore(raiz->esq) + 1;
        dir = alturaArvore(raiz->dir) + 1;

        if(esq > dir){
            return esq;
        }
        else{
            return dir;
        }
    }
}

char** Huffman::alocaDicionario(int colunas) {
    int linhas = TAM;
    // Alocar dinamicamente o array de ponteiros para as linhas
    char** matriz = (char**)malloc(linhas * sizeof(char*));

    if (matriz == NULL) {
        // Se a alocação falhar, retorne NULL ou faça algum tratamento de erro apropriado
        cout << "erro de alocação1" << endl;
        return NULL;
    }

    // Alocar dinamicamente cada linha (vetor de caracteres) da matriz e inicializá-las com zero
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char*)calloc(colunas, sizeof(char));

        // Verificar se a alocação falhou para alguma linha
        if (matriz[i] == NULL) {
            cout << "erro de alocação2" << endl;
            // Liberar a memória alocada até agora para evitar vazamentos de memória
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}


void Huffman::deleteDicionario(char** dicionario){
    for (int i = 0; i < TAM; ++i)
        delete [] dicionario[i];

    delete [] dicionario;
}

void Huffman::geraDicionario(char **dicionario, No *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];
    
    if(raiz->esq == nullptr && raiz->dir == nullptr){
        strcpy(dicionario[raiz->caracter], caminho);
    }
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);
    
        strcat(esquerda, "0");
        strcat(direita, "1");

        geraDicionario(dicionario, raiz->esq, esquerda, colunas);
        geraDicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void Huffman::imprimeDicionario(char **dicionario){
    
    cout << "\tDICIONÁRIO:" << endl;
    for(int i=0;i<TAM;i++){
        cout << "\t" << i << ": " << dicionario[i] << endl;
    }
}

void Huffman::salvaDicionario(char** dicionario){
    fstream arq;
    arq.open("dicionario.txt", ios::out);
    if (!arq) {
		cout << "Arquivo de dicionário não criado!" << endl;
	}
	else {
		cout << "Arquivo de dicionário criado com sucesso!" << endl;
        for(int i=0;i<TAM;i++){
            arq << i << " " << dicionario[i] << endl;
        }
		arq.close(); 
	}
}

int Huffman::calculaTamanhoString(char **dicionario, unsigned char *texto){
    int i=0, tam=0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }

    return tam + 1;
}

char* Huffman::codificar(char **dicionario, unsigned char *texto){
    int i=0, tam = calculaTamanhoString(dicionario, texto);
    //char *codigo = (char)malloc(tam, sizeof(char));
    //char *codigo = (char*)malloc(sizeof(char) * tam);
    char *codigo = (char*)calloc(tam, sizeof(char));
    //inicializar com 0

    while(texto[i] != '\0'){
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }

    return codigo;
}
void Huffman::limparArvore(No* no) {
    if (no == nullptr) {
        return;
    }
    
    // Limpar os nós filhos (recursivamente)
    limparArvore(no->esq);
    limparArvore(no->dir);
    limparArvore(no->prox);
    
    // Liberar memória do nó atual
    delete no;
}

char* Huffman::decodificar(char texto[], No *raiz){
    int i=0;
    No *aux = raiz;
    char temp[2];
    int tam = strlen(texto);
    cout<< "LENGTH: "<< tam <<endl;
    char *decodificado = (char*)calloc(tam, sizeof(char));

    while(texto[i] != '\0'){
        if(texto[i]=='0'){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }

        if(aux->esq == nullptr && aux->dir == nullptr){
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }
        i++;
    }
    return decodificado;
}