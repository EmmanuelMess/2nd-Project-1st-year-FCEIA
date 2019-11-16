#include "structs.h"
#include <malloc.h>
#include <zconf.h>
#include "constantes.h"

struct String* crearString(int largo) {
	struct String* string = malloc(sizeof(struct String));
	string->array = calloc(largo, sizeof(char));
	string->ultimoIndice = 0;

	return string;
}

void destruirString(struct String* string) {
	string->array = reallocarray(string->array, 0, sizeof(char*));
	free(string);
}

void copiarAString(struct String* string, char *fuente) {
	for(int i = 0; fuente[i] != '\0'; i++) {
		string->array[string->ultimoIndice++] = fuente[i];
	}
}

void copiarCharAString(struct String* string, char c) {
	string->array[string->ultimoIndice++] = c;
}

void reasignarAMedida(struct String* string) {
	string->array = reallocarray(string->array, string->ultimoIndice, sizeof(char));
}



/**
 * Mayormente arbitrario, cambiar si hay demasidas reasignaciones de memoria.
 *
 * Es un tamaño de pagina de memoria en Linux para que se pida lo menos seguido posible pero sin pedir demasiado.
 */
unsigned long largoDeAsignacionArrayStrings() {
	return sysconf(_SC_PAGESIZE) / sizeof(struct Persona*);
}


struct ArrayStrings* crearArrayStrings() {
	struct ArrayStrings* arrayStrings = malloc(sizeof(struct ArrayStrings));
	arrayStrings->largoAsignado = largoDeAsignacionArrayStrings();
	arrayStrings->array = reallocarray(NULL, arrayStrings->largoAsignado, sizeof(struct String*));
	arrayStrings->ultimoIndice = 0;

	return arrayStrings;
}

void destruirArrayStrings(struct ArrayStrings* arrayStrings) {
	for(int i = 0; i < arrayStrings->ultimoIndice; i++) {
		destruirString(arrayStrings->array[i]);
	}

	arrayStrings->array = reallocarray(arrayStrings->array, 0, sizeof(struct String*));
	free(arrayStrings);
}

void agrandarArrayStrings(struct ArrayStrings* arrayStrings) {
	arrayStrings->largoAsignado += largoDeAsignacionArrayStrings();
	arrayStrings->array = reallocarray(arrayStrings->array, arrayStrings->largoAsignado, sizeof(struct String*));
}



struct Persona* crearPersona(char *nombre, char *apellido, char *localidad,
                             char *edad, char genero, char gusto) {

	struct Persona* persona = malloc(sizeof(struct Persona));

	persona->personaImprimible = crearString(LARGO_DE_ASIGNACION_PALABRAS);

	copiarAString(persona->personaImprimible, nombre);
	copiarCharAString(persona->personaImprimible, ',');
	copiarAString(persona->personaImprimible, apellido);
	copiarCharAString(persona->personaImprimible, ',');
	copiarAString(persona->personaImprimible, localidad);
	copiarCharAString(persona->personaImprimible, ',');
	copiarAString(persona->personaImprimible, edad);
	copiarCharAString(persona->personaImprimible, ',');
	copiarCharAString(persona->personaImprimible, genero);
	copiarCharAString(persona->personaImprimible, ',');
	copiarCharAString(persona->personaImprimible, gusto);

	persona->personaImprimible->ultimoIndice++;//para el \0

	reasignarAMedida(persona->personaImprimible);

	return persona;
}

void destruirPersona(struct Persona* persona) {
	destruirString(persona->personaImprimible);
	free(persona);
}



/**
 * Mayormente arbitrario, cambiar si hay demasidas reasignaciones de memoria.
 *
 * Es un tamaño de pagina de memoria en Linux para que se pida lo menos seguido posible pero sin pedir demasiado.
 */
unsigned long largoDeAsignacionArrayPersonas() {
	return sysconf(_SC_PAGESIZE) / sizeof(struct Persona*);
}

struct ArrayPersonas* crearArrayPersonas() {
	struct ArrayPersonas* arrayStrings = malloc(sizeof(struct ArrayPersonas));
	arrayStrings->largoAsignado = largoDeAsignacionArrayPersonas();
	arrayStrings->array = reallocarray(NULL, arrayStrings->largoAsignado, sizeof(struct Persona*));
	arrayStrings->ultimoIndice = 0;

	return arrayStrings;
}

void destruirArrayPersonas(struct ArrayPersonas* arrayPersonas) {
	for (int i = 0; i < arrayPersonas->ultimoIndice; ++i) {
		destruirPersona(arrayPersonas->array[i]);
	}
	arrayPersonas->array = reallocarray(arrayPersonas->array, 0, sizeof(char*));
	free(arrayPersonas);
}

void agrandarArrayPersonas(struct ArrayPersonas* arrayStrings) {
	arrayStrings->largoAsignado += largoDeAsignacionArrayPersonas();
	arrayStrings->array = reallocarray(arrayStrings->array, arrayStrings->largoAsignado, sizeof(char*));
}
