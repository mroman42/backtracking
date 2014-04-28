/**
 * tsp.cpp
 * Traveling Salesman Problem.
 * Implementación de un algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef unsigned int uint;
typedef pair<int,int> Point;
vector<Point> ciudades;
int dimension;

void permutaciones () {
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
    // Para cada ciudad visitada, añade a sus vecinos no visitados a la cola.
    queue<Point> a_visitar;

    a_visitar.push(ciudades[0]);
    while (!a_visitar.empty()) {
	Point actual = a_visitar.front();
	a_visitar.push();
    }
}
