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

/**
 Representación de la solución:
 La solución será un objeto de tipo Mochila, es decir, un par (vector<bool>, int)
 donde el vector contendrá true o false según si el elemento indizado correspondiente
 está contenido en la mochila solución; y el entero representa el beneficio asociado
 a la mochila.

 Tamaño del espacio de soluciones:
 ????

 Backtracking -  Función de poda/acotación:
 peso_actual > peso_maximo

 Branch & Bound - Hijos posibles de un nodo intermedio
 Para una mochila sin llenar, la siguiente mochila puede o no contener
 el siguiente elemento, esto nos da dos hijos (en el código, `con_nuevo` y
 `sin_nuevo`)

 Branch & Bound - Cálculo de las cotas
 Calculamos una cota superior para el beneficio que puede reportar la
 mochila actual.

 Branch & Bound - Estrategia de poda
 Solo introducimos la mochila entre las posibles (pendientes de completar)
 si la cota superior del beneficio es mayor que el mayor beneficio obtenido
 hasta el momento.

 Branch & Bound - Estrategia de ramificación
 WTF?

 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
using namespace std;

typedef unsigned int uint;

typedef pair<vector<bool>,int> Mochila;

template<class T>
ostream& operator<< (ostream& output, vector<T>& v){
    for (auto i : v)
        output << i << ' ';

    output << endl;
    return output;
}

#ifdef BBOUND
struct cmp{
    bool operator() (const Mochila& una,
                     const Mochila& otra){
        return una.second < otra.second;
    }
};

bool srt(const pair<double,int>& uno, const pair<double,int>& otro){
    return uno.first < otro.first;
}
#endif

Mochila resolver(int limite, vector<int> pesos, vector<int> beneficios) {
    // Resolución del problema
    uint tamanio = pesos.size();

    #ifdef BBOUND
        priority_queue<Mochila, vector<Mochila>, cmp> posibles_mochilas;
    #else
        queue<Mochila> posibles_mochilas;
    #endif

    posibles_mochilas.push(Mochila(vector<bool>(),0));

    Mochila solucion;
    int max_valor = 0;

    // Prueba cada una de las posibles mochilas.
    while (!posibles_mochilas.empty()) {
        #ifdef BBOUND
            Mochila actual = posibles_mochilas.top();
        #else
            Mochila actual = posibles_mochilas.front();
        #endif

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

            con_nuevo.second += beneficios[actual.first.size()];

            con_nuevo.first.push_back(true);
            sin_nuevo.first.push_back(false);

            int nuevo_peso = 0;
            for (uint i=0; i<con_nuevo.first.size(); i++){
                nuevo_peso += con_nuevo.first[i] ? pesos[i] : 0;
            }

            // Acotación (podamos las ramas que lleven a vectores con pesos
            // mayores que el límite)
            if (nuevo_peso <= limite) {
                posibles_mochilas.push(con_nuevo);
            }

            #ifdef BBOUND
	        // Calculamos una cota superior para el llenado de la parte de la mochila que falta

            // pair<double, int> representará un ratio de beneficio por peso asociado
            // al índice del objeto que le corresponde
	        vector<pair<double,int> > w;
	        int n = sin_nuevo.first.size();

            // Peso que queda por llenar
	        int restante = limite - nuevo_peso + pesos[n-1];
	        int beneficio_extra = 0;

	        for (uint i=0; i < tamanio - n; ++i)
		        w.push_back(make_pair (beneficios[i+n]/pesos[i+n], i+n));

	        sort(w.begin(), w.end(), srt);

	        while (restante > 0 && !w.empty()){
                restante -= pesos[w.back().second];
		        beneficio_extra += beneficios[w.back().second];
		        w.pop_back();
	        }

	        // Si dicha cota superior supera al mejor valor hasta el momento,
	        // introducimos la nueva mochila, en caso opuesto no
	        if (max_valor < sin_nuevo.second + beneficio_extra)
            #endif
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

    cin >> limite;
    cin >> tamanio;

    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        pesos.push_back(leido);
    }
    for (uint i=0; i<tamanio; i++) {
        cin >> leido;
        beneficios.push_back(leido);
    }

    auto time1 = chrono::high_resolution_clock::now();
    Mochila resultado = resolver(limite, pesos, beneficios);
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(time2 - time1);
    double time = time_span.count();
    // Muestra la solución.

    cout << endl << "SOLUCIÓN:" << endl
        << "Valor obtenido: " << resultado.second
        << endl << "Mochila: " << resultado.first
        << endl << "Tiempo de cómputo: " << time << endl;
}
