#include <iostream>
#include <time.h>
#include <fstream>
#include <dirent.h>
#include "./fecho.cpp"
#include <string>
#define MAX_TAM 100000

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Erro: Arquivo digitado não foi encontrado" << std::endl;
        return 1;
    }

    ifstream entrada(argv[1]);

    Point Points[MAX_TAM] = {};
    string line, entry1, entry2;
    Fecho solucao;

    int length = 0;

    //pegando os pontos escritos no arquivo e armazenando em um vetor de pontos(x,y)
    while(getline(entrada, line)){
        istringstream iss(line);
        iss>>entry1;
        iss>>entry2;
        int x,y;
        x=stoi(entry1);
        y=stoi(entry2);

        Point ponto;
        ponto.x = x;
        ponto.y = y;
        Points[length] = ponto;
        length++;
    };

    //vetores de ponto auxiliares, 1 para cada solução incluindo a resposta inicial do programa
    Point pontos0[length] = {}, pontos1[length] = {}, pontos2[length] = {}, pontos3[length] = {}, pontos4[length] = {};
    for(int i=0;i<length;i++) {
        pontos0[i] = Points[i];
        pontos1[i] = Points[i];
        pontos2[i] = Points[i];
        pontos3[i] = Points[i];
        pontos4[i] = Points[i];
    }

    //imprimindo a resposta do fecho convexo -> pode-se descomentar as linhas e deixar a solução que você quer ver funcionando.
    //OBS.: deixar apenas uma linha com a atribuição à resp para não sobrescrever a resposta

    Pilha<Point> resp = solucao.jarvisMarch(pontos0, length); //-> resposta vinda do jarvis
    //Pilha<Point> resp = solucao.grahamScan(pontos1, length, 1); //-> resposta vinda do Graham+MergeSort
    //Pilha<Point> resp = solucao.grahamScan(pontos2, length, 2); //-> resposta vinda do Graham+InsertionSort
    //Pilha<Point> resp = solucao.grahamScan(pontos3, length, 3); //-> resposta vinda do Graham+Linear(bucketSort)
    cout << "FECHO CONVEXO CALCULADO: " << endl;
    while(!resp.isEmpty()) {
        Point point = resp.Desempilha();
        cout << point.x << " " << point.y << endl;
    }

    //clock_t start, end;
    struct timespec start, end;
    double elapsed_time;

    //resolvendo por Graham+MergeSort e contando o tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    solucao.grahamScan(pontos1, length, 1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("\nGRAHAM+MERGESORT: %.7fs\n", elapsed_time);

    //resolvendo por Graham+InsertionSort e contando o tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    solucao.grahamScan(pontos2, length, 2);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("GRAHAM+INSERTIONSORT: %.7fs\n", elapsed_time);

    //resolvendo por Graham+OrdenaçãoLinear(bucketSort) e contando o tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    solucao.grahamScan(pontos3, length, 3);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("GRAHAM+LINEAR: %.7fs\n", elapsed_time);

    //resolvendo por Jarvis e contando o tempo
    clock_gettime(CLOCK_MONOTONIC, &start);
    solucao.jarvisMarch(pontos4, length);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("JARVIS: %.7fs\n", elapsed_time);
        
    entrada.close();

    return 0;
}