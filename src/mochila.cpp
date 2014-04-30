/**
 * mochila.cpp
 * Problema de la mochila.
 * Implementación de un algoritmo de backtracking en C++.
 *
 * Formato del problema: 
 *  [tamaño de mochila]
 *  [número de objetos]
 *  [vector de pesos]
 *  [vector de beneficios]
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef unsigned int uint;
typedef vector<bool> Mochila;

Mochila resolver(vector<int> pesos, vector<int> beneficios) {
    // Resolución del problema
    queue<Mochila> posibles_mochilas;
    Mochila solucion;
    int max_valor = 0;
    
    // Prueba cada una de las posibles mochilas.
    posibles_mochilas.push(Mochila());
    while (!posibles_mochilas.empty()) {
        Mochila actual = posibles_mochilas.front();
        posibles_mochilas.pop();
        
        // Caso de mochila llena
        // Calculamos su valor y si es mejor que la mejor mochila actual.
        if (actual.size() == tamanio) {
            int valor = 0;
            for (uint i=0; i<tamanio; i++)
                valor += actual[i] ? beneficios[i] : 0;

            if (valor > max_valor) {
                max_valor = valor;
                solucion = actual;
            }
        }

        // Caso de la mochila sin llenar
        // Rellenamos o no con el siguiente objeto.
        // Añadimos el nuevo si no excede el peso.
        else {
            Mochila con_nuevo = actual;
            Mochila sin_nuevo = actual;
            con_nuevo.push_back(true);
            sin_nuevo.push_back(false);

            int nuevo_peso = 0;
            for (uint i=0; i<con_nuevo.size(); i++)
                nuevo_peso += con_nuevo[i] ? pesos[i] : 0;
            if (nuevo_peso <= limite) {
                posibles_mochilas.push(con_nuevo);
            }

            posibles_mochilas.push(sin_nuevo);
        }
    }

    return solucion;
} 

int main () {
    // Lectura del problema
    int limite;
    uint tamanio;
    cin >> limite;
    cin >> tamanio;
    
    vector<int> pesos;
    vector<int> beneficios;
    int leido;
    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        pesos.push_back(leido);
    }
    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        beneficios.push_back(leido);
    }

    Mochila solucion = resolver(pesos, beneficios);

    // Muestra la solución.
    cout << "\nSOLUCIÓN:\n";
    cout << "Valor obtenido: " << max_valor << endl;
    cout << "Mochila: ";
    for (auto &i : solucion)
        cout << i << ',';
    cout << endl;
}
