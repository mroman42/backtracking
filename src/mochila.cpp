#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/**
 * Formato del problema: 
 *  [tamaño de mochila]
 *  [número de objetos]
 *  [vector de pesos]
 *  [vector de beneficios]
 */

int main () {
    int tamanio;
    int numero;
    vector<int> pesos;
    vector<int> beneficios;

    // Lectura del problema
    cin >> tamanio;
    cin >> numero;
    
    int leido;
    for (int i=0; i<numero; i++) {
	cin >> leido;
	pesos.push_back(leido);
    }
    for (int i=0; i<numero; i++) {
	cin >> leido;
	beneficios.push_back(leido);
    }

    // Representación del problema

}
