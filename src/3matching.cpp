/**
 * 3matching.cpp
 * 3 dimensional matching problem.
 * Implementación del algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
using namespace std;

typedef tuple<int,int,int> Triple;
typedef vector<bool> Matching;

class Matching {
public:
    vector<bool> aristas;
    vector<bool> nodos1;
    vector<bool> nodos2;
    vector<bool> nodos3;
    int valor;

    Matching (int size1, int size2, int size3)	
	: aristas(), 
	  nodos1(false, size1), 
	  nodos2(false, size2),
	  nodos3(false, size3),
	  valor(0)
    {}
}


int main () {
    // Bloque de entradas
    vector<Triple> aristas;
    int a,b,c;
    while (cin >> a >> b >> c)
	aristas.push_back(Triple(a,b,c));



    
    // Bloque de salidas
    
}
