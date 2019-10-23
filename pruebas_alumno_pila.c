#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#define GRAN_CANTIDAD 100000
#define CONST1 1
#define CONST2 7
#define CONST3 15
#define CONST4 17

/* ******************************************************************
*                   PRUEBAS UNITARIAS ALUMNO
* *****************************************************************/

void pruebas_pila_vacia(pila_t* pila){
    
    printf("\n**PRUEBAS CON PILA VACÍA**\n");
    pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    print_test("Crear pila", pila != NULL);
    print_test("Cantidad pila vacía = 0", pila_esta_vacia(pila));
    print_test("Desapilar pila vacia", pila_desapilar(pila) == NULL);
    print_test("Ver tope pila vacía", pila_ver_tope(pila) == NULL);

    int i = CONST1;
    print_test("Apilar pila vacía", pila_apilar(pila, &i));

    pila_destruir(pila);
    print_test("Destruir pila", true);
}

bool es_lifo(void** vector, int n, pila_t* pila); // definida al final

void pruebas_pila_algunos_elementos(){
    
    printf("\n**PRUEBAS CON ALGUNOS ELEMENTOS**\n");

    pila_t* pila = pila_crear();
    print_test("Crear pila", pila != NULL);

    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    printf("Apilar %d en pila:", i);
    print_test("", pila_apilar(pila, &i));
    printf("%d en tope:", i);
    print_test("", pila_ver_tope(pila) == &i);

    printf("Apilar %d en pila:", j);
    print_test("", pila_apilar(pila, &j));
    printf("%d en tope:", j);
    print_test("", pila_ver_tope(pila) == &j);

    printf("Apilar %d en pila:", k);
    print_test("", pila_apilar(pila, &k));
    printf("%d en tope:", k);
    print_test("", pila_ver_tope(pila) == &k);

    printf("Apilar %d en pila:", l);
    print_test("", pila_apilar(pila, &l));
    printf("%d en tope:", l);
    print_test("", pila_ver_tope(pila) == &l);

    void* vector[4] = {&i,&j,&k,&l};

    bool pila_lifo = es_lifo( vector, 4, pila);
    print_test("Pila LIFO: ", pila_lifo);
    printf("*La pila se encuentra vacía*\n");

    void* n = NULL;
    print_test("Apilar NULL en pila: ", pila_apilar(pila, n));
    print_test("NULL en tope: ", pila_ver_tope(pila) == n);
    print_test("Desapilar NULL", pila_desapilar(pila) == n);

    pila_destruir(pila);
    print_test("Destruir pila", true);
}

bool vaciar_pila(pila_t* pila);
pila_t* chequear_capacidad(pila_t* pila);

void pruebas_pila_gran_cantidad_elementos(){

    printf("\n**PRUEBAS CON GRANDES CANTIDADES DE ELEMENTOS**\n");

    pila_t* pila = pila_crear();
    print_test("Crear pila", pila != NULL);
    
    bool apilado = true;
    bool tope_correcto;

    void* vector[GRAN_CANTIDAD];

    // Guardo en cada posición de memoria un puntero que apunta a su respectiva posición de memoria
    for (int i = 0; i < GRAN_CANTIDAD && apilado; i++){ 

        vector[i] = &vector[i]; 
    }
    
    // Apilo las direcciones de las posiciones de memoria del vector en la pila
    for (int i = 0; i < GRAN_CANTIDAD && apilado; i++){
        
        apilado = pila_apilar(pila, &vector[i]);
        tope_correcto = (pila_ver_tope(pila) == &vector[i]);

        if (apilado != tope_correcto){
            break;
        }
    }
    
    printf("Apilado de %d elementos:",GRAN_CANTIDAD);
    print_test("",apilado);
    print_test("Topes correctos al apilar:",true);

    bool pila_lifo = es_lifo(vector, GRAN_CANTIDAD, pila);
    print_test("Pila LIFO: ", pila_lifo);
    printf("*La pila se encuentra vacía*\n");

    // Comprueba que una pila apilada y luego desapilada hasta vaciarse se comporte como pila vacía
    printf("\nSE COMPRUEBA QUE PILA APILADA Y LUEGO DESAPILADA SE COMPORTA COMO PILA VACÍA:");
    pruebas_pila_vacia(pila);
}

bool vaciar_pila(pila_t* pila){ //vacía la pila chequeando que el tope sea igual al elemento que se desapila posteriormente
    
    void* tope;
    void* desapilado;
    bool son_diferentes = false;

    while (!(pila_esta_vacia(pila)) && !(son_diferentes)){
        
        tope = pila_ver_tope(pila);
        desapilado = pila_desapilar(pila);
        son_diferentes = (tope != desapilado);
    }
    return !(son_diferentes);
}

bool es_lifo(void** vector, int n, pila_t* pila){ // verifica la invariante de pila dado un vector con n elementos

    n-=1;
    bool condicion_lifo = true;
    while (n >= 0 && condicion_lifo){
        void* elemento_correspondiente = vector[n];
        void* desapilado = pila_desapilar(pila);
        condicion_lifo = (elemento_correspondiente == desapilado);
        n--;
    }
    return condicion_lifo;
}

void pruebas_pila_alumno(){

    pila_t* pila = pila_crear();

    pruebas_pila_vacia(pila);
    pruebas_pila_algunos_elementos();
    pruebas_pila_gran_cantidad_elementos();
    return;
}
