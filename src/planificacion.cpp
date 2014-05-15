/**
 * Planificacion.cpp
 * Problema de planificación en multiprocesadores.
 * Implementación de un algoritmo backtracking en C++.
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <numeric>
#include <iostream>
using namespace std;

typedef double tiempo;
typedef unsigned int uint;
int num_cores;

struct Tarea {
    tiempo ejecucion;
    // Dependencias de otras tareas
    vector<Tarea*> dependencias;

    Tarea(tiempo t, vector<Tarea*> deps)
        :ejecucion(t), dependencias(deps) {}
    Tarea(tiempo t) :ejecucion(t) {}
    Tarea() :ejecucion(0) {}

    bool empty(){
        return ejecucion == 0;
    }
    bool operator==(const Tarea& otra) {
        return *this == (Tarea&)otra;
    }
};

struct Asignacion{
    uint core;
    Tarea tarea;
    tiempo t_inicio;

    Asignacion(uint i, Tarea &t, tiempo &init)
       :core(i), tarea(t), t_inicio(init)
    {}
};

struct Planificacion{
    // Asignaciones de tareas a cores en orden
    vector <Asignacion> historial;
    //Estado del procesador en un momento determinado, estará lleno de Tareas vacías cuando se haya terminado la planificación
    vector <Tarea> procesador_actual;
    // Tareas que faltan por planificar
    vector <Tarea> restantes;
    tiempo t_ejecucion;

    Planificacion(){}

    Planificacion(vector <Tarea> tareas)
        :restantes(tareas),
        t_ejecucion(0),
        procesador_actual(num_cores)
    {}
};


// Decimos que la tarea 'otra' depende de 'una' si desciende directamente de ella, o aguna de sus dependencias depende de 'una'
bool depende(const Tarea& una, const Tarea& otra) {
    cerr << una.ejecucion << ' ' << otra.ejecucion << ' ' << otra.dependencias.size() << endl;
    //if (!otra.dependencias.empty())
    //    cerr << otra.dependencias[0]->ejecucion;
    
    if (find(otra.dependencias.begin(), otra.dependencias.end(), &una) != otra.dependencias.end()){
        return true;
    }
    else
        // Subimos un nivel
        for (auto super : otra.dependencias)
            if (depende(una, *super))
                return true;

    return false;
}

bool empty(const vector<Tarea> &procesador){
    for (auto t : procesador){
        if (!t.empty()){
            return false;
        }
    }
    return true;
}

uint gap(vector<Tarea> &procesador){
    for (uint i=0; i<num_cores; ++i){
        if (procesador[i].empty()){
            return i+1;
        }
    }
    return 0;
}

Planificacion planifica(vector<Tarea> tareas) {
    queue<Planificacion> posibles;
    Planificacion solucion;

    posibles.push(Planificacion(tareas));

    while (!posibles.empty()) {
        Planificacion actual = posibles.front();
        posibles.pop();
        
        if (actual.historial.size() == tareas.size() && empty(actual.procesador_actual)) {
            if (actual.t_ejecucion < solucion.t_ejecucion) {
                solucion = actual;
            }
        }
        else{
            bool dependencia;
            uint core;

            /*
             Si hay core libre, intentamos planificar algún proceso en dicho core
             */
            if (core = gap(actual.procesador_actual)){
                core--;
                for (uint j=0; j<actual.restantes.size(); ++j){
                    auto a_planificar = actual.restantes[j];
                    dependencia = false;
                    for (uint i=0; i<num_cores && !dependencia; ++i){
                        auto planificada = actual.procesador_actual[i];
                        if (!planificada.empty())
                            dependencia = depende(planificada,a_planificar);
                    }
                    for (uint k=0; k<actual.restantes.size() && !dependencia; ++k){
                        if (k!=j){
                            auto r = actual.restantes[k];
                            if (!r.empty())
                                dependencia = depende(r,a_planificar);
                        }
                    }
                    
                    if (!dependencia){
                        Planificacion copia_actual = actual;
                        copia_actual.procesador_actual[core] = a_planificar;
                        vector <Tarea>::iterator it = copia_actual.restantes.begin();
                        advance (it,j);
                        copia_actual.restantes.erase(it);
                        copia_actual.historial.push_back(Asignacion(core,a_planificar, copia_actual.t_ejecucion));
                        posibles.push(copia_actual);
                    }
                }
            }
            tiempo minimo = numeric_limits<tiempo>::infinity();
            // Buscamos la tarea en el procesador de menor tiempo de ejecución restante
            for (auto &tarea : actual.procesador_actual){
                if (!tarea.empty()){
                    if (tarea.ejecucion < minimo){
                        minimo = tarea.ejecucion;
                    }
                }
            }
            // Si el procesador no estaba vacío
            if (!empty(actual.procesador_actual)){
                bool sin_planificar = false;
                // Actualizamos tiempos de ejecución del procesador
                for (auto &tarea : actual.procesador_actual){
                    tarea.ejecucion -= minimo;

                    if (tarea.ejecucion > 0)
                        sin_planificar = true;
                    else
                        tarea.ejecucion = 0;
                }

                actual.t_ejecucion += minimo;

                // Si puedo seguir sin planificar nada más, introduzco actual en cola
                if (sin_planificar)
                    posibles.push(actual);
            }
            
        }
    }
    return solucion;
}

int main (int argc, char const *argv[]) {
    vector<Tarea> tareas;
    cin >> num_cores;

    //Tarea t;
    tiempo ej;
    int dep;

    while (cin.good()) {
        vector<Tarea*> dependencias;
        cin >> ej;
        cin >> dep;

        while (dep > -1) {
            dependencias.push_back(&tareas[dep]);
            cin >> dep;
        }

        tareas.push_back(Tarea(ej, dependencias));
    }
    Planificacion solucion = planifica(tareas);

    for (auto& asig : solucion.historial)
        cout << asig.core << ": tarea " << &asig.tarea << " (" << asig.t_inicio << ")" << endl;
}
