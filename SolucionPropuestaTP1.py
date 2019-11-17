#Pareja = (String, String, Int, String, String, Int, String)
#Persona = (String, String, String, Int, String, String)

#String -> ([Persona],[Persona], Dict((Localidad, CategoriaEdad),[Persona]))
#Toma un string que nos referencia al archivo de entrada y, en la medida que va leyendo
#separa lxs menores, lxs desinteresadxs y, lxs restantes se agregan en un Diccionario; cuya clave es Localidad y Categoria de edad.
def procesaEntradaDatos(archivo):
    menores = []
    desinteresadxs = []
    personasParaMatchear = {}
    file = open(archivo, "tr", encoding = "latin1")
    for personaString in file:
        persona = personaString.rstrip("\n").split(', ')
        persona[3] = int(persona[3])
        if persona[3]<= 10:
            menores += [persona]
        elif persona[5] == 'N':
            desinteresadxs += [persona]
        else:
            agregar(personasParaMatchear, persona)
    file.close()
    return (menores, desinteresadxs, personasParaMatchear)

#Dict((Localidad, CategoriaEdad),[Persona])),Persona->Dict((Localidad, CategoriaEdad),[Persona]))
#Agrega una persona al Diccionario teniendo como clave Localidad y Categoría de edad.
def agregar(personasParaMatchear, persona):
    if persona[3] <= 14:
        categoria = 0
    elif persona[3] <= 17:
        categoria = 1
    else:
        categoria = 2
    localidad = persona[2]
    if (localidad,categoria) in personasParaMatchear.keys():
        personasParaMatchear[(localidad,categoria)].append(persona)
    else:
        personasParaMatchear[(localidad,categoria)] = [persona]

#[Personas]->([Parejas],[Personas])
#Dada una lista de personas, devuelve una tupla integrada por la lista de Parejas 
#obtenida y la lista de personas que quedaron sin unir.
def generaParejas(personasParaMatchear):
    parejas = []
    solterxs = []
    claves = personasParaMatchear.keys()
    generos = ['M', 'F']
    generoInteres = ['M', 'F', 'A']
    for clave in claves:
        listaGeneroInteres = separaPorGeneroEInteres(personasParaMatchear[clave])
        for g in generos:
            (parejasObtenidas, solterx)=matchingUno(listaGeneroInteres[g+g])
            parejas += parejasObtenidas
            if solterx != [] and listaGeneroInteres[g+'A'] != []:
                (parejasObtenidas, solterx, listaGeneroInteres[g+'A']) = matchingDos(solterx, listaGeneroInteres[g+'A'])
                parejas += parejasObtenidas
            else:
                solterxs += solterx

        for mg in ['F', 'A']:
            for fg in ['M', 'A']:
                (parejasObtenidas, listaGeneroInteres['M' + mg], listaGeneroInteres['F' + fg]) = matchingDos(
                    listaGeneroInteres['M' + mg], listaGeneroInteres['F' + fg])
                parejas += parejasObtenidas
            
        for g in generos:
            (parejasObtenidas,solterx)= matchingUno(listaGeneroInteres[g+'A'])
            parejas += parejasObtenidas
            solterxs += solterx

        solterxs += listaGeneroInteres['MF']
        solterxs += listaGeneroInteres['FM']
    return (parejas, solterxs)

#[Persona]->([Pareja],[Persona])
#Asigna parejas dentro de una lista. Si la lista que tomamos como argumento tiene una cantidad par,
#no quedarán personas sin asignar, en caso contrario, quedará una única persona.
def matchingUno(listaUno):
    if listaUno == []:
        return ([], [])
    if len(listaUno) == 1:
        return ([], listaUno)
    parejas = []
    solxs = []
    longitud = len(listaUno)
    for i in range(0, int(longitud / 2)):
        parejas += [armaPareja(listaUno[i], listaUno[longitud-1-i])]
    if longitud % 2!= 0:
        solxs = [listaUno[int(longitud/2)+1]]
    return (parejas, solxs)

#[Persona],[Persona] ->([Pareja],[Persona],[Persona])
#Asigna parejas dentro entre dos listas.
#La lista recibida con menor cantidad de elementos, se retornará vacía y, de la otra, se retornan los elementos restantes.
def matchingDos(listaUno, listaDos):
    if listaUno == [] or listaDos == []:
        return ([],listaUno, listaDos)
    parejas = []
    longitud1 = len(listaUno)
    longitud2 = len(listaDos)
    if longitud1 > longitud2:
        minima = longitud2
    else:
        minima = longitud1
    for i in range(0, minima):
        parejas += [armaPareja(listaUno[i],listaDos[i])]
    return (parejas, listaUno[minima:], listaDos[minima:])

#Persona, Persona -> Pareja
#Arma una pareja con dos personas
def armaPareja(persona1, persona2):
    return (persona1[0], persona1[1], persona1[3], persona2[0], persona2[1], persona2[3], persona1[2])

#[Personas]->Dict((Genero+GeneroInteres,[Personas]))
#Dada una lista de personas las separa en un diccionario usando como clave la combinación
#de genero y género de interés.
def separaPorGeneroEInteres(listaDePersonas):
    listaDePersonasGeneroInteres = {'FA':[], 'MA':[], 'FF': [], 'MM':[], 'FM' : [], 'MF' : []}
    for persona in listaDePersonas:
        generoPropio = persona[4]
        generoDeInteres = persona[5]
        listaDePersonasGeneroInteres[generoPropio+generoDeInteres].append(persona)
    return listaDePersonasGeneroInteres

#[Parejas],String -> None
#Escribe las parejas en un archivo, cuyo nombre recibimos como argumento
def escribeParejas(parejas, salidaParejas):
    file = open(salidaParejas, "w", encoding = "latin1")
    for pareja in parejas:
        file.write(parejaToString(pareja)+ "\n")
    file.close()

#[Personas],[Personas],[Personas],String -> None
#Escribe menores, desinteresadxs y solterxs en un archivo, cuyo nombre recibimos como argumento
def escribeSolxs(menores, desinteresadxs, solterxs, salidaSolxs):
    file = open(salidaSolxs, "w", encoding = "latin1")
    file.write("Menores\n")
    for menor in menores:
        file.write(personaToString(menor)+ "\n")
    file.write("\nDesinteresadxs\n")
    for desinteresadx in desinteresadxs:
        file.write(personaToString(desinteresadx)+ "\n")
    file.write("\nSolterxs\n")
    for solterx in solterxs:
        file.write(personaToString(solterx)+ "\n")
    file.close()

#Pareja -> String
#Nos retorna un String que representa una pareja.
def parejaToString(pareja):
    return pareja[0] + ", " + pareja[1] + ", " + str(pareja[2]) + " - " + pareja[3] + ", " + pareja[4] + ", " + str(pareja[5]) + " - " + pareja[6]

#Persona -> String
#Nos retorna un String que representa una persona.
def personaToString(persona):
    return persona[0] + ", " + persona[1] + ", " + persona[2] + ", " + str(persona[3]) + ", " + persona[4] + ", " + persona[5] 
    
def main(entradaPersonas = "salida.txt", salidaParejas = "salidaParejas.txt", salidaSolxs="salidaSolxs.txt"):
    (menores, desinteresadxs, personasParaMatchear) = procesaEntradaDatos(entradaPersonas)
    (parejas, solterxs)=generaParejas(personasParaMatchear)
    escribeParejas(parejas, salidaParejas)
    escribeSolxs(menores, desinteresadxs, solterxs, salidaSolxs)

main()
