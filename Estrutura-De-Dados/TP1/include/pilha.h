#ifndef PILHA_H
#define PILHA_H

#include<string>

// class type{
//     public:
//     type();
//     string numToString(int num);
//     int stringToInt(string str);

//     private:
//     double num;
//     string str;

//     friend class Pilha;
// };

const int MAXTAM = 1000;

class Pilha {
    public:
        Pilha();
        std::string getTopo();
        //int getTamanho();
        void Empilha(std::string item);
        std::string Desempilha();
        //std::string getItem(int pos);
        void Limpa();

    private:
        int topo;
        std::string pilha[MAXTAM];
        int tamanho;
};
class PilhaChar{
    public:
        PilhaChar();
        char getTopoC();
        int getTamanho();
        void EmpilhaC(char item);
        char DesempilhaC();
        //std::string getItem(int pos);
        void LimpaC();
        

    private:
        int topo;
        char pilha[MAXTAM];
        int tamanho;
};
class PilhaDouble{
    public:
        PilhaDouble();
        double getTopoD();
        void EmpilhaD(double item);
        double DesempilhaD();
        //std::string getItem(int pos);
        void LimpaD();
        

    private:
        int topo;
        double pilha[MAXTAM];
        int tamanho;
};

#endif
