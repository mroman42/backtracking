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
typedef unsigned int uint;
typedef std::pair<std::vector<bool>,int> Mochila;

template<class T>
std::ostream& operator<< (std::ostream& output, std::vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << std::endl;
}

struct cmp{
    bool operator() (const Mochila& una, 
                     const Mochila& otra){
        return una.second < otra.second;
    }
};

Mochila resolver(int limite, std::vector<int> pesos, std::vector<int> beneficios) {
    // Resolución del problema
    uint tamanio = pesos.size();
    
    std::priority_queue<Mochila, std::vector<Mochila>, cmp> posibles_mochilas;
    posibles_mochilas.push(Mochila(std::vector<bool>(),0));
    
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
            con_nuevo.second += pesos[actual.first.size()];
            sin_nuevo.first.push_back(false);

            int nuevo_peso = 0;
            for (uint i=0; i<con_nuevo.first.size(); i++)
                nuevo_peso += con_nuevo.first[i] ? pesos[i] : 0;
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
    int limite, leido;
    uint tamanio;
    std::vector<int> pesos;
    std::vector<int> beneficios;

    std::cout << "Introduce límite de peso de la mochila: ";
    std::cin >> limite;
    std::cout << "Introduce número de objetos de la mochila: ";
    std::cin >> tamanio;
    
    std::cout << "Introduce pesos, separados por espacios:" << std::endl;
    for (uint i=0; i<tamanio; i++) {
        std::cin >> leido;
        pesos.push_back(leido);
    }
    std::cout << "Introduce beneficios, separados por espacios:" << std::endl;
    for (uint i=0; i<tamanio; i++) {
        std::cin >> leido;
        beneficios.push_back(leido);
    }

    Mochila resultado = resolver(limite, pesos, beneficios);

    // Muestra la solución.
    // Muestra la solución.
    std::cout << std::endl << "SOLUCIÓN:" << std::endl 
        << "Valor obtenido: " << resultado.second << std::endl
        << "Mochila: " << resultado.first << std::endl;
}
