#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {

	/* Declaro las variables a utilizar*/
	pila_t* pila_1 = pila_crear();

	/* Inicio de pruebas */
	printf("INICIO DE PRUEBAS DE CREACION Y DESTRUCCION DE LA PILA\n");

	print_test("crear pila", pila_1 != NULL);
    print_test("la pila creada está vacía", pila_esta_vacia(pila_1));

    pila_destruir(pila_1);
    print_test("la pila fue destruida",true);

    printf("INICIO DE PRUEBAS DE APILADO Y DESAPILADO DE ELEMENTOS\n");

    pila_t* pila_2 = pila_crear();

    /* Pruebas en pila vacía */
    print_test("desapilar la pila vacía devuelve NULL", pila_desapilar(pila_2) == NULL);
    print_test("ver el tope de una pila vacía devuelve NULL", pila_ver_tope(pila_2) == NULL);

    int elem_1 = 5;
    int* punt_1 = &elem_1;
    int elem_2 = 10;
    int* punt_2 = &elem_2;
    int elem_3 = 20;
    int* punt_3 = &elem_3;

    /* Pruebas de apilado */

    print_test("apilar el elemento 5 devuelve true",pila_apilar(pila_2,punt_1));
    int* tope = pila_ver_tope(pila_2);
    print_test("el tope de la pila es 5",*tope == 5);
    print_test("apilar el elemento 10 devuelve true",pila_apilar(pila_2,punt_2));
    tope = pila_ver_tope(pila_2);
    print_test("el tope de la pila es 10",*tope == 10);
    print_test("apilar el elemento 20 devuelve true",pila_apilar(pila_2,punt_3));
    tope = pila_ver_tope(pila_2);
    print_test("el tope de la pila es 20",*tope == 20);

    print_test("la pila no está vacía", !pila_esta_vacia(pila_2));

    /* Pruebas de desapilado */

    int* desapilado = pila_desapilar(pila_2);
    print_test("el primer elemento desapilado es 20", *desapilado == 20);
    desapilado = pila_desapilar(pila_2);
    print_test("el segundo elemento desapilado es 10", *desapilado == 10);
    desapilado = pila_desapilar(pila_2);
    print_test("el tercer elemento desapilado es 5", *desapilado == 5);
    print_test("la pila apilada y desapilada está vacía", pila_esta_vacia(pila_2));
    
    /* Pruebas sobre pila apilada y desapilada hasta estar vacía */
    print_test("desapilar una pila que fue desapilada hasta estar vacía devuelve NULL", pila_desapilar(pila_2) == NULL);
    print_test("ver el tope de una pila que fue desapilada hasta estar vacía devuelve NULL", pila_ver_tope(pila_2) == NULL);
    print_test("la pila está vacía", pila_esta_vacia(pila_2));

     /* Destruyo la pila */
    pila_destruir(pila_2);

    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    pila_t* pila_3 = pila_crear();
    
    /* Prueba de apilado masivo */
    bool prueba_apilado_masivo(pila_t* pila,size_t tam_vector);
    bool apilado_masivo = prueba_apilado_masivo(pila_3,100);
    print_test("100 elementos se apilan correctamente y el tope es el indicado", apilado_masivo);
    print_test("la memoria se redimensiona correctamente para permitir apilar más elementos", apilado_masivo);
    apilado_masivo = prueba_apilado_masivo(pila_3,10000);
    print_test("10000 elementos se apilan correctamente y el tope es el indicado", apilado_masivo);
    print_test("la memoria se redimensiona correctamente para permitir apilar más elementos", apilado_masivo);
    apilado_masivo = prueba_apilado_masivo(pila_3,1000000);
    print_test("1000000 elementos se apilan correctamente y el tope es el indicado", apilado_masivo);
    print_test("la memoria se redimensiona correctamente para permitir apilar más elementos", apilado_masivo);


    /* Prueba de desapilado masivo */
    size_t tam_prueba = 1001050; /* Desapilo elemento de más para verificar que devuelve NULL si la pila está vacía*/
    bool prueba_desapilado_masivo(pila_t* pila,size_t tam_vector);
    print_test("cada elemento se desapila correctamente", prueba_desapilado_masivo(pila_3,tam_prueba));
    print_test("si la pila ya está vacía se devuelve NULL", prueba_desapilado_masivo(pila_3,tam_prueba));

    /* Destruyo la pila */
    pila_destruir(pila_3);

    printf("PRUEBA CON EL ELEMENTO NULL\n");

    /* Creo la pila de prueba */
    pila_t* pila_4 = pila_crear();

    int* elem_null = NULL;
    print_test("el elemento NULL es apilado correctamente",pila_apilar(pila_4,elem_null));
    pila_desapilar(pila_4);
    elem_null = 0;
    print_test("el elemento 0 es apilado correctamente",pila_apilar(pila_4,elem_null));
    pila_desapilar(pila_4);
    pila_destruir(pila_4);
}


/* FUNCIONES AUXILIARES */

bool prueba_apilado_masivo(pila_t* pila,size_t tam_vector) {
	/* Crea un vector auxiliar de tamaño tam_vector que guarda elementos y los apila en una Pila.
	   Devuelve true si no encontró ningún error en el apilamiento, false en caso contrario. Destruye el vector al finalizar. */

	int* vector = malloc(tam_vector * sizeof(int));

    for ( int i = 0; i < tam_vector; i++ ) {
    	vector[i] = i;
    	int* puntero = &vector[i];
    	bool apilado_ok = pila_apilar(pila,puntero);
    	int* tope = pila_ver_tope(pila);

    	if ( !apilado_ok || *tope != vector[i] ) {
    		free(vector);
    		return false;
    	}
	}
	free(vector);
    return true;
}

bool prueba_desapilado_masivo(pila_t* pila,size_t cant_elem) {
	/* Desapila una Pila una cantidad cant_elem de veces.
	   Devuelve true si la Pila se desapila correctamente, false en caso contrario. Destruye el vector al finalizar. */

    for ( int i = 0; i < cant_elem; i++ ) {
    	pila_desapilar(pila);
    	int* tope = pila_ver_tope(pila);

    	if ((!pila_esta_vacia(pila) &&  tope == NULL) || (pila_esta_vacia(pila) && tope != NULL)) return false;
	
    }
    	return true;
}

