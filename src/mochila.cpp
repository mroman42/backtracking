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

    string lineapesos, lineabeneficios;
    getline(cin, lineapesos);
    getline(cin, lineabenef);
    istringstream cinpesos (lineapesos);
    istringstream cinbenef (lineabenef);
    
    int leido;
    while (cinpesos >> leido)
	pesos.push_back(leido);
    while (cinbenef >> leido)
	beneficios.push_back(leido);
}
