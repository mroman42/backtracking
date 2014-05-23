def planifica
    posibles_planificaciones = new Stack

    solucion.t_ejecucion = LATEXinfty

    #posibles_planificaciones.push(Planificacion(problema))  ???

    until posibles_planificaciones.empty?
        actual = posibles_planificaciones.pop

        # Si es una planificación de todos las tareas, comprobamos si es mejor que la que ya tenemos
        if (actual.historial.size() == problema.size() && empty(actual.procesador_actual))
            if (actual.t_ejecucion < solucion.t_ejecucion)
                solucion = actual
            end
        else
            core = gap(actual.procesador_actual)
            /*
             Si hay core libre, intentamos planificar algún proceso en dicho core
             */


            if (core)
                core--
                # Comprueba si tiene dependencia con...
                for j in [0..actual.restantes.size]
                    dependencia = false
                    # ·Los que están ejecutándose
                    for i in [0..num_cores]
                        if(!dependencia)
                            if (!actual.procesador_actual[i].empty())
                                dependencia = depende(actual.procesador_actual[i].index, actual.restantes[j].index)
                            end
                        end
                    end

                    # ·Los que aún no se han ejecutado
                    for k in [0..actual.restantes.size]
                        if(!dependencia)
                            if (k!=j)
                                if (!actual.restantes[j].empty())
                                    dependencia = depende(actual.restantes[k].index, actual.restantes[j].index)
                            end
                        end
                    end

                    # Si no hay dependencia, lo ejecutamos en el núcleo libre
                    if (!dependencia)
                        copia_actual = actual
                        copia_actual.procesador_actual[core] = actual.restantes[j]
                        #vector <Tarea>::iterator it = copia_actual.restantes.begin()
                        #advance (it,j)
                        #copia_actual.restantes.erase(it)
                        #copia_actual.historial.push_back(Asignacion(core, actual.restantes[j], copia_actual.t_ejecucion))
                        posibles_planificaciones.push(copia_actual)
                    end
                end
            end
            # Si el procesador no estaba vacío,...
            if (!empty(actual.procesador_actual))
                t_minimo = LATEXinfty
                for tarea in actual.procesador_actual
                    if (!tarea.empty())
                        if (tarea.ejecucion < t_minimo)
                            t_minimo = tarea.ejecucion
                        end
                    end
                end

                # Actualizamos tiempos de ejecución del procesador
                for tarea in actual.procesador_actual
                    tarea.ejecucion -= t_minimo

                    if (tarea.ejecucion < 0)
                        tarea.ejecucion = 0
                    end
                end

                actual.t_ejecucion += minimo

                posibles_planificaciones.push(actual)
            end
        end
    end
    return solucion
end
