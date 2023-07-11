#include <stdlib.h>
#include <iostream>

using namespace std;

template <typename Tipo>
class Pilha {
    public:
        Pilha();
        bool isEmpty();
        void Empilha(Tipo item);
        Tipo Desempilha();
        Tipo top() ;
        int size();

    private:
        int topo;
        Tipo elementos_[10000];
        double length;
};