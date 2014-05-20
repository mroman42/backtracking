def 3dmatching(aristas, preferencias)
    particiones = new Queue
    particiones.push([])

    while not particiones.empty?
        actual = particiones.pop
        if CARDactual == CARDaristas
            if valor(actual) > valor(solucion)
                solucion = actual
        else
            if interseca?(LATEX, actual)
                particiones.push(actual ++ [true])
            if (valor(solucion) < valor(actual) + valorMaximo(actual))
                particiones.push(actual ++ [false])

    return solucion
end

def interseca?(particion, arista)
    return LATEX
end

def valor(particion)
    return LATEX
end

def valorMaximo(actual)
    return LATEX 
end
