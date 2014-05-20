def tsp(ciudades):
    # Parte recursiva
    def recorrer(indice):
        if (indice == \ciudades)
            if (coste(ruta) < mejor_coste)
                mejor_coste = coste(ruta)
                mejor_ruta  = ruta
        else
            for i in [indice..ciudades]
                swap(ruta[i], ruta[indice])
                recorrer(indice+1)
                swap(ruta[indice], ruta[i])

    mejor_coste = LATEX
    ruta = [1..ciudades]
    recorrer(1)

    return mejor_coste

def coste(ruta):
    return LATEX


#\sum_{i \in \mathbb{Z}_n} dist(ciudades_{ruta[i]}, ciudades_{ruta[i+1]})
