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
typedef std::vector<bool> Mochila;

template<class T>
std::ostream& operator<< (std::ostream& output, std::vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << std::endl;
}

std::pair<Mochila, int> resolver(int limite, std::vector<int> pesos, std::vector<int> beneficios) {
    // Resolución del problema
    uint tamanio = pesos.size();
    std::queue<Mochila> posibles_mochilas;
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

    return std::pair<Mochila, int>(solucion, max_valor);
} 

int main () {
    // Lectura del problema
    int limite;
    uint tamanio;
    std::cout << "Introduce límite de peso de la mochila: ";
    std::cin >> limite;
    std::cout << "Introduce número de objetos de la mochila: ";
    std::cin >> tamanio;
    
    std::vector<int> pesos;
    std::vector<int> beneficios;
    int leido;
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

    std::pair<Mochila, int> resultado = resolver(limite, pesos, beneficios);

    // Muestra la solución.
    // Muestra la solución.
    std::cout << std::endl << "SOLUCIÓN:" << std::endl 
        << "Valor obtenido: " << resultado.second << std::endl
        << "Mochila: " << resultado.first << std::endl;
}
