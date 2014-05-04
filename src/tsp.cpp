/**
 * tsp.cpp
 * Traveling Salesman Problem.
 * Implementación de un algoritmo de backtracking en C++.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

typedef unsigned int uint;
typedef std::pair<double,double> Point;
typedef std::vector<int> Ruta;
typedef float Coste;


// Función de impresión de vectores
template<class T>
std::ostream& operator<< (std::ostream& output, std::vector<T>& v){
    for (auto i : v)
        output << i << ' ';
    
    output << std::endl;
    return output;
}


std::vector<Point> ciudades;
uint dimension;
Ruta mejor_ruta;
Coste mejor_coste;


Coste distancia (int i, int j) {
    // Calcula la distancia entre dos puntos.
    Point a = ciudades[i];
    Point b = ciudades[j];
    
    Coste x = a.first - b.first;
    Coste y = a.second - b.second;
    
    return sqrt(x*x + y*y);
}

#ifdef OPTBOUND
bool cruce (int u, int v, int w, int z) {
    // Calcula si se cruzan los segmentos uv, wz.
    Point a = ciudades[u];
    Point b = ciudades[v];
    Point c = ciudades[w];
    Point d = ciudades[z];
	
    return distancia(u,v) + distancia(w,z) > distancia(u,w) + distancia(v,z);
}
#endif

// Función de depuración
/* 
Coste total (Ruta &ruta){
    Coste result(0);
    for (uint i = 1; i <= ruta.size(); ++i){
        result += distancia (i-1,i%ruta.size());
    }
    return result;
}

*/
void permutaciones(Ruta& ruta, Coste& coste_actual, uint indice){
    Coste arista;

    // Caso de la ruta finalizada
    // Comprueba si se mejora el óptimo.    
    if (indice == dimension and (coste_actual + (arista = distancia(ruta[indice-1], ruta[0]))) < mejor_coste) {
        mejor_ruta = ruta;
        mejor_coste = coste_actual + arista;
    }
    
    #ifdef BBOUND
    // Caso de superar el coste óptimo.
    // No es necesario seguir estudiando este caso.
    else if (coste_actual > mejor_coste)
        return;
    #endif
    

    // Caso de recorrido intermedio
    // Prueba posibles permutaciones para los restantes elementos.
    else {
        for (uint i = indice; i < dimension; ++i) {
    	    #ifdef OPTBOUND
	    // Caso en el que la permutación introduciría un cruce de caminos.
	    // Por optimización OPT-2, no puede ser el óptimo.
	    bool opt2 = false;
	    for (uint j = 0; j < indice-1 and !opt2; j++)
		opt2 = cruce(ruta[i],ruta[indice-1], ruta[j],ruta[j+1]);

	    if (opt2)
		return;
            #endif


            // Produce una permutación en la ruta.
            uint temp = ruta[i];
            ruta[i] = ruta[indice];
            ruta[indice] = temp;
            
            coste_actual += distancia(ruta[indice - 1], ruta[indice]);
            
            // Estudia permutaciones con ese cambio.
            permutaciones (ruta, coste_actual, indice + 1);
            
            // Deshace la permutación.
            coste_actual -= distancia(ruta[indice - 1], ruta[indice]);
            ruta[indice] = ruta[i];
            ruta[i] = temp;
        }
    }
}


int main() {
    Coste coste_actual(0);
    mejor_coste = std::numeric_limits<Coste>::infinity();
    
    // Lectura del problema
    std::cout << "Introduce número de ciudades del problema: ";
    std::cin >> dimension;
    ciudades.resize(dimension);
    
    for (auto& p : ciudades)
        std::cin >> p.first >> p.second;
    
    // Resolución del problema
    // Recorre las posibles permutaciones dejando fija la primera ciudad.
    // Crea una primera ruta con la permutación identidad.
    Ruta ruta(dimension);
    std::iota(ruta.begin(),ruta.end(),0);

    permutaciones(ruta, coste_actual, 1);
    
    // Muestra la solución
    std::cout << "Mejor coste obtenido: " << mejor_coste << std::endl
              << "Mejor ruta: " << std::endl << mejor_ruta;
    
    // Depuración
    //std::cout << "Recalculado: " << total(mejor_ruta);
}
