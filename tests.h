#ifndef TRABAJO2GUIMPEL_TESTS_H
#define TRABAJO2GUIMPEL_TESTS_H

/*
 * Este archivo funciona como interfaz de metodos que se pueden testear del main.c
 */

void test_main();

unsigned int  charAEntero(char caracter);
unsigned int stringAEnteroPositivo(const char* string);
void swap(struct Persona ** a, struct Persona ** b);

void leerLocalidades_testeable(struct ArrayStrings* localidades, FILE * archivoLocalidades);
void leerPersonasYParsear_testeable(struct ArrayPersonas* personas, struct ArrayStrings* localidades, FILE * archivoPersonas);

#endif //TRABAJO2GUIMPEL_TESTS_H
