/**
 * qap.cpp
 * Quadratic Assignment Problem
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
typedef vector<int> Permutacion;
typedef double Coste;

template<class T> ostream& operator<< (ostream& output, vector<T>& v);
template<class T> istream& operator>> (istream& input, vector<T>& v);


// Datos globales del problema
uint dimension;
uint nodos_expandidos(0);
uint nodos_podados(0);
Permutacion mejor_permutacion;
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


// Comprueba todas las permutaciones a partir de una dada
void permutaciones(Permutacion& p, uint indice = 0){
    // Caso de permutación completa
    // Comprueba si se mejora el óptimo.    
    if (indice == dimension) {
        Coste coste_actual = cost(p,dimension);

        if (coste_actual < mejor_coste) {
            mejor_permutacion = p;
            mejor_coste = coste_actual;
        }
    }    

    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
        // Variables para los Branch & Bound
        #ifdef BBOUND1
        double coste;
        double minimo;
        double actual;
        #endif
        #ifdef BBOUND2
        double coste;
        double minimo_i;
        double minimo_ii;
        #endif
        
        for (uint i = indice; i < dimension; ++i) {
            // Produce una permutación en la ruta.
            uint temp = p[i];
            p[i] = p[indice];
            p[indice] = temp;

            #ifdef BBOUND1
            coste = cost(p,indice + 1);
            
            // Calculamos una cota inferior para el problema
            for (uint h = indice + 1; h < dimension; ++h ){
                minimo = numeric_limits<Coste>::infinity();
                for (uint j = indice + 1; j < dimension; ++j){
                    actual = 0;
                    for (uint k = 0; k < indice + 1; ++k){
                        actual += w[k][h] * d[p[k]][p[j]] + w[h][k] * d[p[j]][p[k]];
                    }
                    actual += w[h][h] * d[p[j]][p[j]];
                    
                    if (actual < minimo)
                        minimo = actual;
                }
                coste += minimo;
            }
            if (coste < mejor_coste){
                permutaciones (p, indice + 1);
                nodos_expandidos++;
            }
            else
                nodos_podados++;
            #else 
            #ifdef BBOUND2
            coste = cost(p,indice + 1);
            
            // Calculamos una cota inferior para el problema
            for (uint h = 0; h < indice + 1; ++h){
                for (uint j = indice + 1; j < dimension; ++j){
                    minimo_i = minimo_ii = numeric_limits<Coste>::infinity();
                    for (uint k = indice + 1; k < dimension; ++k){
                        minimo_i = (d[p[h]][p[k]] < minimo_i ? d[p[h]][p[k]] : minimo_i);
                        minimo_ii = (d[p[k]][p[h]] < minimo_ii ? d[p[k]][p[h]] : minimo_ii);
                    }
                    coste += w[h][j] * minimo_i + w[j][h] * minimo_ii;   
                }
            }
            if (coste < mejor_coste){
                permutaciones (p, indice + 1);
                nodos_expandidos++;
            }
            else
                nodos_podados++;
            
            #else
            #ifdef BBOUND3
            // Si la permutación actual es peor que la mejor en cuanto a coste,
            // no la introducimos
            if (cost(p,indice + 1) < mejor_coste){
                permutaciones (p, indice + 1);    
                nodos_expandidos++;
            }
            else
                nodos_podados++;
            #else
            // Estudia permutaciones con ese cambio.
            permutaciones (p, indice + 1);
            nodos_expandidos++;
            #endif
            #endif
            #endif
            // Deshace la permutación
            p[indice] = p[i];
            p[i] = temp;
        }
    }
}


int main(){
    mejor_coste = numeric_limits<Coste>::infinity();
    
    // Bloque de lecturas
    // Lectura del problema
    cin >> dimension;

    Permutacion p(dimension);
    w.resize(dimension);
    d.resize(dimension);
    for (uint i=0; i<dimension; ++i) {
        w[i].resize(dimension);
        d[i].resize(dimension);
    }

    cin >> w;
    cin >> d;
    iota(p.begin(), p.end(), 0);


    // Bloque de cómputos
    // Resolución desde la permutación inicial calculando el tiempo que tarda
    auto time1 = chrono::high_resolution_clock::now();
    permutaciones (p);
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    double time = time_span.count();


    // Bloque de salidas
    cout << "Mejor coste obtenido: " << mejor_coste << endl
        << "Mejor permutación: " << endl << mejor_permutacion
        << "Tiempo de cómputo: " << time << endl
        << "Nodos expandidos: " << nodos_expandidos << endl
        << "Nodos podados: " << nodos_podados << endl;
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
