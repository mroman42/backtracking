/**
 * Planificacion.cpp
 * Problema de planificación en multiprocesadores.
 * Implementación de un algoritmo backtracking en C++.
 */
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

typedef double tiempo;
typedef unsigned int uint;

class Planificador {
public:
    struct Tarea;
    struct Asignacion;
    struct Planificacion;
    static const int num_cores = 4;
    const vector<Tarea> problema;
private:
    bool depende(int una, int otra);
    bool empty(const vector<Tarea> &procesador);
    uint gap(vector<Tarea> &procesador);
public:
    Planificacion planifica();
    Planificador(vector<Tarea> tareas) :problema(tareas) {}
};

struct Planificador::Tarea {
    uint index;
    tiempo ejecucion;
    // Dependencias de otras tareas
    vector<int> dependencias;

    Tarea(uint i, tiempo t, vector<int> deps)
        :index(i), ejecucion(t), dependencias(deps) {}
    Tarea(tiempo t) :ejecucion(t) {}
    Tarea() :ejecucion(0) {}

    bool empty(){
        return ejecucion == 0;
    }
};

// Relaciona una tarea y un procesador
struct Planificador::Asignacion{
    uint core;
    Tarea tarea;
    tiempo t_inicio;

    Asignacion(uint i, Tarea &t, tiempo init)
       :core(i), tarea(t), t_inicio(init)
    {}
};

struct Planificador::Planificacion{
    // Asignaciones de tareas a cores en orden
    vector <Asignacion> historial;
    // Estado del procesador en un momento determinado, estará
    // lleno de Tareas vacías cuando se haya terminado la planificación
    vector <Tarea> procesador_actual;
    // Tareas que faltan por planificar
    vector <Tarea> restantes;
    tiempo t_ejecucion;

    Planificacion(){}

    Planificacion(vector <Tarea> tareas)
        :restantes(tareas),
        t_ejecucion(0)
    {
        procesador_actual.resize(num_cores);
    }
};


// Decimos que la tarea 'otra' depende de 'una' si desciende directamente
// de ella, o aguna de sus dependencias depende de 'una'
bool Planificador::depende(int una, int otra) {
    if (find(problema[otra].dependencias.begin(), problema[otra].dependencias.end(), una)
        != problema[otra].dependencias.end()){
        return true;
    }
    else{
        // Subimos un nivel
        for (auto super : problema[otra].dependencias){
            if (depende(una, super))
                return true;
        }
    }
    return false;
}

// Comprueba si el planificador es vacío
bool Planificador::empty(const vector<Tarea> &procesador){
    for (auto t : procesador){
        if (!t.empty()){
            return false;
        }
    }
    return true;
}

// Busca procesadores vacíos
int Planificador::gap(vector<Tarea> &procesador){
    for (unsigned i=0; i<num_cores; ++i){
        if (procesador[i].empty()){
            return i;
        }
    }
    return -1;
}

struct cmp {
    bool operator()(const Planificador::Planificacion& una,
        const Planificador::Planificacion& otra) {
        return una.t_ejecucion < otra.t_ejecucion;
    }
};

// Crea planificaciones
Planificador::Planificacion Planificador::planifica() {
    #ifdef BBOUND
    priority_queue<Planificacion, vector<Planificacion>, cmp> posibles;
    #else
    stack<Planificacion> posibles;
    #endif

    Planificacion solucion;
    solucion.t_ejecucion = numeric_limits<tiempo>::infinity();

    posibles.push(Planificacion(problema));


    while (!posibles.empty()) {
        Planificacion actual = posibles.top();
        posibles.pop();

        // Si es una planificación de todos las tareas, comprobamos si es mejor que la que ya tenemos
        if (actual.historial.size() == problema.size() && empty(actual.procesador_actual)) {
            if (actual.t_ejecucion < solucion.t_ejecucion) {
                solucion = actual;
            }
        }
        else {
            bool dependencia;
            int core = gap(actual.procesador_actual);
            /*
             Si hay core libre, intentamos planificar algún proceso en dicho core
             */


            if (core > -1){
                // Comprueba si tiene dependencia con...
                for (uint j=0; j<actual.restantes.size(); ++j){
                    dependencia = false;
                    // ·Los que están ejecutándose
                    for (uint i=0; i<num_cores && !dependencia; ++i){

                        if (!actual.procesador_actual[i].empty()){
                            dependencia = depende(actual.procesador_actual[i].index, actual.restantes[j].index);
                        }
                    }
                    // ·Los que aún no se han ejecutado
                    for (uint k=0; k<actual.restantes.size() && !dependencia; ++k){
                        if (k!=j){
                            if (!actual.restantes[j].empty())
                                dependencia = depende(actual.restantes[k].index, actual.restantes[j].index);
                        }
                    }

                    // Si no hay dependencia, lo ejecutamos en el núcleo libre
                    if (!dependencia){
                        Planificacion copia_actual = actual;
                        copia_actual.procesador_actual[core] = actual.restantes[j];
                        vector <Tarea>::iterator it = copia_actual.restantes.begin();
                        advance (it,j);
                        copia_actual.restantes.erase(it);
                        copia_actual.historial.push_back
                            (Asignacion(core, actual.restantes[j], copia_actual.t_ejecucion));
                        posibles.push(copia_actual);
                    }
                }
            }
            // Si el procesador no estaba vacío,...
            if (!empty(actual.procesador_actual)){
                tiempo minimo = numeric_limits<tiempo>::infinity();
                // Buscamos la tarea en el procesador de menor tiempo de ejecución restante
                for (auto &tarea : actual.procesador_actual){
                    if (!tarea.empty()){
                        if (tarea.ejecucion < minimo){
                            minimo = tarea.ejecucion;
                        }
                    }
                }

                // Actualizamos tiempos de ejecución del procesador
                for (Tarea &tarea : actual.procesador_actual){
                    tarea.ejecucion -= minimo;

                    if (tarea.ejecucion < 0)
                        tarea.ejecucion = 0;
                }

                actual.t_ejecucion += minimo;

                #ifdef BBOUND
                if (actual.t_ejecucion < solucion.t_ejecucion)
                #endif
                    posibles.push(actual);
            }
        }
    }
    return solucion;
}

// Mostramos una planificación
ostream& operator<<(ostream& out, const Planificador::Tarea& t) {
    out << t.index << " [tiempo " << t.ejecucion << "; dependencias ";

    for (auto& d : t.dependencias)
        out << d << " ";

    out << "]";

    return out;
}

int main (int argc, char const *argv[]) {
    vector<Planificador::Tarea> tareas;
    //Tarea t;
    tiempo ej;
    int dep;
    int index=0;

    // Leyendo datos
    while (cin >> ej) {
        vector<int> dependencias;

        while ((cin >> dep) && dep > -1) {
            dependencias.push_back(dep);
        }

        tareas.push_back(Planificador::Tarea(index, ej, dependencias));
        index++;
    }
    Planificador instancia(tareas);

    auto time1 = chrono::high_resolution_clock::now();

    Planificador::Planificacion solucion = instancia.planifica();

    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(time2 - time1);
    double time = time_span.count();

    for (auto& asig : solucion.historial)
        cout << "Core " << asig.core << ": tarea " << asig.tarea << " (comenzando en " << asig.t_inicio << ")" << endl;

    cout << "Tiempo total: " << solucion.t_ejecucion << endl;
    cout << "Tiempo de cómputo: " << time << endl;
}
