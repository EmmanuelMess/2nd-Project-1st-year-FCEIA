#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "constantes.h"
#include "tests.h"

#define DEBUG 0

/* PARTE 1 */

const char GENEROS[2] = "MF";
const char GUSTOS[4] = "FMAN";

/*PARTE 2*/

/*
 * Convierte un unico digito a un entero de largo 1.
 */
unsigned int charAEntero(char digito) {
	return digito-'0';
}

/**
 * Convierte un numero natural no negativo representado por un char* a un entero.
 * @param string char* terminado en NULL.
 * @return un entero no negativo.
 */
unsigned int stringAEnteroPositivo(const char* string) {
	unsigned int resultado = 0;
	for(int i = 0; string[i] != '\0'; i++) {
		resultado += charAEntero(string[i]);
		if(string[i+1] != '\0') resultado *= 10;
	}
	return resultado;
}

/**
 * Los el puntero al que hacer referencia a pasa a estar en b y viceversa.
 */
void swap(struct Persona ** a, struct Persona ** b){
	void *c;
	c = *a;
	*a = *b;
	*b = c;
}

/**
 * RAND_MAX solo esta garantizado a ser como minimo 32767 (http://www.cplusplus.com/reference/cstdlib/RAND_MAX/)
 * Esta funcion extiende el rango haciendo 2 llamadas
 * y uniendolas de forma que la uniformidad del rango no se vea muy afectada.
 */
unsigned long randExtendido() {
	unsigned long x = rand();
	x <<= 15;//15 es el largo en bits de el minimo RAND_MAX
	x ^= rand();
	return x;
}


/*PARTE 3*/

void leerLocalidades(struct ArrayStrings* localidades) {
	FILE* archivoLocalidades = fopen("codigoLocalidades.txt", "r");

	{
		struct String *nombreLocalidad = crearString(8);
		strcpy(nombreLocalidad->array, "NINGUNA\0");
		nombreLocalidad->ultimoIndice = 9;

		localidades->array[localidades->ultimoIndice++] = nombreLocalidad;
	}

	while(!feof(archivoLocalidades)) {
		if(localidades->ultimoIndice == localidades->largoAsignado - 1) {
			agrandarArrayStrings(localidades);
		}

		struct String *nombreLocalidad = crearString(LARGO_DE_ASIGNACION_PALABRAS);
		fscanf(archivoLocalidades, "%*[1234567890,]%500[^\r\n]", nombreLocalidad->array);

		while (nombreLocalidad->array[nombreLocalidad->ultimoIndice+1] != '\0' &&
		       !(nombreLocalidad->array[nombreLocalidad->ultimoIndice] == ' ' && nombreLocalidad->array[nombreLocalidad->ultimoIndice+1] == ' ')) {
			nombreLocalidad->ultimoIndice++;
		}
		nombreLocalidad->array[nombreLocalidad->ultimoIndice++] = '\0';

		reasignarAMedida(nombreLocalidad);

		localidades->array[localidades->ultimoIndice] = nombreLocalidad;

		localidades->ultimoIndice++;

		if(fgetc(archivoLocalidades) == '\r'){
			fgetc(archivoLocalidades);//Come finales de linea y adelanta hasta el EOF si llegamos al final
		}
	}

	fclose(archivoLocalidades);

	for(unsigned int i = 0; i < localidades->ultimoIndice; i++){
		if(DEBUG) printf("%d: %s\n", i+1, localidades->array[i]->array);
	}
}

void leerPersonasYParsear(struct ArrayPersonas* personas, struct ArrayStrings* localidades) {
	FILE* archivoPersonas = fopen("personas.txt", "r");

	while(!feof(archivoPersonas)) {
		if (personas->ultimoIndice == personas->largoAsignado - 1) {
			agrandarArrayPersonas(personas);
		}

		char nombre[LARGO_DE_ASIGNACION_PALABRAS] = {0};
		fscanf(archivoPersonas, "%500[^,]%*[,]", nombre);

		char apellido[LARGO_DE_ASIGNACION_PALABRAS] = {0};
		fscanf(archivoPersonas, "%500[^,]%*[,]", apellido);

		char codigoLocalidadStr[50] = {0};
		fscanf(archivoPersonas, "%50[^,]%*[,]", codigoLocalidadStr);

		char edad[5] = {0};
		fscanf(archivoPersonas, "%5[^,]%*[,]", edad);

		char genero;
		fscanf(archivoPersonas, "%c%*[,]", &genero);

		char gusto;
		fscanf(archivoPersonas, "%c", &gusto);


		int codigoLocalidad = stringAEnteroPositivo(codigoLocalidadStr);
		struct String *localidad = localidades->array[codigoLocalidad];


		personas->array[personas->ultimoIndice++] = crearPersona(
			nombre,
			apellido,
			localidad->array,
			edad,
			GENEROS[charAEntero(genero)-1],
			GUSTOS[charAEntero(gusto)-1]
		);

		if(fgetc(archivoPersonas) == '\r'){
			fgetc(archivoPersonas);//Come finales de linea y adelanta hasta el EOF si llegamos al final
		}
	}

	fclose(archivoPersonas);

	for(unsigned long i = 0; i < personas->ultimoIndice; i++){
		if(DEBUG) printf("%ld: %s\n", i+1, personas->array[i]->personaImprimible->array);
	}
}


/**
 * NOMBRE Trabajo2Guimpel
 * SINOPSIS
 *     Trabajo2Guimpel
 *     Trabajo2Guimpel -p <numeroDePersonas>
 *     Trabajo2Guimpel -t
 * 	DESCRIPCION
 * 		Trabajo2Guimpel: permite ingresar por teclado la cantidad de personas a imprimir
 * 		Trabajo2Guimpel -p <numeroDePersonas>: lo mismo que el anterior pero ahorra el tiempo del usuario
 * 		Trabajo2Guimpel -t: (solo desarrollo) testing
 */
int main(int argc, char * argv []) {
	if(argc == 2) {//modo testing
		test_main();
		return 0;
	}

	struct ArrayStrings* localidades = crearArrayStrings();//TODO pedir RAM directamente proporcional con el tamaño del archivo
	leerLocalidades(localidades);

	struct ArrayPersonas* personas = crearArrayPersonas();
	leerPersonasYParsear(personas, localidades);

	long genteAImprimir;

	if(argc == 1) {
		printf("%s", "Cantidad de personas: ");
		scanf("%ld", &genteAImprimir);
	} else if(argc == 3) {// permite hacer "Trabajo2Guimpel -p 3" para no tener que lidiar con la interfaz por consola
		genteAImprimir = stringAEnteroPositivo(argv[2]);
	}

	srand(time(NULL));

	FILE * archivoSalida = fopen("salida.txt", "w");

	for(long i = 0; i < genteAImprimir; i++) {
		unsigned long random = personas->ultimoIndice < RAND_MAX? rand():randExtendido();
		unsigned long indiceElegido = random % (personas->ultimoIndice - i);

		fprintf(archivoSalida,"%s\n", personas->array[indiceElegido]->personaImprimible->array);
		if(DEBUG) printf("%s\n", personas->array[indiceElegido]->personaImprimible->array);

		swap(&personas->array[indiceElegido], &personas->array[(personas->ultimoIndice - i - 1)]);
	}

	destruirArrayStrings(localidades);
	destruirArrayPersonas(personas);

	return 0;
}
