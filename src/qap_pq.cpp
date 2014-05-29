/**
 * qap.cpp
 * Quadratic Assignment Problem
 * Implementación de un algoritmo de backtracking en C++.
 */
#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <chrono>
#include <stack>
#include <queue>
using namespace std;

#if defined(BBOUND1) || defined(BBOUND2) || defined(BBOUND3)
#define BBOUND
#endif

typedef unsigned int uint;
typedef vector<int> Permutacion;
typedef double Coste;
typedef struct {
    Permutacion p;
    unsigned indice;
    double cota;
} Nodo;

template<class T> ostream& operator<< (ostream& output, vector<T>& v);
template<class T> istream& operator>> (istream& input, vector<T>& v);


// Datos globales del problema
uint dimension;
uint nodos_expandidos(0);
uint nodos_podados(0);
uint tam_maximo(0);
Coste mejor_coste;
vector<vector<double>> w;
vector<vector<double>> d;

// Coste de una permutación
double cost (Permutacion &p, uint n){
    double sum(0);
    
    for (uint i=0; i<n; ++i)
        for (uint j=0; j<n; ++j)
            sum += w[i][j] * d[p[i]][p[j]];
        
    return sum;
}

void actualiza_cota1 (Nodo &actual){
    actual.cota = cost(actual.p, actual.indice + 1);
    double coste_actual;
    double minimo;
    
    // Calculamos una cota inferior para el problema
    for (uint h = actual.indice + 1; h < dimension; ++h ){
        minimo = numeric_limits<Coste>::infinity();
        
        for (uint j = actual.indice + 1; j < dimension; ++j){
            coste_actual = 0;
            uint p_j = actual.p[j];
            
            for (uint k = 0; k < actual.indice + 1; ++k){
                uint p_k = actual.p[k];
                coste_actual += w[k][h] * d[p_k][p_j] + w[h][k] * d[p_j][p_k];
            }
            coste_actual += w[h][h] * d[p_j][p_j];
            
            if (coste_actual < minimo)
                minimo = coste_actual;
        }
        actual.cota += minimo;
    }
}

void actualiza_cota2 (Nodo &actual){
    actual.cota = cost(actual.p, actual.indice + 1);
    double minimo_i;
    double minimo_ii;

    // Calculamos una cota inferior para el problema
    for (uint h = 0; h < actual.indice + 1; ++h){
        
        for (uint j = actual.indice + 1; j < dimension; ++j){
            minimo_i = minimo_ii = numeric_limits<Coste>::infinity();
        
            for (uint k = actual.indice + 1; k < dimension; ++k){
                uint p_h = actual.p[h];
                uint p_k = actual.p[k];
                
                if (d[p_h][p_k] < minimo_i)
                    minimo_i = d[p_h][p_k];
            
                if (d[p_k][p_h] < minimo_ii)
                    minimo_ii = d[p_k][p_h];
            }
            actual.cota += w[h][j] * minimo_i + w[j][h] * minimo_ii;   
        }
    }
}

void actualiza_cota3 (Nodo &actual){
    actual.cota = cost(actual.p,actual.indice + 1);
}

double coste_greedy (Permutacion actual){
    double min = numeric_limits<Coste>::infinity();
    uint s = actual.size();
    uint max_w_index, min_d_index;
    double max_weight, min_distance;
    Permutacion p, mejor;
    
    for (uint i = 0; i < s; ++i){
        p = actual;
        vector<bool> fab_asignada(s,false);
        vector<bool> loc_asignada(s,false);
        uint j = i;
        
        for (uint recorridas = 1; recorridas < s; ++recorridas){
            fab_asignada[j] = true;
            loc_asignada[p[j]] = true;
            max_weight = 0;
            min_distance = numeric_limits<Coste>::infinity();
            
            for (uint k = 0; k < s; ++k){
                if (!fab_asignada[k]){
                    if (w[i][k] > max_weight){
                        max_w_index = k;
                        max_weight = w[i][k];
                    }
                    if (d[i][k] < min_distance){
                        min_d_index = k;
                        min_distance = d[i][k];
                    }
                }   
            }
            
            p[max_w_index] = min_d_index;
            j = max_w_index;
        }
        
        if (cost(p, dimension) < min){
            mejor = p;
        }
    }
    
    return cost(mejor, dimension);
}

