def qap(permutacion)
    def recorrer(indice)
        if (indice == LATEXciudades)
            if (coste(permutacion, indice) < mejor_permutacion)
                mejor_coste = coste(permutacion)
                mejor_permutacion  = permutacion
        else
            for i in [indice..LATEXciudades]
                swap(permutacion[i], permutacion[indice])
                
                if (coste(permutacion, indice+1) < mejor coste)
                    recorrer(indice+1)
                    
                swap(permutacion[indice], permutacion[i])
    end

    mejor_coste = LATEX
    permutacion = [1..LATEXciudades]
    recorrer(1)

    return mejor_coste
end

def coste(permutacion, n)
    return LATEX
end

