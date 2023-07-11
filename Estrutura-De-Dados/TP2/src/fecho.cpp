#include <algorithm>
#include <cassert>
#include "../include/fecho.h"
#include <sstream>
#include <cmath>

//Sumário:
//->funções genéricas usadas pelo programa e pelas funções de ordenação
//->TAD fecho
//
//---------------
//->Tad Pilha


//->funções genéricas

//retorna o ângulo entre 2 pontos
double angle(Point first, Point second){
    if(second.x - first.x == 0) {
        if(second.y - first.y > 0) {
            return M_PI/2;
        } else {
            return 3*M_PI/2;
        }
    }
    return atan2(second.y - first.y, second.x - first.x);
}

//retorna a distância entre pontos
int distSq(Point p1, Point p2){
    return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//retorna o ponto mais a esquerda
Point minX(Point points[], int length){
    assert((length >= 2) && "A quantidade de pontos não é suficiente");

    int i = 0;
    Point min = points[0];
    while(i < length){
        if(points[i].x < min.x) {
            min = points[i];
        }
        i++;
    }
    return min;
}

//retorna o ponto em baixo do topo da pilha - penúltimo
Point nextToTop(Pilha<Point> &stack){
    assert(!stack.isEmpty() && "A pilha possui poucos elementos suficientes");

    if(stack.size() == 1){
        cout << "A pilha possui apenas 1 elemento" << endl;
        return stack.top();
    }else{
        Point p = stack.top();
        stack.Desempilha();
        Point res = stack.top();
        stack.Empilha(p);
        return res;
    }
}

//retorna o ponto de menor Y e tem critério de desempate o menor X
int minXY(Point points[], int length){
    assert((length >= 2) && "A quantidade de pontos é muito pequena!");
    
    int min = 0;
    int ymin = points[0].y;
    for(int i=1;i<length;i++){
        int y = points[i].y;
        if ((y<ymin) || (ymin == y && points[i].x<points[min].x)){
            ymin = points[i].y;
            min = i;
        }
    }
    return min;
}

//método auxiliar para o funcionamento da ordenação do buckets
bool comparePoints(Point p1, Point p2, Point p0){
    double angle1 = angle(p0, p1);
    double angle2 = angle(p0, p2);
    if(angle1 < angle2){
        return true;
    }
    else if(angle1 > angle2){
        return false;
    }
    else{
        return distSq(p1, p0) < distSq(p2, p0);
    }
}

//-----------
//
//->TAD fecho
//
//

//verifica a orientação da reta formada pela junção dos 3 pontos
int Fecho::orientation(Point first, Point second, Point third){
    double d = (third.y - second.y) * (second.x - first.x) - (second.y - first.y) * (third.x - second.x);

    if(d > 0){return 1;} //girei anti-horário
    if(d < 0){return -1;} //girei horário
    return 0; //os pontos são colineares
}

//verifica qual ordenação será feita pelo scan de Graham
void Fecho::order(Point points[], int length, int tipoOrder, Point p0){
    assert((tipoOrder == 1 || tipoOrder == 2 || tipoOrder == 3) && "Tipo de ordenação inválido!");

    if(tipoOrder == 1){
        mergeSort(points, 0, length - 1, p0);
    }else if(tipoOrder == 2){
        insertionSort(points, length, p0);
    }else if(tipoOrder == 3){
        bucketSort(points, length, p0);
    }
}

//método auxiliar para o funcionamento do mergeSort
void Fecho::merge(Point points[], int const left, int const mid, int const right, Point p0){
    auto const firstVector = mid - left + 1;
    auto const secondVector = right - mid;

    //criação de arrays temporários e copia dos pontos para esses vetores
    auto *leftArray = new Point[firstVector], *rightArray = new Point[secondVector];
    for(auto i=0;i<firstVector;i++){
        leftArray[i] = points[left + i];
    }
    for(auto j=0;j<secondVector;j++){
        rightArray[j] = points[mid + 1 + j];
    }
    int firstIndex = 0;
    int secondIndex = 0;
    int indexNewVector = left;
    double angle1, angle2;

    //merge dos dos vetores temporários para o array original
    while(firstIndex < firstVector && secondIndex < secondVector){
        angle1 = angle(p0, leftArray[firstIndex]);
        angle2 = angle(p0, rightArray[secondIndex]);

        if(angle1 < angle2){
            points[indexNewVector].x = leftArray[firstIndex].x;
            points[indexNewVector].y = leftArray[firstIndex].y;
            firstIndex++;
        }else if(angle1 > angle2){
            points[indexNewVector].x = rightArray[secondIndex].x;
            points[indexNewVector].y = rightArray[secondIndex].y;
            secondIndex++;
        }else{
            double dist1 = distSq(p0, leftArray[firstIndex]);
            double dist2 = distSq(p0, rightArray[secondIndex]);
            if (dist1 < dist2) {  // Compare as distâncias usando '<' em vez de '<='
                points[indexNewVector].x = leftArray[firstIndex].x;
                points[indexNewVector].y = leftArray[firstIndex].y;
                firstIndex++;
            } else {
                points[indexNewVector].x = rightArray[secondIndex].x;
                points[indexNewVector].y = rightArray[secondIndex].y;
                secondIndex++;
            }
        }
        indexNewVector++;
    }

    //pega os elementos restantes do vetor da esquerda, se tiver
    while(firstIndex < firstVector){
        points[indexNewVector] = leftArray[firstIndex];
        firstIndex++;
        indexNewVector++;
    }

    //pega os elementos restantes do vetor da direita, se tiver
    while(secondIndex < secondVector){
        points[indexNewVector] = rightArray[secondIndex];
        secondIndex++;
        indexNewVector++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

//função que realiza o método do mergeSort
void Fecho::mergeSort(Point points[], int const init, int const fim, Point p0){
    if(fim <= init){
        return;
    }
    auto mid = init + (fim - init) / 2;
    mergeSort(points, init, mid, p0);
    mergeSort(points, mid + 1, fim, p0);
    merge(points, init, mid, fim, p0);
}

//função que realiza o método do insertionSort
void Fecho::insertionSort(Point points[], int length, Point p0){
    int i = 1;
    //iteração dos elementos do array
    while(i<length){
        int j = i;
        double angle1 = angle(p0, points[j-1]);
        double angle2 = angle(p0, points[j]);
        //angulo entre os pontos >
        if(angle1>angle2){
            while(j>0){
                angle1 = angle(p0, points[j-1]);
                angle2 = angle(p0, points[j]);
                if(angle1>angle2){
                    Point temp = points[j - 1];
                    points[j - 1] = points[j];
                    points[j] = temp;
                }
                j--;
            }
        //angulo entre os pontos =
        }else if(angle1 == angle2){
            double dist1 = distSq(p0, points[j-1]);
            double dist2 = distSq(p0, points[j]);
            if(dist1>dist2){
                while(j>0){
                    dist1 = distSq(p0, points[j-1]);
                    dist2 = distSq(p0, points[j]);
                    if(dist1>dist2){
                        Point temp = points[j - 1];
                        points[j - 1] = points[j];
                        points[j] = temp;
                    }
                    j--;
                }
            }
        }
        i++;
    }
}

//função que realiza o método do bucketSort
void Fecho::bucketSort(Point points[], int n, Point p0){
    int bucketNumber = 10; //10 será o máximo número de baldes
    
    //criação e cálculo dos tamanhos dos baldes + aloca memória
    Point* buckets[bucketNumber];
    for(int i=0;i<bucketNumber;i++){
        buckets[i] = nullptr;
    }
    int size[bucketNumber] = {0};
    for(int i=0;i<n;i++){
        int index = bucketNumber * angle(p0, points[i]) / (2 * M_PI);
        size[index]++;
    }
    for(int i=0;i<bucketNumber;i++){
        buckets[i] = new Point[size[i]];
    }
    
    //colocando os pontos nos baldes de acordo com suas angulações
    int counter[bucketNumber] = {0};
    for(int i=0;i<n;i++){
        int index = bucketNumber * angle(p0, points[i]) / (2 * M_PI);
        buckets[index][counter[index]] = points[i];
        counter[index]++;
    }
    
    //ordenação dos pontos dos baldes
    for(int i=0;i<bucketNumber;i++){
        sort(buckets[i], buckets[i] + size[i], [p0](Point p1, Point p2) { return comparePoints(p1, p2, p0); });
    }
    int index = 0;
    for(int i=0;i<bucketNumber;i++){
        for(int j=0;j<size[i];j++){
            points[index++] = buckets[i][j];
        }
        delete[] buckets[i];
    }
}

//resolução pela marcha de Jarvis
Pilha<Point> Fecho::jarvisMarch(Point points[], int length){
    Point hull = minX(points, length);
    Pilha<Point> resp; //pilha que será atribuído o conjunto resposta da marcha de Jarvis
    Point initialPoint = hull;

    //encontrando os pontos solução
    while(true){ 
        resp.Empilha(hull);
        Point nextPoint = points[0];
        for(int j = 0; j < length; j++){
            int o = orientation(hull, nextPoint, points[j]);
            if((nextPoint.x == hull.x && nextPoint.y == hull.y) || o == 1){
                nextPoint = points[j];
            }
        }
        hull = nextPoint;
        if ((hull.x == initialPoint.x) && (hull.y == initialPoint.y)){
            break;
        }
    }
    return resp;
}

//resolução pelo scan de Graham, a ordenação é escolhida pela função order()
Pilha<Point> Fecho::grahamScan(Point points[], int length, int tipoOrder){
    //pilha que será atribuído o conjunto resposta do scan de graham
    Pilha<Point> resultPoints;
    
    //pegando o ponto mais à esquerda e ajustando a primeira posição para ter esse ponto
    int minPointIndex = minXY(points, length);
    Point temp = points[0];
    points[0] = points[minPointIndex];
    points[minPointIndex] = temp;
    Point p0 = points[0];

    //passando para o método que irá ordenar os pontos
    order(&points[1], length - 1, tipoOrder, p0);

    //remoção dos pontos colineares
    int m = 1;
    for(int i=1;i<length;i++){
        while(i < length-1 && orientation(p0, points[i], points[i+1]) == 0){
            i++;
        }
        points[m] = points[i];
        m++;
    }
    if(m < 3){
        return resultPoints;
    }

    //criação da pilha auxiliar e empilhando 3 pontos iniciais
    resultPoints.Empilha(points[0]);
    resultPoints.Empilha(points[1]);
    resultPoints.Empilha(points[2]);
   
    for(int i=3;i<m;i++){
        //remoção dos pontos até que nextToTop, top e points[i] formem uma curva que não seja no sentido anti-horário
        while (orientation(nextToTop(resultPoints), resultPoints.top(), points[i]) != 1) {
            resultPoints.Desempilha();
        }
        resultPoints.Empilha(points[i]);
    }
   return resultPoints;
}

//-------
//
//->Pilha
//
//-------

template <typename Tipo>
Pilha<Tipo>::Pilha() {
    topo = -1;
    length = 0;
}

template <typename Tipo>
bool Pilha<Tipo>::isEmpty() {
    return topo == -1;
}

template <typename Tipo>
void Pilha<Tipo>::Empilha(Tipo item) {
    topo++;
    elementos_[topo] = item;
}

template <typename Tipo>
int Pilha<Tipo>::size(){
    return topo+1;
}

template <typename Tipo>
Tipo Pilha<Tipo>::Desempilha() {
    Tipo valor = elementos_[topo];
    topo--;
    return valor;
}

template <typename Tipo>
Tipo Pilha<Tipo>::top() {
    return elementos_[topo];
}