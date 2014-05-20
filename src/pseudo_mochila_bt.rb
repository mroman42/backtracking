def mochila(capacidad, pesos, beneficios)
    n = LATEXpesos
    solucion = [false,\dots,false]
    posibles_mochilas.push([])
    while (not posibles_mochilas.empty?)
        actual = posibles_mochilas.pop
        if (actual == n)
            if (beneficio(actual) > beneficio(solucion))
                solucion = actual
        else 
            con_nuevo = sin_nuevo = actual
            con_nuevo.push(true)
            sin_nuevo.push(false)
            nuevo_peso = peso(con_nuevo)
            if (nuevo_peso <= capacidad)
                posibles_mochilas.push(con_nuevo)
            posibles_mochilas.push(sin_nuevo)
        
    return solucion
end

def beneficio(mochila)
    return LATEX
end

def peso(mochila)
    return LATEX
end

            
