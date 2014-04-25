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



class Objeto {
public:
    Objeto (int peso_init, int valor_init)
	:peso(peso_init), valor(valor_init)
    {}

    const int peso;
    const int valor;
};

typedef vector<bool> Mochila;
Mochila rellenar (int n, vector<Objeto>& objeto, int tamanio) {
    if ()
}

int main () {
    // Lectura del problema
    int tamanio;
    int numero;
    vector<int> pesos;
    vector<int> beneficios;
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

    vector<Objeto> objetos;
    for (int i=0; i<numero; i++)
	objetos.push_back(Objeto(pesos[i], beneficios[i]));


    // Resolución del problema
    Mochila mochila(tamanio);
    mochila.llenar(objetos);
    
}
