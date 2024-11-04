
#include <stdio.h>

#include "libreria.h"
#include <stdlib.h>
#include <string.h>


/**
 * Programa principal que ejecuta las funciones head, tail o longlines según los argumentos proporcionados.
 *
 * Este programa recibe hasta dos argumentos adicionales. El primero especifica la operación:
 * - `-head`: Imprime las primeras N líneas de la entrada.
 * - `-tail`: Imprime las últimas N líneas de la entrada.
 * - `-long`: Imprime las N líneas más largas de la entrada.
 *
 * El segundo argumento (opcional) especifica el número de líneas N a procesar. Si no se proporciona, el valor
 * predeterminado es 10. Si se proporciona un valor no numérico para N, el programa devuelve un error.
 *
 * @param argc Número de argumentos pasados al programa (incluido el nombre del ejecutable).
 * @param argv Arreglo de cadenas de caracteres con los argumentos.
 *             argv[1] debe contener `-head`, `-tail`, o `-long`.
 *             argv[2] (opcional) puede contener el número N de líneas a procesar.
 *
 * @return Código de salida: 0 si es exitoso, 1 si hay un error en el formato del segundo argumento,
 *         y 2 si el primer argumento es incorrecto.
 */

int main(int argc, char *argv[]) {
    int i;

    if(argc > 3) {
        printf("El numero de parametros introducido no es correcto\n");
    }
    else if(argc == 3) {
        i = atoi(argv[2]);
        if(i == 0 && strcmp(argv[2], "0") != 0) {
            printf("El formato del segundo argumento introducido no es correcto\n");
            return 1;
        }
    }
    else {
        i = 10;
    }

    if(strcmp(argv[1], "-head") == 0) {
        return head(i);
    }

    else if (strcmp(argv[1], "-tail") == 0) {
        return tail(i);
    }

    else if (strcmp(argv[1], "-long") == 0) {
        return longlines(i);
    }

    else {
        printf("Error. La extension introducida no es correcta\n");
        return 2;
    }
}