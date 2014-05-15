<<<<<<< HEAD
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
    tiempo ejecucion;
    // Dependencias de otras tareas
    vector<int> dependencias;

    Tarea(tiempo t, vector<int> deps)
        :ejecucion(t), dependencias(deps) {}
    Tarea(tiempo t) :ejecucion(t) {}
    Tarea() :ejecucion(0) {}

    bool empty(){
        return ejecucion == 0;
    }
};

struct Planificador::Asignacion{
    uint core;
    Tarea tarea;
    tiempo t_inicio;

    Asignacion(uint i, Tarea &t, tiempo &init)
       :core(i), tarea(t), t_inicio(init)
    {}
};

struct Planificador::Planificacion{
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
        t_ejecucion(0)
    {
        procesador_actual.resize(num_cores);
    }
};


// Decimos que la tarea 'otra' depende de 'una' si desciende directamente de ella, o aguna de sus dependencias depende de 'una'
bool Planificador::depende(int una, int otra) {
    if (find(problema[otra].dependencias.begin(), problema[otra].dependencias.end(), una) != problema[otra].dependencias.end()){
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

bool Planificador::empty(const vector<Tarea> &procesador){
    for (auto t : procesador){
        if (!t.empty()){
            return false;
        }
    }
    return true;
}

uint Planificador::gap(vector<Tarea> &procesador){
    for (uint i=0; i<num_cores; ++i){
        if (procesador[i].empty()){
            return i+1;
        }
    }
    return 0;
}

Planificador::Planificacion Planificador::planifica() {
    queue<Planificacion> posibles;
    Planificacion solucion;
    solucion.t_ejecucion = numeric_limits<tiempo>::infinity();

    posibles.push(Planificacion(problema));

   
    while (!posibles.empty()) {
        Planificacion actual = posibles.front();
        posibles.pop();
        cerr << "Actual tiene tamaño: " << actual.t_ejecucion << endl;
        if (actual.historial.size() == problema.size() && empty(actual.procesador_actual)) {
            cerr << "quiero una puta solución" << endl;
            if (actual.t_ejecucion < solucion.t_ejecucion) {
                solucion = actual;
            }
        }
        else {
            bool dependencia;
            uint core = gap(actual.procesador_actual);
            /*
             Si hay core libre, intentamos planificar algún proceso en dicho core
             */
            if (core){
                core--;
                for (uint j=0; j<actual.restantes.size(); ++j){
                    cerr << "Quedan restantes: " << actual.restantes.size() << endl;
                    dependencia = false;
                    for (uint i=0; i<num_cores && !dependencia; ++i){
                        
                        if (actual.procesador_actual[i].empty()){
                            dependencia = depende(i,j);
                        }
                    }
                    
                    for (uint k=0; k<actual.restantes.size() && !dependencia; ++k){
                        if (k!=j){
                            if (!actual.restantes[j].empty())
                                dependencia = depende(k,j);
                        }
                    }
                    
                    if (!dependencia){
                        Planificacion copia_actual = actual;
                        copia_actual.procesador_actual[core] = actual.restantes[j];
                        vector <Tarea>::iterator it = copia_actual.restantes.begin();
                        advance (it,j);
                        copia_actual.restantes.erase(it);
                        copia_actual.historial.push_back(Asignacion(core,actual.restantes[j], copia_actual.t_ejecucion));
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

ostream& operator<<(ostream& out, const Planificador::Tarea& t) {
    out << "Insertado: " << t.ejecucion << "; ";

    for (auto& d : t.dependencias)
        out << d << " ";

    return out;
}

int main (int argc, char const *argv[]) {
    vector<Planificador::Tarea> tareas;
    //Tarea t;
    tiempo ej;
    int dep;

    while (cin.good()) {
        vector<int> dependencias;
        cin >> ej;
        cin >> dep;

        while (dep > -1) {
            dependencias.push_back(dep);
            cin >> dep;
        }

        tareas.push_back(Planificador::Tarea(ej, dependencias));
    }
    Planificador instancia(tareas);

    Planificador::Planificacion solucion = instancia.planifica();
    
    for (auto& asig : solucion.historial)
        cout << asig.core << ": tarea " << &asig.tarea << " (" << asig.t_inicio << ")" << endl;
}