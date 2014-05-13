/**
 * 3matching.cpp
 * 3 dimensional matching problem.
 * Implementación del algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <queue>
// No estamos usando tuple
#include <tuple>
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
    vector<bool> aristas;
    vector<bool> nodosa;
    vector<bool> nodosb;
    vector<bool> nodosc;
    int valor;
    
    Matching ()	
    : valor(0),
    nodosa(sizea, false), 
    nodosb(sizeb, false),
    nodosc(sizec, false)
    {}
};


int main () {
    // Bloque de entradas
    #ifdef BBOUND
    vector<pair <Arista,int>> aristas;
    int preferencia;
    #else
    vector<Arista> aristas;
    #endif
    int a,b,c;
    
    #ifdef BBOUND
    while (cin >> a >> b >> c >> preferencia)
        aristas.push_back(make_pair(Arista(a,b,c),preferencia));
    #else
    while (cin >> a >> b >> c)
        aristas.push_back(Arista(a,b,c));
    #endif
    
    // Bloque de cómputos
    // El tamaño de cada tabla de nodos usados será la mayor de sus componentes.
    for (auto arista : aristas) {
        #ifdef BBOUND
        if (sizea < arista.first.a+1)
            sizea = arista.first.a+1;
        if (sizeb < arista.first.b+1)
            sizeb = arista.first.b+1;
        if (sizec < arista.first.c+1)
            sizec = arista.first.c+1;
        #else
        if (sizea < arista.a+1)
            sizea = arista.a+1;
        if (sizeb < arista.b+1)
            sizeb = arista.b+1;
        if (sizec < arista.c+1)
            sizec = arista.c+1;
        #endif
    }
    cerr << sizea << sizeb << sizec;
    
    // Prueba combinaciones de aristas.
    // Marca como true las aristas escogidas.
    queue<Matching> posibles_particiones;
    Matching solucion;
    uint tamanio = aristas.size();
    
    // Prueba cada posible asignación, empezando por la vacía.
    posibles_particiones.push(Matching());
    while (!posibles_particiones.empty()) {
        Matching actual = posibles_particiones.front();
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
            
            #ifdef BBOUND
            Arista nueva_arista = aristas[indice].first;
            #else
            Arista nueva_arista = aristas[indice];
            #endif
            
            #ifdef BBOUND
            int sum_pref(0);
            
            // Condición de poda: poder mejorar la satisfacción de la solución actual
            for (uint i=indice+1; i<tamanio; ++i)
                if ((not actual.nodosa.at(nueva_arista.a)) and 
                    (not actual.nodosb.at(nueva_arista.b)) and
                    (not actual.nodosc.at(nueva_arista.c))) 
                sum_pref += aristas[i].second;
            
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
                con_nueva.valor+= aristas[indice].second;
                #else
                con_nueva.valor++;
                #endif
                posibles_particiones.push(con_nueva);
            }
        }
    }
    
    // Bloque de salidas
    // Escribe la solución.
    cout << "Solución:\n";
    for (uint i=0; i<aristas.size(); i++)
        if (solucion.aristas[i])
            #ifdef BBOUND
            cout << aristas[i].first << endl;
            #else
            cout << aristas[i] << endl;
            #endif
        cout << "Cardinalidad: " << solucion.valor << endl;
}
