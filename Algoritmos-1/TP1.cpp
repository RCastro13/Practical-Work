#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<map>
#define PIE 3.14159265359 //número pi para auxiliar a ordenação dos pontos

using namespace std;

//estrutura para vértice
struct point{
    double x, y;
    vector<int> adjacent;
};

//estrutura para aresta
struct edge{
    int start, end;

    //função auxiliar de comparação para ordenação do map
    bool operator<(const edge& other) const{
        if (start < other.start) return true;
        if (start > other.start) return false;
        return end < other.end;
    }
};

//coeficiente da reta orientada de p para q. -> função professor adaptada com PI
double inclinacaoRelativa(point p, point q){
    if (atan2(q.y - p.y, q.x - p.x) < 0){
        return atan2(q.y - p.y, q.x - p.x) + 2*PIE;
    }
    return atan2(q.y - p.y, q.x - p.x);
}

//função auxiliar que indica ao "sort" qual o parâmetro para ordenação (ângulo nesse caso)
bool CompareByAngle(int a, int b, vector<point>& Pontos, point p){
    return inclinacaoRelativa(p, Pontos[a]) < inclinacaoRelativa(p, Pontos[b]);
}

//função para ordenar os pontos pelo maior ângulo de inclinação relativa entre o ponto atual e seus vizinhos
void angleSort(vector<point>& Pontos){
    for (point& p : Pontos){
        sort(p.adjacent.begin(), p.adjacent.end(), [&](int a, int b){
            return CompareByAngle(a, b, Pontos, p);
        });
    }
}

//função que encontra cada face do grafo
vector<int> findFace(int before, int current, vector<point>& vertices){
    vector<int> face;
    face.push_back(before);
    int start = before, end = current;
    int index;

    //realizando 2 iterações antes da busca para preencher 3 posições da face
    for(int i=0;i<2;i++){
        face.push_back(current);
        //pegando o index do before na lista de adj do current + 1 % lista.size() (lógica modular)
        for(int i=0;i<vertices[current].adjacent.size();i++){
            if(before == vertices[current].adjacent[i]){
                index = (i+1) % vertices[current].adjacent.size();
                break;
            }
        }
        int next = vertices[current].adjacent[index];
        before = current;
        current = next;
    }

    //caminhando para continuar a encontrar a face
    while(true){
        face.push_back(current);
        
        //verificando se já encontrei a face inteira
        if(face[0] == face[face.size() - 2] && face[1] == face[face.size() - 1]){
            break; 
        }

        //mesma iteração feita anteriormente para continuar a buscar os vértices da face (lógica modular)
        for(int i=0;i<vertices[current].adjacent.size();i++){
            if(before == vertices[current].adjacent[i]){
                index = (i+1) % vertices[current].adjacent.size();
                break;
            }
        }
        int next = vertices[current].adjacent[index];
        before = current;
        current = next;
    }

    //eliminando o último termo para evitar repetição de vértice
    face.pop_back();
    return face;
}

//função que retorna as faces do grafo
vector<vector<int>> findFaces(int numEdges, vector<point>& vertices, map<edge, int>& edges){
    vector<vector<int>> faces;

    //para cada aresta presente eu começo uma busca de face
    for(const auto& aresta : edges){
        if(aresta.second == 0){
            vector<int> face = findFace(aresta.first.start, aresta.first.end, vertices);
            //tratando a possibilidade dele encontrar uma face com tamanho 3
            if(face.size() > 3){
                //percorrendo a face e marcando as arestas já percorridas
                for(int h=0;h<face.size();h++){
                    if(h <= face.size()-2){
                        edges[{face[h],face[h+1]}] = 1;
                    }
                }
                faces.push_back(face);
            }
        }
    }

    return faces;
}

int main(){

    int numVertex, numEdge, numNeighbor, neighbor;
    double coordY, coordX;

    //leitura da entrada
    cin >> numVertex >> numEdge; //primeira linha
    vector<point> vertices;
    map<edge, int> edges;
    int counter=0;

    //para cada vértice leio uma linha
    for(int i=0;i<numVertex;i++){
        point p;
        cin >> coordX >> coordY;
        cin >> numNeighbor; //3 primeiros nºs da linha do vértice (coordenadas e nº de vizinhos)
        p.x = coordX; 
        p.y = coordY;

        for(int j=0;j<numNeighbor;j++){
            cin >> neighbor; //restante da linha do vértice (vizinhos)
            p.adjacent.push_back(neighbor-1); //preenchendo a lista de adjacência
            edges[{i,neighbor-1}] = 0; //preenchendo o mapa de arestas
        } 
        vertices.push_back(p);
    }

    //ordenando os pontos pelo ângulo
    angleSort(vertices);

    //calculando o total de faces com a fórmula de Euler
    int numFaces = numEdge - numVertex + 2;

    //encontrando as faces do grafo
    vector<vector<int>> faces = findFaces(numEdge, vertices, edges);

    //imprimindo o total de faces e as faces encontradas
    cout << numFaces << endl;
    for(int i=0;i<faces.size();i++){
        cout << faces[i].size() << " ";
        for(int j=0;j<faces[i].size();j++){
            cout << faces[i][j]+1 << " ";
        }
        cout << endl;
    }
    return 0;
}