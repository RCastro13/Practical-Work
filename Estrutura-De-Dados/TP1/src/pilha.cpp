#include "pilha.h"
#include <iostream>
#include <string>
#include <sstream>

Pilha::Pilha(){
    topo = -1;
}

std::string Pilha::getTopo(){
    return pilha[topo];
}

void Pilha::Empilha(std::string item){

    if(tamanho == 1000){
        throw "A pilha está cheia!";
    }
    topo++;
    std::string aux;
    aux = item;
    pilha[topo] = aux;
    tamanho++;
}       

std::string Pilha::Desempilha(){
    std::string aux;
    if(tamanho == 0)
        throw "A pilha está vazia!";

    aux = pilha[topo];
    topo--;
    tamanho--;
    return aux;
}

void Pilha::Limpa(){
    topo = -1;
    tamanho = 0;
}

PilhaChar::PilhaChar(){
    topo = -1;
    tamanho = 0;
}

char PilhaChar::getTopoC(){
    return pilha[topo];
}

int PilhaChar::getTamanho(){
    return tamanho;
}

void PilhaChar::EmpilhaC(char item){
    if(tamanho == 1000){
        throw "A pilha está cheia!";
    }
    topo++;
    pilha[topo] = item;
    tamanho++;
    
}       

char PilhaChar::DesempilhaC(){
    char aux;
    if(tamanho == 0)
        throw "A pilha está vazia!";

    aux = pilha[topo];
    topo--;
    tamanho--;
    return aux;
}

void PilhaChar::LimpaC(){
    topo = -1;
    tamanho = 0;
}

PilhaDouble::PilhaDouble(){
    topo = -1;
    tamanho = 0;
}

double PilhaDouble::getTopoD(){
    return pilha[topo];
}

void PilhaDouble::EmpilhaD(double item){
    if(tamanho == 1000){
        throw "A pilha está cheia!";
    }
    topo++;
    pilha[topo] = item;
    tamanho++;
    
}       

double PilhaDouble::DesempilhaD(){
    double aux;
    if(tamanho == 0)
        throw "A pilha está vazia!";

    aux = pilha[topo];
    topo--;
    tamanho--;
    return aux;
}

void PilhaDouble::LimpaD(){
    topo = -1;
    tamanho = 0;
}