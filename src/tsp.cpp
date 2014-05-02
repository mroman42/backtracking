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
#include <numeric>

using namespace std;
typedef unsigned int uint;
typedef std::pair<int,int> Point;
typedef std::vector<int> Ruta;
typedef float Coste;

template<class T>
ostream& operator<< (ostream& output, std::vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << std::endl;
}


std::vector<Point> ciudades;
int dimension;
Ruta mejor_ruta;
Coste mejor_coste;


Coste distancia (int i, int j) {
    // Calcula la distancia entre dos puntos.
    Point a = ciudades[i];
    Point b = ciudades[j];
    
    Coste x = a.first - b.first;
    Coste y = a.second - b.second;
    return sqrt(x*x - y*y);
}

void permutaciones(Ruta& ruta, Coste& coste_actual, int indice){
    // Caso de la ruta finalizada
    // Comprueba si se mejora el óptimo.
    if (indice == dimension) {
        if (coste_actual < mejor_coste) {
            mejor_ruta = ruta;
            mejor_coste = coste_actual;
        }
    }
    
    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
        for (int i = indice; i < dimension; ++i) {
            // Produce una permutación en la ruta.
            Point temp = ruta[i];
            ruta[i] = ruta[indice];
            ruta[indice] = temp;
            coste_actual += distancia(ruta[indice - 1], ruta[indice]);
            
            // Estudia permutaciones con ese cambio.
            permutaciones (ruta, coste_actual, indice + 1);
            
            // Deshace la permutación.
            coste_actual -= distancia(ruta[indice - 1], ruta[indice]);
            ruta[i] = ruta[indice];
            ruta[indice] = temp;
        }
    }
}


int main() {
    Coste coste_actual;s
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
    Ruta ruta(dimension);
    std::iota(ruta.begin(),ruta.end(),0);
    
    mejor_ruta = ruta;
    mejor_coste = numeric_limits<Coste>::infinity();
    
    permutaciones(ruta, 0, 1);
    
    // Muestra la solución
    std::cout << "Mejor coste obtenido: " << mejor_coste << std::endl
              << "Mejor ruta: " << std::endl << ruta;
}
