#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef unsigned int uint;

/**
 * Formato del problema: 
 *  [tamaño de mochila]
 *  [número de objetos]
 *  [vector de pesos]
 *  [vector de beneficios]
 */


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

    // Resolución del problema
    typedef vector<bool> Mochila;
    Mochila solucion;
    int max_valor = 0;
    queue<Mochila> posibles_mochilas;
    
    posibles_mochilas.push(Mochila());
    while (!posibles_mochilas.empty()) {
	Mochila actual = posibles_mochilas.front();
	posibles_mochilas.pop();
	
	// Caso de mochila llena
	// Calculamos su valor y si es mejor que la mejor mochila actual.
	if (actual.size() == tamanio) {
	    int valor = 0;
	    for (uint i=0; i<tamanio; i++)
		valor += actual[i]? beneficios[i] : 0;

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
	    for (uint i=0; i<tamanio; i++)
		nuevo_peso += actual[i]? pesos[i] : 0;
	    if (nuevo_peso <= limite)
		posibles_mochilas.push(con_nuevo);
	    posibles_mochilas.push(sin_nuevo);
	}
    }
}
