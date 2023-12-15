#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
#include<climits>
const long long int INF = LLONG_MAX;

using namespace std;

//estutura para representar conexões (arestas)
struct connections{
    long long int start, end;

    //função auxiliar de comparação para ordenação do map
    bool operator<(const connections& other) const{
        if (start == other.start){
            return end < other.end;
        }
        return start < other.start;
    }
};

//estrutura para representar os pesos das arestas
struct costs{
    long long int buildTime, crossTime, costValue;
};

//estrutura de Union-Find para melhorar o custo do algoritmo de kruskal
class UnionFind{
    public:
        //criando o conjunto
        void makeSet(long long int n, vector<long long int>& parent, vector<long long int>& rank){
            for(long long int i=0;i<n;i++){
                parent[i] = i;
                rank[i] = 0;
            }
        }
        //encontrando em qual conjunto está o elemento v
        long long int findSet(long long int v, vector<long long int>& parent){
            if(v != parent[v]){
                parent[v] = findSet(parent[v], parent);
            }
            return parent[v];
        }
        //fazendo a união dos conjuntos que u e v estão
        void unionSet(long long int u, long long int v, vector<long long int>& parent, vector<long long int>& rank){
            long long int rootU = findSet(u, parent);
            long long int rootV = findSet(v, parent);

            if(rootU != rootV){
                if(rank[rootU] > rank[rootV]){
                    parent[rootV] = rootU;
                }else if(rank[rootU] < rank[rootV]){
                    parent[rootU] = rootV;
                }else{
                    parent[rootV] = rootU;
                    rank[rootU]++;
                }
            }
        }
};

//execução do algoritmo de kruskal
pair<long long int, long long int> kruskal(map<connections, costs>& arestas, long long int numVertices){
    vector<pair<connections,costs>> orderedEdgesByCost;
    vector<pair<connections,costs>> orderedEdgesByYear;
    vector<long long int> parent1(numVertices, 0), rank1(numVertices, 0), parent2(numVertices, 0), rank2(numVertices, 0); //vetores para o UnionFind

    //convertendo de map para vetor para facilitar a ordenação
    for(const auto& par : arestas){
        orderedEdgesByCost.push_back(par);
        orderedEdgesByYear.push_back(par);
    }

    //ordenando as arestas em ordem crescente de custo de produção
    sort(orderedEdgesByCost.begin(), orderedEdgesByCost.end(), [&](pair<connections,costs>& a, pair<connections,costs>& b){
        return a.second.costValue < b.second.costValue;
    });

    //ordenando as arestas em ordem crescente de tempo
    sort(orderedEdgesByYear.begin(), orderedEdgesByYear.end(), [&](pair<connections,costs>& a, pair<connections,costs>& b){
        return a.second.buildTime < b.second.buildTime;
    });
    
    UnionFind dsuCost, dsuYear;
    dsuCost.makeSet(numVertices, parent1, rank1);
    dsuYear.makeSet(numVertices, parent2, rank2);
    
    long long int custoTotal = 0;
    long long int ano = 0;

    //para cada aresta do grafo (estão ordenadas por custo de produção)
    for(long long int i=0;i<orderedEdgesByCost.size();i++){
        //u e v - aresta kruskal 1 / U e V - aresta kruskal 2
        long long int u = orderedEdgesByCost[i].first.start;
        long long int v = orderedEdgesByCost[i].first.end;
        long long int U = orderedEdgesByYear[i].first.start;
        long long int V = orderedEdgesByYear[i].first.end;

        //kruskal 1 - encontrando o custo total 
        if(dsuCost.findSet(u, parent1) != dsuCost.findSet(v, parent1)){
            custoTotal += arestas[{u,v}].costValue;
            dsuCost.unionSet(u, v, parent1, rank1);
        }
        //kruskal 2 - encontrando o primeiro ano de união de todas as vilas
        if(dsuYear.findSet(U, parent2) != dsuYear.findSet(V, parent2)){
            if(arestas[{U,V}].buildTime > ano){
                ano = arestas[{U,V}].buildTime;
            }
            dsuYear.unionSet(U,V, parent2, rank2);
        }
    }

    pair<long long int, long long int> resp(custoTotal, ano);
    return resp;
}

