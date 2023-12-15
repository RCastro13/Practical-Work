#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<climits>
#include<ctime>

using namespace std;
const long long int INF = LLONG_MAX;
int power;

//estrutura representando as seções
struct section{
    long long int multiplierBonus, traverseTime;
};

//estrutura representando as manobras
struct trick{
    long long int basePoints, executionTime;
};

//função para pré-computar a pontuações das diferentes possibilidades de manobras
void preComputingPoints(vector<section>& sections, vector<trick>& tricks, vector<vector<long long int>>& pointsMatrix){
    long long int pathPoints = 0;
    int bitJ = 0, bitI = 0;
    
    //preenchendo a matriz da seguinte forma: dados i e j, a posição indica qual a pontuação eu faço com a sequência j dado que eu fiz a sequência i na última seção
    for(int i=0;i<power;++i){
        for(int j=0;j<power;++j){ 
        
            //vou olhar os 10 bits de i e j para saber as manobras realizadas
            for(int h=0;h<tricks.size();++h){
                bitI = (i >> h) & 1;
                bitJ = (j >> h) & 1;
                
                //caso ambos os bits sejam 1, significa que eu quero fazer uma manobra que eu também realizei na última seção (pontuação diminui)
                if(bitJ == 1 && bitI == 1){
                    pathPoints = pathPoints + floor(tricks[h].basePoints/2);
                }
                //caso em j seja 1 e i seja 0, significa que estou realizando uma manobra sem ter feito ela na última seção (pontuação integral)
                else if(bitJ == 1 && bitI == 0){
                    pathPoints = pathPoints + tricks[h].basePoints;
                }
            }
            //atribuo a pontuação para a posição na matriz
            pointsMatrix[i][j] = pathPoints;
            pathPoints = 0;
        }
    }
}

//função para pré-computar o tempo gasto pelas diferentes possibilidades de manobras
void preComputingTime(vector<trick>& tricks, vector<long long int>& pathVector){
    int bitI = 0;
    long long int pathTime = 0;
    for(int i=0;i<power;++i){
        for(int h=0;h<tricks.size();++h){
            bitI = (i >> h) & 1;
            if(bitI == 1){
                pathTime = pathTime + tricks[h].executionTime;
            }
        }
        pathVector[i] = pathTime;
        pathTime = 0;
    }
}

//função recursiva para calcular a pontuação máxima e as manobras realizadas
pair<long long int, int> calculateMaxPoints(int currentSection, int currentMask, vector<section>& sections, vector<trick>& tricks, vector<vector<long long int>>& pointsMatrix, vector<long long int>& pathVector, vector<vector<pair<long long int, int>>>& memo) {
    //Caso base: todas as seções já foram percorridas
    if(currentSection >= sections.size()){
        return {0, 0};
    }

    //caso já tenha calculado a pontuação dessa combinação apenas retorno-a
    if(memo[currentSection][currentMask].first != -INF){
        return memo[currentSection][currentMask];
    }

    long long int maxPoints = 0, trickTime = 0;
    int bestManeuvers = 0;

    //combinando a sequência atual com todas as possíveis sequências de manobras nesta seção
    for(int nextMask=0;nextMask<power;++nextMask){
        trickTime = pathVector[nextMask];

        if(trickTime > sections[currentSection].traverseTime){
            continue;
        }

        //cálculo da pontuação para a transição de currentMask para nextMask na seção atual (pontuação pré-calculada)
        long long int transitionPoints = pointsMatrix[currentMask][nextMask];

        //cálculo da pontuação total para a seção atual (multiplicador * pontosManobras * qntd manobras)
        long long int sectionPoints = sections[currentSection].multiplierBonus * transitionPoints * __builtin_popcountll(nextMask);
        
        //chamada recursiva para encontrar a pontuação máxima para as seções restantes e as manobras realizadas (passo para a próxima seção com a sequência de manobras atual)
        auto result = calculateMaxPoints(currentSection + 1, nextMask, sections, tricks, pointsMatrix, pathVector, memo);
        long long int remainingPoints = result.first;

        //atualização da pontuação máxima caso essa seja uma combinação melhor
        if(sectionPoints + remainingPoints > maxPoints){
            maxPoints = sectionPoints + remainingPoints;
            bestManeuvers = nextMask;
        }
    }

    //memoização do resultado
    memo[currentSection][currentMask] = {maxPoints, bestManeuvers};

    return {maxPoints, bestManeuvers};
}

//função para printar qual manobra eu fiz em cada seção
void printManeuvers(const vector<vector<pair<long long int, int>>>& memo, int numSections, int numTricks) {
    int currentMask = 0;

    //para cada seção eu vou imprimir uma sequência
    for(int i=0;i<numSections;++i){
        int maneuvers = memo[i][currentMask].second;
        vector<int> currentManeuvers;

        for(int j=0;j<numTricks;++j){
            if(maneuvers & (1 << j)){
                currentManeuvers.push_back(j + 1); //Manobra j+1 foi realizada
            }
        }

        //impressão da qtnd manobras e quais manobras foram realizadas na seção
        cout << currentManeuvers.size() << " ";
        for(int maneuver : currentManeuvers){
            cout << maneuver << " ";
        }
        cout << endl;

        currentMask = maneuvers;
    }
}

int main(){

    long long int numSections, numTricks, sectionBonus, sectionTime, trickPoints, trickTime; //variáveis para leitura dos dados

    scanf("%lld %lld", &numSections, &numTricks);
    power = pow(2, numTricks);
    vector<section> sections; //vetor de seções
    vector<trick> tricks; //vetor de manobras
    vector<vector<long long int>> pointsMatrix(power, vector<long long int>(power)); //matriz para pré-computar os pontos
    vector<long long int> pathVector(power); //matriz para pré-computador
    
    //leitura das seções
    for(int i=0;i<numSections;++i){
        scanf("%lld %lld", &sectionBonus, &sectionTime);
        section newSection;
        newSection.multiplierBonus = sectionBonus;
        newSection.traverseTime = sectionTime;
        sections.push_back(newSection);
    }
    //leitura das manobras
    for(int i=0;i<numTricks;++i){
        scanf("%lld %lld", &trickPoints, &trickTime);
        trick newTrick;
        newTrick.basePoints = trickPoints;
        newTrick.executionTime = trickTime;
        tricks.push_back(newTrick);
    }

    //pré-computando todas as possibilidades de pontuação nas seções
    preComputingPoints(sections, tricks, pointsMatrix);

    //pré-computando todas as possibilidades de tempo nas seções
    preComputingTime(tricks, pathVector);
    
    //matriz de recursão da PD e inicializando as posições com -INF (programação dinâmica - memoização)
    vector<vector<pair<long long int, int>>> memo(sections.size(), vector<pair<long long int, int>>(power, {-INF, {}}));

    //início da recursão que retornará a maior pontuação possível e as manobras realizadas em cada seção
    auto result = calculateMaxPoints(0, 0, sections, tricks, pointsMatrix, pathVector, memo);
    long long int maxPoints = result.first;
    int bestManeuvers = result.second;

    //impressão da saída
    cout << maxPoints << endl;
    printManeuvers(memo, numSections, numTricks);

    return 0;
}