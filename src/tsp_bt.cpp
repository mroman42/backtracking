/**
 * tsp.cpp
 * Traveling Salesman Problem.
 * Implementación de un algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>
#include <chrono>
using namespace std;

typedef unsigned int uint;
typedef pair<double,double> Point;
typedef vector<int> Ruta;
typedef float Coste;


// Función de impresión de vectores
template<class T>
ostream& operator<< (ostream& output, vector<T>& v){
    for (auto i : v)
        output << i << ' ';

    output << endl;
    return output;
}


vector<Point> ciudades;
uint dimension;
Ruta mejor_ruta;
Coste mejor_coste;

Coste distancia (int i, int j) {
    // Calcula la distancia entre dos puntos.
    Point a = ciudades[i];
    Point b = ciudades[j];

    Coste x = a.first - b.first;
    Coste y = a.second - b.second;

    return sqrt(x*x + y*y);
}

void permutaciones(Ruta& ruta, Coste coste_actual, uint indice){
    // Caso de la ruta finalizada
    // Comprueba si se mejora el óptimo.
    if (indice == dimension) {
	    Coste coste_total = coste_actual + distancia(ruta[indice-1], ruta[0]);

	    if (coste_total < mejor_coste) {
	        mejor_ruta = ruta;
	        mejor_coste = coste_total;
	    }
    }
    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
        for (uint i = indice; i < dimension; ++i) {
            // Produce una permutación en la ruta.
            uint temp = ruta[i];
            ruta[i] = ruta[indice];
            ruta[indice] = temp;

            coste_actual += distancia(ruta[indice - 1], ruta[indice]);

            // Estudia permutaciones con ese cambio.
            permutaciones (ruta, coste_actual, indice + 1);

            // Deshace la permutación.
            coste_actual -= distancia(ruta[indice - 1], ruta[indice]);
            ruta[indice] = ruta[i];
            ruta[i] = temp;
        }
    }
}


int main() {
    Coste coste_actual(0);
    mejor_coste = numeric_limits<Coste>::infinity();

    // Lectura del problema
    cin >> dimension;
    ciudades.resize(dimension);

    for (auto& p : ciudades)
        cin >> p.first >> p.second;

    // Resolución del problema
    // Recorre las posibles permutaciones dejando fija la primera ciudad.
    // Crea una primera ruta con la permutación identidad.
    Ruta ruta(dimension);
    iota(ruta.begin(),ruta.end(),0);

    auto time1 = chrono::high_resolution_clock::now();
    permutaciones(ruta, coste_actual, 1);
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    double time = time_span.count();

    // Muestra la solución
    cout << "Mejor coste obtenido: " << mejor_coste << endl
        << "Mejor ruta: " << endl << mejor_ruta
	    << "Tiempo de cómputo: " << time << endl;
}
