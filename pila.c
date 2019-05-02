#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

size_t CAPACIDAD_ARREGLO_DE_PILA = 1000;

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t* pila_crear(void) {
	pila_t* pila = malloc(sizeof(pila_t));

	if (pila == NULL) return NULL;

	pila -> datos = malloc(CAPACIDAD_ARREGLO_DE_PILA * sizeof(void *));
	pila -> cantidad = 0;
	pila -> capacidad = CAPACIDAD_ARREGLO_DE_PILA;

	if ( pila -> capacidad > 0 && pila -> datos == NULL) {
		free(pila);
		return NULL;
	}

	return pila;
}

void pila_destruir(pila_t *pila) {
	while (!pila_esta_vacia(pila)) {
		free(pila_desapilar(pila));
	}
	free(pila -> datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
	if ( pila -> cantidad == 0 ) return true;

	return false;
}

void evaluar_agrandar_pila(pila_t *pila) {
	if ( pila -> cantidad == pila -> capacidad ) {
		size_t nueva_capacidad = pila -> capacidad * 2;
		pila -> datos = realloc(pila -> datos,nueva_capacidad * sizeof(void *));
		pila -> capacidad = nueva_capacidad;
	}
}


bool pila_apilar(pila_t *pila, void* valor) {
	evaluar_agrandar_pila(pila);
	bool errores_encontrados = true;
	pila -> datos[pila -> cantidad] = valor;
	pila -> cantidad += 1;
	errores_encontrados = false;
	return !errores_encontrados;	
}

void* pila_ver_tope(const pila_t *pila) {
	if ( pila_esta_vacia(pila) ) return NULL;

	size_t posicion = pila -> cantidad -1;
	return pila -> datos[posicion];
}

void evaluar_achicar_pila(pila_t *pila) {
	if ( pila -> cantidad == pila -> capacidad / 4 ) {
		size_t nueva_capacidad = pila -> capacidad / 2;
		if ( nueva_capacidad > CAPACIDAD_ARREGLO_DE_PILA ) {
			pila -> datos = realloc(pila -> datos,nueva_capacidad * sizeof(void *));
			pila -> capacidad = nueva_capacidad;
		}
	}
}


void* pila_desapilar(pila_t *pila) {
	if ( pila_esta_vacia(pila) ) return NULL;

	size_t ult_posicion = pila -> cantidad -1;
	void* valor_a_devolver = pila -> datos[ult_posicion];
	pila -> datos[ult_posicion] = NULL;
	pila -> cantidad -= 1;
	evaluar_achicar_pila(pila);
	return valor_a_devolver;
}


