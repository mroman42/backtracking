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
typedef std::pair<double,double> Point;
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
    
    return sqrt(x*x + y*y);
}

void permutaciones(Ruta& ruta, Coste& coste_actual, uint indice){
    Coste arista;
    // Caso de la ruta finalizada
    // Comprueba si se mejora el óptimo.
    if (indice == dimension && 
        (coste_actual + (arista = distancia(ruta[indice], ruta[0]))) < mejor_coste) {
        mejor_ruta = ruta;
        mejor_coste = coste_actual + arista;
    }
    
    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
        for (uint i = indice; i < dimension; ++i) {
            // Produce una permutación en la ruta.
            auto temp = ruta[i];
            ruta[i] = ruta[indice];
            ruta[indice] = temp;
            
            // Si hay alguna arista...
            if (indice)
                coste_actual += distancia(ruta[indice - 1], ruta[indice]);
            
            
            // Estudia permutaciones con ese cambio.
            permutaciones (ruta, coste_actual, indice + 1);
            
            // Deshace la permutación.
            if (indice)
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
    std::cout << "Introduce número de ciudades del problema: ";
    std::cin >> dimension;
    ciudades.resize(dimension);
    
    for (auto& p : ciudades)
        std::cin >> p.first >> p.second;
    
    // Resolución del problema
    // Recorre las posibles permutaciones dejando fija la primera ciudad.
    // Crea una primera ruta con la permutación identidad.
    Ruta ruta(dimension);
    std::iota(ruta.begin(),ruta.end(),0);

    permutaciones(ruta, coste_actual, 0);
    
    // Muestra la solución
    std::cout << "Mejor coste obtenido: " << mejor_coste << std::endl
              << "Mejor ruta: " << std::endl << mejor_ruta;
}