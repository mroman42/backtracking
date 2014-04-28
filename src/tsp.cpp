/**
 * tsp.cpp
 * Traveling Salesman Problem.
 * Implementación de un algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;
typedef unsigned int uint;
typedef pair<int,int> Point;
typedef vector<int> Ruta;
typedef float Coste;


vector<Point> ciudades;
int dimension;
Ruta mejor_ruta;
Coste mejor_coste;


Coste distancia (Point a, Point b) {
    // Calcula la distancia entre dos puntos.
    Coste x = a.first - b.first;
    Coste y = a.second - b.second;
    return sqrt(x*x - y*y);
}


void permutaciones (Ruta& ruta, Coste& coste_actual, int indice) {
    // Caso de la ruta finalizada
    // Comprueba si se mejora el óptimo.
    if (indice == dimension) {
	if (coste_actual < mejor_coste) {
	    mejor_ruta = ruta;
	    coste_acutal = mejor_coste;
	}
    }

    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
	for (int i=indice; i<dimension; i++) {
	    // Produce una permutación en la ruta.
	    Point temp = ruta[i];
	    ruta[i] = ruta[indice];
	    ruta[indice] = ruta[i];
	    coste_actual += distancia(ruta[indice-1], ruta[indice]);
	    
	    // Estudia permutaciones con ese cambio.
	    permutaciones (ruta, coste_actual, indice+1);

	    // Deshace la permutación.
	    coste_actual -= distancia(ruta[indice-1], ruta[indice]);
	    temp = ruta[i];
	    ruta[i] = ruta[indice];
	    ruta[indice] = ruta[i];
	}
    }
}


int main() {
    // Lectura del problema
    Point leido;
    cin >> dimension;
    for (int i=0; i<dimension; i++) {
	cin >> leido.first;
	cin >> leido.second;
	ciudades.push_back(leido);
    }


    // Resolución del problema
    // Recorre las posibles permutaciones dejando fija la primera ciudad.
    // Crea una primera ruta con la permutación identidad.
    Ruta ruta;
    for (int i=0; i<dimension; ++i) {
	ruta.push_back(i);
    }
    
    mejor_ruta = ruta;
    mejor_coste = numeric_limits<Coste>::infinity();

    permutaciones(ruta, 0, 1);
}
