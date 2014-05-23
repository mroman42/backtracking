/**
 * 3matching.cpp
 * 3 dimensional matching problem.
 * Implementación del algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <utility>
using namespace std;
typedef unsigned int uint;

// Estructura para representar una arista.
// Indica los tres puntos en los tres conjuntos unidos por la arista.
struct Arista {
    int a;
    int b;
    int c;

    Arista (int x, int y, int z)
    :a(x), b(y), c(z)
    {}
};

ostream& operator << (ostream& output, Arista& arista) {
    cout << "(" << arista.a << "," << arista.b << "," << arista.c << ")";
    return output;
}

template<class T>
ostream& operator<< (ostream& output, vector<T>& v){
    for (auto i : v)
        output << i;
    output << endl;
    return output;
}

// Tamaños de las tablas de nodos
int sizea = 0;
int sizeb = 0;
int sizec = 0;

// Estructura para representar una asignación.
// Señala las aristas seleccionadas y los nodos usados de cada conjunto.
// Señala además la cardinalidad de la asignación (su valor).
struct Matching {
    int valor;
    vector<bool> aristas;
    vector<bool> nodosa;
    vector<bool> nodosb;
    vector<bool> nodosc;

    Matching ()
    : valor(0),
    nodosa(sizea, false),
    nodosb(sizeb, false),
    nodosc(sizec, false)
    {}
};

struct cmp{
    bool operator() (const Matching& una,
                     const Matching& otra){
        return una.valor < otra.valor;
                     }
};

Matching resolver(vector<Arista> aristas, vector<int> preferencias) {
    // Prueba combinaciones de aristas.
    // Marca como true las aristas escogidas.
    #ifdef BBOUND
    priority_queue<Matching, vector<Matching>, cmp> posibles_particiones;
    #else
    stack<Matching> posibles_particiones;
    #endif
    Matching solucion;
    uint tamanio = aristas.size();

    // Prueba cada posible asignación, empezando por la vacía.
    posibles_particiones.push(Matching());
    while (!posibles_particiones.empty()) {
        Matching actual = posibles_particiones.top();
        posibles_particiones.pop();
        uint indice = actual.aristas.size();

        // Caso de matching completo
        if (indice == tamanio) {
            if (actual.valor > solucion.valor)
                solucion = actual;
        }

        // Caso de matching por completar.
        // Añade el caso de que se obtenga la arista o no.
        else {
            Matching con_nueva = actual;
            Matching sin_nueva = actual;
            con_nueva.aristas.push_back(true);
            sin_nueva.aristas.push_back(false);

            Arista nueva_arista = aristas[indice];

            #ifdef BBOUND
            int sum_pref(0);

            // Condición de poda: poder mejorar la satisfacción de la solución actual
            for (uint i=indice+1; i<tamanio; ++i)
                if ((not actual.nodosa.at(nueva_arista.a)) and
                    (not actual.nodosb.at(nueva_arista.b)) and
                    (not actual.nodosc.at(nueva_arista.c)))
                    sum_pref += preferencias[i];

            if (sin_nueva.valor + sum_pref > solucion.valor)
                posibles_particiones.push(sin_nueva);

            #else
            // Siempre puede continuarse sin añadir nada.
            posibles_particiones.push(sin_nueva);
            #endif

            // Comprobamos si se puede añadir la arista.
            if ((not actual.nodosa.at(nueva_arista.a)) and
                (not actual.nodosb.at(nueva_arista.b)) and
                (not actual.nodosc.at(nueva_arista.c)))
            {
                con_nueva.nodosa[nueva_arista.a] = true;
                con_nueva.nodosb[nueva_arista.b] = true;
                con_nueva.nodosc[nueva_arista.c] = true;
                #ifdef BBOUND
                // Sumamos la preferencia
                con_nueva.valor+= preferencias[indice];
                #else
                con_nueva.valor++;
                #endif
                posibles_particiones.push(con_nueva);
            }
        }
    }
    return solucion;
}
int main () {
    // Bloque de entradas
    vector<Arista> aristas;
    vector<int> preferencias;
    int a,b,c;

    #ifdef BBOUND
    int preferencia;

    while (cin >> a >> b >> c >> preferencia){
        aristas.push_back(Arista(a,b,c));
        preferencias.push_back(preferencia);
    }
    #else
    while (cin >> a >> b >> c)
        aristas.push_back(Arista(a,b,c));
    #endif

    // Bloque de cómputos
    // El tamaño de cada tabla de nodos usados será la mayor de sus componentes.
    for (auto arista : aristas) {
        if (sizea < arista.a+1)
            sizea = arista.a+1;
        if (sizeb < arista.b+1)
            sizeb = arista.b+1;
        if (sizec < arista.c+1)
            sizec = arista.c+1;
    }

    Matching solucion = resolver(aristas, preferencias);

    // Bloque de salidas
    // Escribe la solución.
    cout << "Solución:\n";
    for (uint i=0; i<aristas.size(); i++)
        if (solucion.aristas[i])
            cout << aristas[i] << endl;
    #ifdef BBOUND
    cout << "Satisfacción: ";
    #else
    cout << "Cardinalidad: ";
    #endif
    cout << solucion.valor << endl;
}
