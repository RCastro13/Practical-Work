#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Huffman.h"

#define TAM 256

using namespace std;

void writeTree(No* x, ofstream& out) {
    if (x->esq == nullptr && x->dir == nullptr) {
        out << '1' << (char)x->caracter; // '1' antes de uma folha
    }
    else {
        out << '0'; // '0' antes de um nó interno
        writeTree(x->esq, out);
        writeTree(x->dir, out);
    }
}

void writeHeader(No* raiz, ofstream& out) {
    writeTree(raiz, out); // Chama a função para escrever o caminhamento da árvore
    out << '#';
}

No* reconstructTree(ifstream& in) {
    char bit;
    in.get(bit);
    No* novo = new No;
    novo->frequencia = 0;
    novo->dir = nullptr;
    novo->esq = nullptr;
    novo->prox = nullptr;

    if (bit == '1') {
        char caracter;
        in.get(caracter);
        novo->caracter = caracter;
        
        return novo;
    } else if (bit == '0') {
        novo->caracter = '+';
        novo->esq = reconstructTree(in);
        novo->dir = reconstructTree(in);
        return novo;
    }else if (bit == '#') {
        return nullptr;
    }

    delete novo;
    return nullptr; // Caso inválido
}

void compactar(No* raiz, char str[], char* saida) {
    ofstream arquivo(saida, ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir/criar arquivo em compactar" << endl;
        return;
    }

    writeHeader(raiz, arquivo); // Escreve o cabeçalho com o caminhamento da árvore

    unsigned char byte = 0;
    int bitCount = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char bit = (str[i] == '1') ? 1 : 0;

        byte = byte << 1; // Desloca um bit para a esquerda
        byte = byte | bit; // Faz o OR bit a bit

        bitCount++;

        if (bitCount == 8) {
            arquivo.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
            byte = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        byte = byte << (8 - bitCount); // Desloca os bits restantes para a esquerda
        arquivo.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
    }

    cout << "Arquivo compactado " << saida << " foi criado com sucesso." << endl;
    arquivo.close();
}

unsigned int ehBitUm(unsigned char byte, int i){
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void descompactar(No* raiz, string entrada, string saida) {
    ifstream entradaFile(entrada, ios::binary);
    ofstream saidaFile(saida);

    No* aux = raiz;
    unsigned char byte;
    int i, cont=0;

    if (entradaFile && saidaFile && aux) {
        bool startDescompactacao = false;
        while (entradaFile.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
            if (byte == '#' && cont == 0) {
                startDescompactacao = true;
                cont = 1;
                continue;
            }

            if (startDescompactacao) {
                for (i = 7; i >= 0; i--) {
                    if (ehBitUm(byte, i)) {
                        aux = aux->dir;
                    } else {
                        aux = aux->esq;
                    }
                    if (aux->esq == nullptr && aux->dir == nullptr) {
                        saidaFile << aux->caracter;
                        aux = raiz;
                    }
                }
            }
        }
        cout << "Arquivo descompactado: " << saida << " foi descompactado com sucesso" << endl;
    } else {
        cout << "Erro ao abrir arquivo(s) em descompactar." << endl;
    }

    entradaFile.close();
    saidaFile.close();
}

int main(int argc, char *argv[]){

    //verificação se os parâmetros foram passados corretamente
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " entrada saida c\n";
        return 1;
    }

    //strings passadas por parâmetro -> arquivos e flag de instrução
    string nomeEntrada = argv[1];
    char* nomeSaida = argv[2];
    string c = argv[3]; 

    Huffman conjunto;
    
    if(c == "c" || c == "C"){
        cout << "O programa irá compactar o arquivo " << nomeEntrada << " com a saída no arquivo " << nomeSaida << endl;
        string textAux="", text="";
        ifstream arq(nomeEntrada);
        if (!arq) {
            cout << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }
        string linha;
        string texto;
        while (getline(arq, linha)) {
            texto += linha;

            // Verifica se não é a última linha antes de adicionar a quebra de linha
            if (!arq.eof()) {
                texto += '\n';
            }
        }
        arq.close();

        //passando o texto de entrada para unsigned char
        unsigned char* buffer = reinterpret_cast<unsigned char*>(const_cast<char*>(texto.c_str()));
        unsigned int tabela_frequencia[TAM];
        Lista lista;
        No *arvore;
        int colunas;
        char *codificado;
        char **dicionario;
        
        //1ª parte -> desenvolvendo a tabela de frequência -> quantidade de cada elemento presente na entrada
        conjunto.inicializaTabela(tabela_frequencia);
        conjunto.preencheTabela(buffer, tabela_frequencia);
        //conjunto.imprimeTabela(tabela_frequencia); //apenas para teste e visualização

        //2ª parte -> desenvolvendo a lista ordenada -> coloca-se os elementos da tabela de frequência ordenados em uma lista
        conjunto.criarLista(&lista);
        conjunto.preencherLista(tabela_frequencia, &lista);
        //conjunto.imprimeLista(&lista); //apenas para teste e visualização

        //3ª parte -> montagem da árvore de Huffman
        arvore = conjunto.montaArvore(&lista);
        //conjunto.imprimeArvore(arvore, 0); //apenas para teste e visualização

        //4ª parte -> montagem do dicionário com os caminhamentos na árvore
        colunas = conjunto.alturaArvore(arvore) + 1;
        char caminho[colunas + 1];
        caminho[0] = '\0';
        dicionario = conjunto.alocaDicionario(colunas);
        conjunto.geraDicionario(dicionario, arvore, caminho, colunas);
        //conjunto.imprimeDicionario(dicionario); //apenas para teste e visualização
        //conjunto.salvaDicionario(dicionario); //apenas para teste e visualização

        //5ª parte -> montagem da nova string codificada
        codificado = conjunto.codificar(dicionario, buffer);
        //salvaCompactado(codificado); //apenas para teste e visualização

        //6ª parte -> compactação da string codificada
        compactar(arvore, codificado, nomeSaida);

        conjunto.limparArvore(arvore);
        conjunto.deleteDicionario(dicionario);
    }
    else if(c == "d" || c == "D"){
        cout << "O programa irá descompactar o arquivo " << nomeEntrada << " com a saída no arquivo " << nomeSaida << endl;
        
        //7ª parte -> descompactação
        ifstream arquivo(nomeEntrada, ios::binary);
        No* newTree = reconstructTree(arquivo);
        //conjunto.imprimeArvore(newTree, 0); //apenas para teste e visualização
        descompactar(newTree, nomeEntrada, nomeSaida);

        conjunto.limparArvore(newTree);
    }
    else{
        cout << "Flag incorreta." << endl;
        return 1;
    }

    return 0;
}