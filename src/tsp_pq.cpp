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

using namespace std;

typedef pair<double,double> Punto;
typedef vector<int> Ruta;
typedef float Coste;
typedef struct {
    Ruta ruta;
    unsigned indice;
    Coste cota;
    Coste coste;
} Nodo;

vector<Punto> ciudades;

// Función de impresión de vectores
template<class T>
ostream& operator<<(ostream& output, vector<T>& v) {
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

Coste restante(Nodo& una) {
    return 0;
}

struct cmp {
    bool operator()(Nodo& una, Nodo& otra) {
        return una.cota < otra.cota;
    }
};

Coste calcula_coste(Ruta& ruta) {
    Coste resultado = 0;
    for (unsigned i = 1; i <= ruta.size(); ++i)
        resultado += distancia(i-1,i%ruta.size());
    return resultado;
}

Nodo resuelve() {
    priority_queue<Nodo, vector<Nodo>, cmp> posibles;
    unsigned dim = ciudades.size();

    // Generamos una ruta inicial, fijamos la primera ciudad
    Nodo mejor({ Ruta(dim), 1, 0, 0 });
    iota(mejor.ruta.begin(), mejor.ruta.end(), 0);
    posibles.push(mejor);
    mejor.coste = numeric_limits<Coste>::infinity();

    while (!posibles.empty()) {
        Nodo actual = posibles.top();
        posibles.pop();

        // Caso de la ruta finalizada
        // Comprueba si se mejora el óptimo.
        if (actual.indice >= dim - 1) {
            Coste total = actual.coste + distancia(actual.ruta[actual.indice-1], actual.ruta[0]);

            if (total < mejor.coste) {
                mejor = actual;
                cout << "estoy asignando " << actual.ruta;
            }
        }
        // Poda: No generamos más hijos si no vamos a mejorar la solución
        else if (actual.cota < mejor.coste) {
            for (unsigned i = actual.indice; i < dim; ++i) {
                bool opt2 = false;

                #ifdef OPTBOUND
                    // Caso en el que la permutación introduciría un cruce de caminos.
                    // Por optimización OPT-2, no puede ser el óptimo.
                    for (unsigned j = 1; j < indice && !opt2; j++)
                        opt2 = cruce(actual.ruta[i],actual.ruta[actual.indice-1],
                            actual.ruta[j], actual.ruta[j-1]);
                #endif

                if (!opt2) {
                    // Produce una permutación en la ruta.
                    Nodo hijo(actual);
                    swap(hijo.ruta[i], hijo.ruta[hijo.indice]);

                    hijo.coste += distancia(hijo.ruta[hijo.indice - 1], hijo.ruta[hijo.indice]);
                    hijo.indice++;

                    posibles.push(hijo);
                    // Estudia permutaciones con ese cambio.
                    //permutaciones (ruta, coste_actual, indice + 1);
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

    // Resolución del problema
    // Recorre las posibles permutaciones dejando fija la primera ciudad.
    // Crea una primera ruta con la permutación identidad.
    Ruta ruta(dimension);
    iota(ruta.begin(),ruta.end(),0);

    auto time1 = chrono::high_resolution_clock::now();
    mejor = resuelve();
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    double tiempo = time_span.count();

    // Muestra la solución
    cout << "Mejor coste obtenido: " << mejor.coste << " " << calcula_coste(mejor.ruta) << endl
        << "Mejor ruta: " << endl << mejor.ruta
        << "Tiempo de cómputo: " << tiempo << endl;
}
