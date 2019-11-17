#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "structs.h"
#include "tests.h"


/*
 * El formato de nombre de los tests es "test_<metodoTesteado>[_especificaciones]()"
 */

void test_charAEntero() {
	assert(charAEntero('0') == 0);
	assert(charAEntero('9') == 9);
	//Hay mas tests en test_stringAEnteroPositivo()
}

void test_stringAEnteroPositivo() {
	assert(stringAEnteroPositivo("0123456789") == (int)(123456789));
}

void test_swap() {
	struct Persona* p1 = crearPersona("a", "b", "c", "12", 'M', 'A');
	struct Persona* p2 = crearPersona("j", "k", "l", "50", 'F', 'N');

	swap(&p1, &p2);

	assert(strcmp(p2->personaImprimible->array, "a,b,c,12,M,A\0") == 0);
	assert(strcmp(p1->personaImprimible->array, "j,k,l,50,F,N\0") == 0);
}

void test_leerLocalidades_basico() {
	char buffer[] = "1,HOSPITAL                         \n"
	                "2,ZAPOTE                                      \n"
	                "3,SAN FRANCISCO DE DOS RIOS     ";
	FILE * archivoLocalidades = fmemopen(buffer, strlen(buffer), "r");
	struct ArrayStrings* localidades = crearArrayStrings();
	leerLocalidades_testeable(localidades, archivoLocalidades);
	fclose(archivoLocalidades);

	assert(localidades->ultimoIndice == 3);

	assert(strcmp(localidades->array[0]->array, "HOSPITAL\0") == 0);
	assert(strcmp(localidades->array[1]->array, "ZAPOTE\0") == 0);
	assert(strcmp(localidades->array[2]->array, "SAN FRANCISCO DE DOS RIOS\0") == 0);
}

void test_leerLocalidades_retornoDeCarro() {
	char buffer[] = "1,HOSPITAL                         \r\n"
	                "2,ZAPOTE                                      \r\n"
	                "3,SAN FRANCISCO DE DOS RIOS     ";
	FILE * archivoLocalidades = fmemopen(buffer, strlen(buffer), "r");
	struct ArrayStrings* localidades = crearArrayStrings();
	leerLocalidades_testeable(localidades, archivoLocalidades);
	fclose(archivoLocalidades);

	assert(localidades->ultimoIndice == 3);

	assert(strcmp(localidades->array[0]->array, "HOSPITAL\0") == 0);
	assert(strcmp(localidades->array[1]->array, "ZAPOTE\0") == 0);
	assert(strcmp(localidades->array[2]->array, "SAN FRANCISCO DE DOS RIOS\0") == 0);
}

void test_leerLocalidades_caracteresNoASCII() {
	char buffer[] = "1,L'HOPITÁL                         \n"
	                "2,ZAPOTE                                      \n"
	                "3,ÑU     ";
	FILE * archivoLocalidades = fmemopen(buffer, strlen(buffer), "r");
	struct ArrayStrings* localidades = crearArrayStrings();
	leerLocalidades_testeable(localidades, archivoLocalidades);
	fclose(archivoLocalidades);

	assert(localidades->ultimoIndice == 3);

	assert(strcmp(localidades->array[0]->array, "L'HOPITÁL\0") == 0);
	assert(strcmp(localidades->array[1]->array, "ZAPOTE\0") == 0);
	assert(strcmp(localidades->array[2]->array, "ÑU\0") == 0);
}

void test_leerPersonasYParsear() {
	char bufferLocalidades[] = "1,CHOMES                         \n"
	                "2,CONCEPCION                                      \n"
	                "3,C.P. CRISTO REY     ";
	FILE * archivoLocalidades = fmemopen(bufferLocalidades, strlen(bufferLocalidades), "r");
	struct ArrayStrings* localidades = crearArrayStrings();
	leerLocalidades_testeable(localidades, archivoLocalidades);
	fclose(archivoLocalidades);

	char bufferPersonas[] = "JOSE,DELGADO,1,56,1,3\n"
						 "CARMEN,CORRALES,2,72,2,2\n"
	                        "RAFAEL,AGUERO,3,75,1,4";
	FILE * archivoPersonas = fmemopen(bufferPersonas, strlen(bufferPersonas), "r");
	struct ArrayPersonas* personas = crearArrayPersonas();
	leerPersonasYParsear_testeable(personas, localidades, archivoPersonas);
	fclose(archivoLocalidades);

	assert(personas->ultimoIndice == 3);

	assert(strcmp(personas->array[0]->personaImprimible->array, "JOSE,DELGADO,CHOMES,56,M,A\0") == 0);
	assert(strcmp(personas->array[1]->personaImprimible->array, "CARMEN,CORRALES,CONCEPCION,72,F,M\0") == 0);
	assert(strcmp(personas->array[2]->personaImprimible->array, "RAFAEL,AGUERO,C.P. CRISTO REY,75,M,N\0") == 0);
}

void test_main() {
	test_charAEntero();

	test_stringAEnteroPositivo();

	test_swap();

	test_leerLocalidades_basico();
	test_leerLocalidades_retornoDeCarro();
	test_leerLocalidades_caracteresNoASCII();

	test_leerPersonasYParsear();
}