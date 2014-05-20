def tsp(ciudades)
    def recorrer(indice)
        if (indice == LATEXciudades)
            if (coste(ruta) < mejor_coste)
                mejor_coste = coste(ruta)
                mejor_ruta  = ruta
        else
            for i in [indice..LATEXciudades]
                swap(ruta[i], ruta[indice])
                recorrer(indice+1)
                swap(ruta[indice], ruta[i])
    end

    mejor_coste = LATEX
    ruta = [1..LATEXciudades]
    recorrer(1)

    return mejor_coste
end

def coste(ruta)
    return LATEX
end
