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
#include <algorithm>
#include <chrono>
#include <queue>
#include <stack>

using namespace std;

typedef pair<double,double> Punto;
typedef float Coste;
typedef vector<int> Ruta;
typedef struct {
    Ruta ruta;
    unsigned indice;
    Coste cota_restantes;
    Coste coste;
} Nodo;

vector<Punto> ciudades;

// Función de impresión de vectores
template<class T>
ostream& operator<<(ostream& output, const vector<T>& v) {
    for (auto i : v)
        output << i << ' ';

    output << endl;
    return output;
}


Coste distancia(int i, int j) {
    // Calcula la distancia entre dos Puntos.
    Punto a = ciudades[i];
    Punto b = ciudades[j];

    Coste x = a.first - b.first;
    Coste y = a.second - b.second;

    return sqrt(x*x + y*y);
}

#ifdef OPTBOUND
bool cruce (int u, int v, int w, int z) {
    // Calcula si se cruzan los segmentos uv, wz.
    return distancia(u,v) + distancia(w,z) > distancia(u,w) + distancia(v,z);
}
#endif

struct cmp {
    bool operator()(Nodo& una, Nodo& otra) {
        return una.coste + una.cota_restantes < otra.coste + otra.cota_restantes;
    }
};

vector<int> get_minimos() {
    vector<int> min_distancias;

    for (unsigned i = 0; i < ciudades.size(); ++i) {
        Coste minimo = numeric_limits<Coste>::infinity();

        for (unsigned j = 0; j < ciudades.size(); ++j) {
            Coste posible = distancia(i,j);

            if (posible < minimo && posible > 0) {
                minimo = posible;
            }
        }

        min_distancias.push_back(minimo);
    }

    return min_distancias;
}

Nodo resuelve() {
    priority_queue<Nodo, vector<Nodo>, cmp> posibles;

    unsigned dim = ciudades.size();

    // Generamos una ruta inicial, fijamos la primera ciudad
    Nodo mejor({ Ruta(dim), 1, 0, 0 });
    iota(mejor.ruta.begin(), mejor.ruta.end(), 0);

    vector<int> min_distancias = get_minimos();
    mejor.cota_restantes = accumulate(min_distancias.begin(), min_distancias.end(), 0);

    posibles.push(mejor);
    mejor.coste = numeric_limits<Coste>::infinity();

    while (!posibles.empty()) {
        Nodo actual = posibles.top();
        posibles.pop();

        // Caso de la ruta finalizada
        // Comprueba si se mejora el óptimo
        if (actual.indice == dim) {
            Coste total = actual.coste + distancia(actual.ruta[dim-1], actual.ruta[0]);

            if (total < mejor.coste) {
                mejor.ruta = actual.ruta;
                mejor.coste = total;
            }
        }
        // Poda: No generamos más hijos si no vamos a mejorar la solución
        else if (actual.coste + actual.cota_restantes < mejor.coste) {
            for (unsigned i = actual.indice; i < dim; ++i) {
                bool opt2 = false;

                #ifdef OPTBOUND
                    // Caso en el que la permutación introduciría un cruce de caminos
                    // Por optimización OPT-2, no puede ser el óptimo
                    for (unsigned j = 1; j < actual.indice && !opt2; j++)
                        opt2 = cruce(actual.ruta[i],actual.ruta[actual.indice-1],
                            actual.ruta[j], actual.ruta[j-1]);
                #endif

                if (!opt2) {
                    // Produce una permutación en la ruta
                    Nodo hijo(actual);
                    swap(hijo.ruta[i], hijo.ruta[hijo.indice]);

                    hijo.coste += distancia(hijo.ruta[hijo.indice - 1], hijo.ruta[hijo.indice]);
                    hijo.cota_restantes -= min_distancias[hijo.indice - 1];

                    hijo.indice++;

                    posibles.push(hijo);
                }
            }
        }
    }

    return mejor;
}


int main() {
    unsigned dimension;
    Nodo mejor;

    // Lectura del problema
    cin >> dimension;

    ciudades.resize(dimension);

    for (auto& p : ciudades)
        cin >> p.first >> p.second;

    auto time1 = chrono::high_resolution_clock::now();
    mejor = resuelve();
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    double tiempo = time_span.count();

    // Muestra la solución
    cout << "Mejor coste obtenido: " << mejor.coste << endl
        << "Mejor ruta: " << endl << mejor.ruta
        << "Tiempo de cómputo: " << tiempo << endl;
}
