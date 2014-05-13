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

// Estructura para representar una arista.
// Indica los tres puntos en los tres conjuntos unidos por la arista.
struct Arista {
    int a;
    int b;
    int c;
    
    Arista (int x, int y, int z)
	:a(x), b(y), c(z)
    {}
};

// Estructura para representar una asignación.
// Señala las aristas seleccionadas y los nodos usados de cada conjunto.
// Señala además la cardinalidad de la asignación (su valor).
struct Matching {
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
};


int main () {
    // Bloque de entradas
    vector<Arista> aristas;
    int a,b,c;
    while (cin >> a >> b >> c)
	aristas.push_back(Arista(a,b,c));


    // Bloque de cómputos
    // El tamaño de cada tabla de nodos usados será la mayor de sus componentes.
    int sizea = 0;
    int sizeb = 0;
    int sizec = 0;
    for (Triple arista : aristas) {
	if (sizea < arista.a)
	    sizea = arista.a;
	if (sizeb < arista.b)
	    sizeb = arista.b;
	if (sizec < arista.c)
	    sizec = arista.c;
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
	    con_nueva.aristas.push_back(true);
	    sin_nueva.aristas.push_back(false);

	    // Comprobamos si se puede añadir la arista.
	    Triple nueva_arista = aristas[];
	    if (actual[aristas])


	}
    }
    
    // Bloque de salidas
    
}
