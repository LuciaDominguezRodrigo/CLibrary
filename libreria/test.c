
#include <stdio.h>

#include "libreria.h"
#include <stdlib.h>
#include <string.h>

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
        i = 0;
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