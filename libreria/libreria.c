#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* content;
    size_t size; //Declarada como int pero pasada a size_t para evitar casting
}Line;



int head(int N) {
    char buffer[1024];
    for(int i = 0; i < N; i++) {
        fgets(buffer, 1024, stdin);
        fputs(buffer, stdout);
    }
    return 0;
}

int tail(int N) {
    if (N <= 0) return 0;

    // Crear un búfer dinámico para almacenar punteros a las líneas
    char** lines_buffer = (char**)malloc(N * sizeof(char));
    if (!lines_buffer) {
        fputs("Error al asignar memoria para el búfer de líneas\n", stdout);
        return 1;
    }

    // Inicializar el búfer con espacio para cada línea
    for (int i = 0; i < N; i++) {
        lines_buffer[i] = (char*)malloc(1024 * sizeof(char));
        if (!lines_buffer[i]) {
            fputs("Error al asignar memoria para una línea\n", stdout);
            // Liberar memoria parcialmente asignada
            for (int j = 0; j < i; j++) {
                free(lines_buffer[j]);
            }
            free(lines_buffer);
            return 1;
        }
    }

    int line_count = 0;
    char* current_line;
    // Leer el stdin línea por línea, almacenando en un ciclo de N posiciones
    while (!feof(stdin)) {
        current_line = fgets(lines_buffer[line_count % N], 1024, stdin);
        if (current_line != NULL) line_count++;
    }

    // Imprimir las últimas N líneas en orden
    int start = line_count > N ? line_count % N : 0;
    int total_lines = line_count < N ? line_count : N;
    fputs("\n", stdout); //Se separa la respuesta de tail con un \n por legibilidad
    for (int i = 0; i < total_lines; i++) {
        fputs(lines_buffer[(start + i) % N], stdout);
    }

    // Liberar memoria asignada
    for (int i = 0; i < N; i++) {
        free(lines_buffer[i]);
    }
    free(lines_buffer);

    return 0;
}


int longlines(int N) {
    if (N <= 0) return 0;

    Line* linebuffer = NULL;
    char interline [1024]; //Linea intermedia para leer la entrada del bufer

    while(!feof(stdin)) {
        char* auxline = fgets(interline, sizeof(interline), stdin);
        if(auxline != NULL){
            //Recogemos el struct linea en el buffer de lineas
            Line line;
            line.content = auxline;
            line.size = strlen(interline);
            linebuffer[i] = line;
        }
    }
    return 0;
}

