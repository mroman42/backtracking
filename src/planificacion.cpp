#include <vector>
#include <algorithm>

using std::vector;

struct Tarea;

typedef vector<Tarea> procesador;

/* Tarea v1: struct */
struct Tarea {
    double ejecucion;

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

vector<procesador> planifica(vector<Tarea>) {
    return vector<procesador>();
}

int main (int argc, char const *argv[]) {
    vector<Tarea> tareas;

    tareas.push_back((Tarea){2, 0});
    //tareas.push_back({2, &tareas[0]});

    return 0;
}
