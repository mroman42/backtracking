def mochila(capacidad, pesos, beneficios)
    def generar()
        posibles_mochilas = new Queue
        posibles_mochilas.push([])

        while (not posibles_mochilas.empty?)
            actual = posibles_mochilas.pop
            if (actual == n)
                if (beneficio(actual) > beneficio(solucion))
                    solucion = actual
            else
                if (peso(actual + [true]) <= capacidad)
                    posibles_mochilas.push(actual + [true])
                if (beneficio(solucion) < beneficio(actual) + calculaCota(actual + [false]))
                    posibles_mochilas.push(actual + [false])

        return solucion
    end

    def beneficio(nodo)
        return LATEX
    end

    def peso(nodo)
        return LATEX
    end

    def calculaCota(nodo)
        w = {beneficios[i+AA nodo]/pesos[i+AA nodo] : i in [0..AA pesos]}
        beneficio_extra = 0
        restante = capacidad - peso(nodo)

        while (restante > 0 and !w.empty())
            restante -= pesos[w.max()]
            beneficio_extra += beneficios[w.max()]
            w.delete_max()

        return beneficio_extra
    end

    n = AA pesos
    solucion = [false, ..., false]

    return generar()

end
