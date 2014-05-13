#include <vector>
#include <queue>
#include <algorithm>

using std::vector;

struct Tarea;

typedef double tiempo;
typedef vector<Tarea>  procesador; // Importantes los dos espacios!

/* Tarea v1: struct */
struct Tarea {
    tiempo ejecucion;

    // Como el grafo es acíclico, cada Tarea solo puede depender de una única Tarea.
    Tarea* dependencia;
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
        if (otra.dependencia == 0)
            return false;
        else if (otra.dependencia == &una)
            return true;
        else
            // Subimos un nivel
            return operator()(una, *(otra.dependencia));
    }
};

// Calcula el tiempo (coste) de una ordenación de tareas en un multiprocesador
tiempo hallaTiempo(vector<procesador> historial) {
    tiempo max_time = 0;
    int num_cores = historial[0].size();

    for (int i = 0; i < num_cores; ++i) {
        tiempo suma = 0;

        for (auto& m : historial)
            suma += m[i].ejecucion;

        if (suma > max_time)
            max_time = suma;
    }

    return max_time;
}

vector<procesador> planifica(vector<Tarea>, int num_cores) {
    std::queue<vector<procesador>> posibles;
    vector<procesador> solucion;

    posibles.push(vector<procesador>());
    posibles.front().push_back(procesador(num_cores, (Tarea){0,0} ));

    while (!posibles.empty()) {
        //vector<procesador> actual = posibles.front();
        //procesador ahora = actual.front();
        //posibles.pop();

        bool very_dependencia = false;
        int c = 0;

        while (!very_dependencia && c < num_cores) {
            //actual[c] = 0;
            /* TODO
                Asignar tareas al procesador actual, evitando asignar
                tareas dependientes de posteriores o actuales

                Añadir un procesador más con las siguientes tareas de
                cada core, calculadas de la misma forma

                Contabilizar el coste y encontrar la solución óptima.
            */
            c++;
        }

    }

    return vector<procesador>();
}

int main (int argc, char const *argv[]) {
    vector<Tarea> tareas;

    tareas.push_back({2, 0});
    tareas.push_back({2, &tareas[0]});

    return 0;
}
