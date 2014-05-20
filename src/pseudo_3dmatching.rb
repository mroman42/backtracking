def 3dmatching(aristas)
    particiones = new Queue
    particiones.push([])

    while not particiones.empty?
        actual = particiones.pop
        if CARDactual == CARDaristas
            if valor(actual) > valor(solucion)
                solucion = actual
        else
            if intersecta?(LATEX, actual)
                particiones.push(actual ++ [true])
            particiones.push(actual ++ [false])

    return solucion
end

def intersecta?(particion, arista)
    return LATEX
end

def valor(particion)
    return LATEX
end
