#ifndef TRABAJO2GUIMPEL_STRUCTS_H
#define TRABAJO2GUIMPEL_STRUCTS_H

/**
 * @param array: Es un array, se garantiza la inicialización a ceros
 *   y que este puntero hace referencia a un bloque asignado de al menos el largo pasado a crearString(struct String*).
 * @param ultimoIndice: deberá ser la posicion siguiente al ultimo caracter de la palabra.
 *
 * Se garantiza que todos los metodos que operan con struct String adelantan ultimoIndice correctamente
 *
 *  Ejemplo: array = "AAAA\0", ultimoIndice = 6
 */
struct String {
	char* array;
	unsigned int ultimoIndice;
};

/**
 *
 * @param largo largo minimo que tendra el bloque de memoria al que hace referencia String->array.
 * @return Un puntero a un nuevo struct String.
 */
struct String* crearString(int largo);

/**
 * Libera la memoria del struct String al que hace referencia el puntero string.
 * @param string Puntero al struct String a liberar.
 */
void destruirString(struct String* string);

/**
 * Copia los caracteres a la posicion indicada por string->ultimoIndice.
 *
 * @param string puntero a un struct String a donde copiar fuente
 * @param fuente puntero a un array de chars terminados por null.
 *
 * @warning Este metodo no hace chequeos de largo, ni de la terminación en null de fuente.
 */
void copiarAString(struct String* string, char *fuente);

/**
 * Copia un unico char a string->ultimoIndice.
 * @param string puntero a un struct String a donde copiar c
 * @param c El caracter a copiar
 *
 * @warning Este metodo no hace chequeos de largo
 */
void copiarCharAString(struct String* string, char c);

/**
 * Reduce el largo del bloque de memoria asignado a string a string->ultimoIndice.
 */
void reasignarAMedida(struct String* string);



/**
 * Array de struct String que tiene una idea de su largo asignado y puede extenderse cuando se necesita mas memoria.
 * @param largoAsignado El largo del bloque de al que array hace referencia esta garantizado a ser al menos largoAsignado.
 * @param ultimoIndice: deberá ser la posicion siguiente al ultimo caracter de la palabra.
 */
struct ArrayStrings {
	struct String ** array;
	unsigned int largoAsignado;
	unsigned int ultimoIndice;
};

/**
 * Array de struct String que tiene una idea de su largo asignado y puede extenderse cuando se necesita mas memoria.
 *
 * El largo inicial y por el que se extiende es LARGO_DE_ASIGNACION_ARRAY_STRINGS bytes.
 */
struct ArrayStrings* crearArrayStrings();

/**
 * Libera la memoria del struct ArrayStrings al que hace referencia el puntero arrayStrings.
 * Libera la memoria de todos los struct String contenidos en su array.
 */
void destruirArrayStrings(struct ArrayStrings* arrayStrings);

/**
 * Agranda la memoria asignada a este array.
 */
void agrandarArrayStrings(struct ArrayStrings* arrayStrings);



/**
 * Contenedor de un struct String que sirve para manipular y formatear personas mas facilmente.
 * //TODO esto deberia ser un typedef Persona struct String*
 */
struct Persona {
	struct String *personaImprimible;
};

/**
 * Formatea correctamente todos los datos pasados para que la salida sea parseable por el Trabajo Practico 1:
 *
 *   <nombre>,<apellido>,<localidad>,<edad>,<genero>,<gusto>
 *
 * Luego guarda el string resultante en un struct Persona que devuelve.
 *
 * @warning no hace chequeos de ningun tipo.
 */
struct Persona* crearPersona(char *nombre, char *apellido, char *localidad,
                             char *edad, char genero, char gusto);
/**
 * Destruye la struct Persona a la que hace referencia el puntero pasado
 * y el struct String al que hace referencia el puntero en este.
 */
void destruirPersona(struct Persona* persona);



/**
 * Array de largo variable para Personas.
 * @see ArrayStrings
 */
struct ArrayPersonas {
	struct Persona** array;
	unsigned long largoAsignado;
	unsigned long ultimoIndice;
};

/**
 * @see crearArrayStrings()
 */
struct ArrayPersonas* crearArrayPersonas();

/**
 * @see crearArrayStrings()
 */
void destruirArrayPersonas(struct ArrayPersonas* arrayPersonas);

/**
 * @see agrandarArrayStrings()
 */
void agrandarArrayPersonas(struct ArrayPersonas* arrayStrings);

#endif //TRABAJO2GUIMPEL_STRUCTS_H