//execução do algoritmo de dijkstra 
pair<vector<long long int>, long long int> dijkstra(map<connections, costs>& edges, long long int numVillages, vector<vector<long long int>>& villages){

    long long int palace = 0; //palácio
    vector<long long int> dist(numVillages, INF); //vetor de distâncias do palácio para cada vértice
    vector<long long int> year(numVillages, INF); //vetor de anos que a vila pode ser acessável pelo palácio
    vector<bool> visited(numVillages, false); //vetor para verificar se a aresta já foi visitada
    priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int>>, greater<pair<long long int, long long int>>> queue_ordenada; //fila ordenada
    queue_ordenada.push({0, palace}); //entrada da fila
    long long int minYear = 0; //primeiro ano com as distância mutualmente alcançaveis

    dist[palace] = 0; //distância do palácio para ele mesmo
    year[palace] = 0; //ano de construção do palácio

    //enquanto a fila não estiver vazia
    while(!queue_ordenada.empty()){
        long long int u = queue_ordenada.top().second;
        queue_ordenada.pop();

        //caso eu já tenha visitado u eu pulo essa iteração
        if(visited[u]){
            continue;
        }
        visited[u] = true;

        //para cada vizinho do vértice eu faço a iteração
        for(long long int i=0;i<villages[u].size();i++){
            long long int v = villages[u][i];
            //se ainda não viditei o vizinho e seu custo for maior ou igual ao do vértice atual + aresta eu altero os valores
            if(dist[u] + edges[{u, v}].crossTime <= dist[v]){
                dist[v] = dist[u] + edges[{u, v}].crossTime; //alterando o custo (distância) do vértice v
                queue_ordenada.push({dist[v], v}); //insiro o vértice atualizado na pilha
                year[v] = max(year[u], edges[{u,v}].buildTime); //alterando o custo (ano) do vértice v
            }
        }
    }

    //percorrendo o vetor de anos e pegando o maior
    for(long long int i=0;i<year.size();i++){
        if(year[i] > minYear){
            minYear = year[i];
        }
    }
    
    pair<vector<long long int>, long long int> resp(dist, minYear);
    return resp;
}

int main(){
    
    long long int numVillages, numConnections;

    //leitura dos dados de entrada
    scanf("%lld %lld", &numVillages, &numConnections); //qntd arestas e vértices
    vector<vector<long long int>> villages(numVillages); //vetor com as listas de adjacência
    map<connections, costs> edges; //mapa de aresta (aresta, peso)

    for(long long int i=0;i<numConnections;i++){
        long long int firstVillage, secondVillage, buildingTime, crossingTime, costingValue;

        //cin >> firstVillage >> secondVillage >> buildingTime >> crossingTime >> costingValue; //valores de tempo e custo de cada aresta
        scanf("%lld %lld %lld %lld %lld", &firstVillage, &secondVillage, &buildingTime, &crossingTime, &costingValue);

        //preenchendo o map de arestas com seus respectivos custos
        edges[{firstVillage-1, secondVillage-1}] = {buildingTime, crossingTime, costingValue};
        edges[{secondVillage-1, firstVillage-1}] = {buildingTime, crossingTime, costingValue};

        //preenchendo as listas de adjacência de cada vértice
        villages[firstVillage-1].push_back(secondVillage-1);
        villages[secondVillage-1].push_back(firstVillage-1);
    }

    //algoritmo de dijkstra para encontrar caminho e o ano mínimo que conecta o palácio e cada vila
    pair<vector<long long int>, long long int> distance = dijkstra(edges, numVillages, villages);

    //algoritmo de kruskal para encontrar a AGM (menor custo e ano de construção)
    pair<long long int, long long int> totalCost = kruskal(edges, numVillages);

    //tempo mínimo necessário para sair do palácio real e chegar na vila i
    for(long long int i=0;i<distance.first.size();i++){
        printf("%lld\n", distance.first[i]);
    }

    //primeiro ano no qual as distâncias listadas nas linha anteriores são mutuamente realizáveis
    printf("%lld\n", distance.second);

    //primeiro ano a partir do qual é possível chegar em qualquer vila do reino a partir do palácio real
    printf("%lld\n", totalCost.second);

    //menor custo necessário para conectador todo o reino
    printf("%lld\n", totalCost.first);

    return 0;
}