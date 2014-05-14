/**
 * planificacion.cpp
 * Problema de planificación en multiprocesadores.
 * Implementación de un algoritmo backtracking en C++.
 */
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;

struct Tarea;

typedef double tiempo;
typedef vector<int>  procesador; // Importantes los dos espacios!

/* Tarea v1: struct */
struct Tarea {
    tiempo ejecucion;

    // Como el grafo es acíclico, cada Tarea solo puede depender de una única Tarea.
    vector<Tarea*> dependencias;
};

/* Tarea v2: clase /
// Similar a una lista enlazada, una Tarea va precedida de una o ninguna Tarea pero
// precede a varias Tareas.
class Tarea {
private:
    // Como el grafo es acíclico, cada Tarea solo puede depender de una única Tarea.
    Tarea* dependencia;
    vector<Tarea*> dependientes;
    time ejecucion;

public:
    Tarea(time t) {
        dependencia = 0;
        ejecucion = t;
    }
    Tarea(time t, Tarea& otra) : Tarea(t) {
        depende(otra);
    }
    Tarea& depende(Tarea& otra) {
        if (dependencia) {
            vector<Tarea*>& deps = dependencia->dependientes;
            deps.erase(std::find(deps.begin(), deps.end(), this));
        }

        dependencia = &otra;

        otra.dependientes.push_back(this);
        return *this;
    }
    const time& tiempo() const { return ejecucion; } // r-value
    time& tiempo() { return ejecucion; } // l-value
    friend struct cmp;
};*/

struct cmp {
    // Esto no es una relación de orden completa
    // Decimos que la tarea 'otra' depende de 'una'
    bool operator() (const Tarea& una, const Tarea& otra) {
        if (otra.dependencias.empty())
            return false;
        else if (std::find(otra.dependencias.begin(), otra.dependencias.end(), &una) != otra.dependencias.end())
            return true;
        else
            // Subimos un nivel
            for (auto& super : otra.dependencias)
                if (operator()(una, *super))
                    return true;

        return false;
    }
};

// Calcula el tiempo (coste) de una ordenación de tareas en un multiprocesador
tiempo hallaTiempo(vector<procesador> historial, vector<Tarea> tareas) {
    tiempo max_time = 0;
    int num_cores = historial[0].size();

    for (int i = 0; i < num_cores; ++i) {
        tiempo suma = 0;

        for (auto& m : historial)
            suma += tareas[m[i]].ejecucion;

        if (suma > max_time)
            max_time = suma;
    }

    return max_time;
}

unsigned cuentaTareas(vector<procesador> historial) {
    unsigned contenidas = 0;

    for (auto& p : historial)
        for (auto& i : p)
            if (i > -1)
                contenidas++;

    return contenidas;
}

/**
 * Representación de una solución
 * Una solución es un vector de procesadores, que a su vez son vectores de
 * enteros de un tamaño específico. Cada entero indica la tarea que se
 * realiza en el núcleo en ese momento, y el vector de procesadores indica
 * la secuencia de tareas que se realizarán en cada núcleo.
 */

vector<procesador> planifica(vector<Tarea> tareas, int num_cores) {
    std::queue<vector<procesador>> posibles;
    vector<procesador> solucion;
    tiempo mejor;

    posibles.push(vector<procesador>());
    posibles.front().push_back(procesador(num_cores, -1));

    while (!posibles.empty()) {
        vector<procesador> actual = posibles.front();
        posibles.pop();

        if (cuentaTareas(actual) == tareas.size()) { // El vector está lleno
            tiempo t_actual = hallaTiempo(actual, tareas);
            if (t_actual < mejor) {
                mejor = t_actual;
                solucion = actual;
            }
        }
        else {
            procesador ahora = actual.front();

            bool very_dependencia = false;
            int core = 0, i = 0;

            while (!very_dependencia && core < num_cores) {
                ahora[core] = i;
                /* TODO
                    Asignar tareas al procesador actual, evitando asignar
                    tareas dependientes de posteriores o actuales

                    Añadir un procesador más con las siguientes tareas de
                    cada core, calculadas de la misma forma

                    Contabilizar el coste y encontrar la solución óptima.
                */
                core++;
            }
        }

    }

    return vector<procesador>();
}

int main (int argc, char const *argv[]) {
    vector<Tarea> tareas;

    tareas.push_back({2, vector<Tarea*>()});
    tareas.push_back({2, {&tareas[0]}});

    return 0;
}
