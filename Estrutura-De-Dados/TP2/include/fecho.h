#include "./Pilha.h"
#include <string>

using namespace std;

struct Point {
    int x; int y;
};

class Fecho {
    private:
        int orientation(Point first, Point second, Point third);
        void order(Point points[], int length, int type, Point p0);        
        void mergeSort(Point points[], int const init, int const fim, Point p0);
        void merge(Point points[], int const init, int const mid, int const fim, Point p0);
        void insertionSort(Point points[], int length, Point p0);
        void bucketSort(Point points[], int length, Point p0);

    public:
        Pilha<Point> jarvisMarch(Point points[], int length);
        Pilha<Point> grahamScan(Point points[], int length, int tipoOrder);
};