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


    // Bloque de cómputos
    // El tamaño de cada tabla de nodos usados será la mayor de sus componentes.
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;
    for (Triple arista : aristas) {
	if (size1 < get<1>(arista))
	    size1 = get<1>(arista);
	if (size2 < get<2>(arista))
	    size2 = get<2>(arista);
	if (size3 < get<3>(arista))
	    size3 = get<3>(arista);
    }

    // Prueba combinaciones de aristas.
    // Marca como true las aristas escogidas.
    queue<Matching> posibles_particiones;
    Matching solucion;
    int tamanio = aristas.size();
    
    while (!posibles_particiones.empty()) {
	Matching actual = posibles_particiones.top();
	posibles_particiones.pop();

	// Caso de matching completo
	if (actual.aristas.size() == tamanio) {
            if (actual.valor > solucion.valor)
                solucion = actual;
        }

	// Caso de matching por completar.
	// Añade el caso de que se obtega la arista o no.
	else {
	    Matching con_nueva = actual;
	    Matching sin_nueva = actual;
	}
    }
    
    // Bloque de salidas
    
}
