def planifica(ncores, tareas)
    def resolver()
        posibles = new PriorityQueue
        solución = []
        tiempo = LATEXinfty

        posibles.push({
            historial: []
            ejecutando: []
            restantes: tareas
        })

        while (not posibles.empty?)
            actual = posibles.pop

            if (LATEXactual.historial == LATEXtareas && actual.ejecutando.empty?)
                solucion = actual if t_ejecucion(actual) < t_ejecucion(solucion)
            else
                libre = get_core(actual.ejecutando)

                if (libre > -1)
                    for (nueva in actual.restantes)
                        if (not tiene_dependencias(nueva, actual))
                            copia = actual
                            copia.ejecutando[libre] = nueva
                            copia.restantes.delete(j)
                            copia.historial.push({
                                tarea: nueva
                                t_inicio: t_ejecucion(copia)
                                core: libre
                            })

                            posibles.push(copia)

                if (not actual.ejecutando.empty?)
                    min_restante = min{tarea.tiempo, tarea LATEXin actual.ejecutando}

                    for (tarea in actual.restantes)
                        tarea.tiempo -= min_restante

                    posibles.push(actual) if t_ejecucion(actual) < t_ejecucion(solucion)

        return solucion
    end

    def t_ejecucion(planificacion)
        return max{planificacion[i].t_inicio + planificacion[i].tarea.tiempo,
            i LATEXin {1, ... LATEXplanificacion}}
    end

    def get_core(multiprocesador)
        return min{i < ncores, multiprocesador[i].empty?}
    end

    def tiene_dependencias(tarea, plan)
        return LATEXexists i : tarea LATEXin plan.ejecutando[i].dependencias or
            LATEXexists i : tarea LATEXin plan.restantes[i].dependencias
    end

    return resolver()
end
