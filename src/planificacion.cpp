/**
 * planificacion.cpp
 * Problema de planificación en multiprocesadores.
 * Implementación de un algoritmo backtracking en C++.
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <numeric>
using namespace std;

typedef double tiempo;
typedef unsigned int uint;
int num_cores;

struct Tarea {
    tiempo ejecucion;
    // Dependencias de otras tareas
    vector<Tarea*> dependencias;
    
    Tarea(tiempo t)
        :ejecucion(t)
    {}
    Tarea()
        :ejecucion(0)
    {}
    
    bool empty(){
        return ejecucion == 0;
    }
};


struct planificacion{
    // Asignaciones de tareas a cores en orden
    vector <pair <uint, Tarea>> asignacion;
    //Estado del procesador en un momento determinado, estará lleno de Tareas vacías cuando se haya terminado la planificación
    vector <Tareas> procesador_actual; 
    // Tareas que faltan por planificar
    vector <Tareas> restantes;
    tiempo t_ejecucion;
    
    planificacion(vector <Tareas> tareas)
        :restantes(tareas),
        t_ejecucion(0),
        procesador_actual(num_cores,null)
    {}
};


// Decimos que la tarea 'otra' depende de 'una' si desciende directamente de ella, o aguna de sus dependencias depende de 'una'
bool depende(const Tarea& una, const Tarea& otra) {
    if (find(otra.dependencias.begin(), otra.dependencias.end(), &una) != otra.dependencias.end())
        return true;
    else
        // Subimos un nivel
        for (auto& super : otra.dependencias)
            if (operator()(una, *super))
                return true;

    return false;
}

planificacion planifica(vector<Tarea> tareas, int num_cores) {
    queue<planificacion> posibles;
    planificacion solucion;

    posibles.push(planificacion(tareas));

    while (!posibles.empty()) {
        planificacion actual = posibles.front();
        posibles.pop();

        if (planificacion.asignacion.size() == tareas.size()) {
            if (actual.t_ejecucion < solucion.t_ejecucion) {
                solucion = actual;
            }
        }
        else{
            tiempo minimo = numeric_limits<tiempo>::infinity();
            
            // Buscamos la tarea en el procesador de menor tiempo de ejecución restante
            for (auto &tarea : planificacion.procesador_actual)
                if (!tarea.empty())
                    if (tarea.ejecucion < min)
                        minimo = tarea.ejecucion;
            
            bool sin_planificar = false;
            // Actualizamos tiempos de ejecución del procesador
            for (auto &tarea : planificacion.procesador_actual){
                tarea.ejecucion -= minimo;
                
                if (tarea.ejecucion > 0)
                    sin_planificar = true;
                else
                    tarea.ejecucion = 0;    
            }
            
            // Si puedo seguir sin planificar nada más, introduzco actual en cola
            if (sin_planificar){
                posibles.push(actual);
            }
            
            
            
        }
    }

    return solucion;
}

int main (int argc, char const *argv[]) {
    vector<Tarea> tareas;
    double t;
    cin >> num_cores;
    
    while (cin >> t){
        tareas.push(Tarea(t));
    }
}
