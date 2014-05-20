def tsp(ciudades)
    def recorrer(indice)
        if (indice == LATEXciudades)
            if (coste(ruta) < mejor_coste)
                mejor_coste = coste(ruta)
                mejor_ruta  = ruta

        else if (coste(ruta) < mejor_coste)
            for i in [indice..LATEXciudades]
                if(!hay_cruce(i, indice))
                    swap(ruta[i], ruta[indice])
                    recorrer(indice+1)
                    swap(ruta[indice], ruta[i])
    end

    mejor_coste = LATEX
    ruta = [1..LATEXciudades]
    recorrer(1)

    return mejor_coste
end

def hay_cruces(i, indice)
    opt2 = false
        for j in [1..indice]
            opt2 = opt2 && (d(ruta[i],ruta[indice]) + d(ruta[j],ruta[j-1]) > d(ruta[i],ruta[j]) + d(ruta[indice],ruta[j-1]))

    return opt2
end

def coste(ruta)
    return LATEX
end