struct cmp {
    bool operator()(Nodo& una, Nodo& otra) {
        return una.cota < otra.cota;
    }
};

// Comprueba todas las permutaciones a partir de una dada
Nodo resuelve(){
    #if defined(BBOUND1) || defined(BBOUND2) || defined(BBOUND3)
    priority_queue<Nodo, vector<Nodo>, cmp> posibles;
    #else
    stack<Nodo> posibles;
    #endif
    
    Nodo mejor({ Permutacion(dimension), 0, 0});
    iota(mejor.p.begin(), mejor.p.end(), 0);
    
    posibles.push(mejor);
    mejor_coste = coste_greedy(mejor.p);
    
    while(!posibles.empty()){
        #ifdef BBOUND
        if (posibles.size() > tam_maximo){
            tam_maximo = posibles.size();
        }
        #endif
        Nodo actual = posibles.top();
        posibles.pop();
        
        // Caso de permutación completa
        // Comprueba si se mejora el óptimo.  
        if (actual.indice == dimension) {
            Coste total = cost(actual.p,dimension);
            
            if (total <= mejor_coste) {
                mejor.p = actual.p;
                mejor_coste = total;
            }
        }    

        // Caso de recorrido intermedio
        // Prueba posibles permutaciones para los restantes elementos.
        else {
            // Variables para los Branch & Bound
            #ifdef BBOUND1
            double minimo;
            double coste_actual;
            #endif
            #ifdef BBOUND2
            double minimo_i;
            double minimo_ii;
            #endif
            
            for (uint i = actual.indice; i < dimension; ++i) {
                // Produce una permutación en la ruta.
                uint temp = actual.p[i];
                actual.p[i] = actual.p[actual.indice];
                actual.p[actual.indice] = temp;

                #ifdef BBOUND1
                actualiza_cota1(actual);
                #endif
                #ifdef BBOUND2                
                actualiza_cota2(actual);
                #endif
                #ifdef BBOUND3
                actualiza_cota3(actual);               
                #endif
                
                #ifdef BBOUND
                // Si la permutación actual es peor que la mejor en cuanto a coste,
                // no la introducimos
                if (actual.cota < mejor_coste){
                #endif
                    actual.indice++;
                    posibles.push(actual);
                    actual.indice--;
                    nodos_expandidos++;
                #ifdef BBOUND
                }
                else
                    nodos_podados++;
                #endif
                
                
                // Deshace la permutación
                actual.p[actual.indice] = actual.p[i];
                actual.p[i] = temp;
            }
        }
    }
    return mejor;
}


int main(){
    mejor_coste = numeric_limits<Coste>::infinity();
    Nodo mejor;
    // Bloque de lecturas
    // Lectura del problema
    cin >> dimension;

    w.resize(dimension);
    d.resize(dimension);
    for (uint i=0; i<dimension; ++i) {
        w[i].resize(dimension);
        d[i].resize(dimension);
    }

    cin >> w;
    cin >> d;


    // Bloque de cómputos
    // Resolución desde la permutación inicial calculando el tiempo que tarda
    auto time1 = chrono::high_resolution_clock::now();
    mejor = resuelve();
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    double time = time_span.count();


    // Bloque de salidas
    cout << "Mejor coste obtenido: " << mejor_coste << endl
        << "Mejor permutación: " << endl << mejor.p
        << "Tiempo de cómputo: " << time << endl
        << "Nodos expandidos: " << nodos_expandidos << endl
        << "Nodos podados: " << nodos_podados << endl;
    #ifdef BBOUND
    cout << "Máximo tamaño de la cola con prioridad: " << tam_maximo << endl;
    #endif
}
 


// Función de impresión de vectores
template<class T>
ostream& operator<< (ostream& output, vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << endl;
    return output;
}

// Función de lectura de vectores
template<class T>
istream& operator>> (istream& input, vector<T>& v){
    for (auto &i : v)
        input >> i;
    
    return input;
}
