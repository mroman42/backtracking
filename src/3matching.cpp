/**
 * 3matching.cpp
 * 3 dimensional matching problem.
 * Implementación del algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <chrono>
using namespace std;
typedef unsigned int uint;

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

ostream& operator << (ostream& output, Arista& arista) {
    cout << "(" << arista.a << "," << arista.b << "," << arista.c << ")";
    return output;
}


// Tamaños de las tablas de nodos
int sizea = 0;
int sizeb = 0;
int sizec = 0;

// Estructura para representar una asignación.
// Señala las aristas seleccionadas y los nodos usados de cada conjunto.
// Señala además la cardinalidad de la asignación (su valor).
struct Matching {
    vector<bool> aristas;
    vector<bool> nodosa;
    vector<bool> nodosb;
    vector<bool> nodosc;
    int valor;

    Matching ()	
	: aristas(), 
	  nodosa(false, sizea), 
	  nodosb(false, sizeb),
	  nodosc(false, sizec),
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
    for (Arista arista : aristas) {
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
    uint tamanio = aristas.size();
    
    // Prueba cada posible asignación, empezando por la vacía.
    posibles_particiones.push(Matching());
    while (!posibles_particiones.empty()) {
	Matching actual = posibles_particiones.front();
	posibles_particiones.pop();
	uint indice = actual.aristas.size();

	// Caso de matching completo
	if (indice == tamanio) {
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

	    // Siempre puede continuarse sin añadir nada.
	    posibles_particiones.push(sin_nueva);

	    // Comprobamos si se puede añadir la arista.
	    Arista nueva_arista = aristas[indice];
	    if ((not actual.nodosa[nueva_arista.a]) and 
		(not actual.nodosb[nueva_arista.b]) and
		(not actual.nodosc[nueva_arista.c])) 
	    {
		con_nueva.nodosa[nueva_arista.a] = true;
		con_nueva.nodosb[nueva_arista.b] = true;
		con_nueva.nodosc[nueva_arista.c] = true;
		con_nueva.valor++;
		posibles_particiones.push(con_nueva);
 	    }
	}
    }
    
    // Bloque de salidas
    // Escribe la solución.
    cout << "Solución:\n";
    for (uint i=0; i<aristas.size(); i++)
	if (solucion.aristas[i])
	    cout << aristas[i] << endl;
    cout << "Cardinalidad: " << solucion.valor << endl;
}
