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
#include <algorithm>
using namespace std;

typedef unsigned int uint;
typedef pair<vector<bool>,int> Mochila;

template<class T>
ostream& operator<< (ostream& output, vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << endl;
}

struct cmp{
    bool operator() (const Mochila& una, 
                     const Mochila& otra){
        return una.second < otra.second;
    }
};

bool srt(const pair<double,int>& uno, const pair<double,int>& otro){
    return uno.first < otro.first;
}

pair<vector<bool>,int> resolver(int limite, vector<int> pesos, vector<int> beneficios) {
    // Resolución del problema
    uint tamanio = pesos.size();
    
    priority_queue<Mochila, vector<Mochila>, cmp> posibles_mochilas;
    posibles_mochilas.push(Mochila(vector<bool>(),0));
    
    Mochila solucion;
    int max_valor = 0;
    
    // Prueba cada una de las posibles mochilas.
    while (!posibles_mochilas.empty()) {
        Mochila actual = posibles_mochilas.top();
        posibles_mochilas.pop();
        
        // Caso de mochila llena
        // Calculamos su valor y si es mejor que la mejor mochila actual.
        if (actual.first.size() == tamanio) {                    
            if (actual.second > max_valor) {
                max_valor = actual.second;
                solucion = actual;
            }
        }

        // Caso de la mochila sin llenar
        // Rellenamos o no con el siguiente objeto.
        // Añadimos el nuevo si no excede el peso.
        else {
            Mochila con_nuevo = actual;
            Mochila sin_nuevo = actual;
            con_nuevo.first.push_back(true);
            con_nuevo.second += beneficios[actual.first.size()];
            sin_nuevo.first.push_back(false);

            int nuevo_peso = 0;
            for (uint i=0; i<con_nuevo.first.size(); i++)
                nuevo_peso += con_nuevo.first[i] ? pesos[i] : 0;
            if (nuevo_peso <= limite) {
                posibles_mochilas.push(con_nuevo);
            }
            
            
            // Calculamos una cota superior para el llenado de la parte de la mochila que falta
            vector<pair<double,int>> w;
            int n = sin_nuevo.first.size();
            int restante = limite - nuevo_peso + pesos[n-1];
            int max_beneficio(0);
            double coef;
            
            for (uint i=0; i < tamanio - n; ++i)                
                w.push_back(make_pair (beneficios[i+n]/pesos[i+n], i+n));
            
            sort(w.begin(), w.end(), srt);
            
            while (restante != 0 && !w.empty()){
                coef = min(1.0,restante*1.0/pesos[w.back().second]);
                restante -= pesos[w.back().second] * coef;
                max_beneficio += beneficios[w.back().second];
                w.pop_back();
            }
            
            // Si dicha cota superior supera al mejor valor hasta el momento,
            // introducimos la nueva mochila, caso opuesto no
            if (max_valor < sin_nuevo.second + max_beneficio)
                posibles_mochilas.push(sin_nuevo);
        }
    }

    return solucion;
} 

int main () {
    // Lectura del problema
    int limite, leido;
    uint tamanio;
    vector<int> pesos;
    vector<int> beneficios;

    cout << "Introduce límite de peso de la mochila: ";
    cin >> limite;
    cout << "Introduce número de objetos de la mochila: ";
    cin >> tamanio;
    
    cout << "Introduce pesos, separados por espacios:" << endl;
    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        pesos.push_back(leido);
    }
    cout << "Introduce beneficios, separados por espacios:" << endl;
    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        beneficios.push_back(leido);
    }

    Mochila resultado = resolver(limite, pesos, beneficios);

    // Muestra la solución.
    // Muestra la solución.
    cout << endl << "SOLUCIÓN:" << endl 
        << "Valor obtenido: " << resultado.second << endl
        << "Mochila: " << resultado.first << endl;
}
