def mochila(capacidad, pesos, beneficios)
    n = AA pesos
    solucion = [false,\dots,false]
    posibles_mochilas.push([])
    
    while (not posibles_mochilas.empty?)
        actual = posibles_mochilas.pop
        if (actual == n)
            if (beneficio(actual) > beneficio(solucion))
                solucion = actual
        else
            if (peso(actual + [true]) <= capacidad)
                posibles_mochilas.push(actual + [true])
            posibles_mochilas.push(actual + [false])

    return solucion
end

def beneficio(mochila)
    return LATEX
end

def peso(mochila)
    return LATEX
end
