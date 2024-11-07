#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024  // Máxima longitud de cada línea

// Estructura que representa una línea de texto con su contenido y tamaño.

typedef struct {              // Contenido de la línea
    char* content;
    size_t size;             // Tamaño de la línea (número de caracteres)
} Line;



/**
 * Imprime las primeras N líneas de la entrada estándar.
 *
 * @param N Número de líneas a imprimir.
 * @return int Código de estado: 0 si es exitoso.
 */

int head(int N) {
    int count = 0;
    char buffer[MAX_LINE_LENGTH];

    //fgets sera NULL cuando se haya llegado al final del archivo o haya un error de lectura
    while((count < N) && fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL)
    {
        fputs(buffer, stdout);
        count++;
    }

    if(count == N) return 0;
    else return 1;
}

/**
 * Imprime las últimas N líneas de la entrada estándar.
 *
 * @param N Número de líneas a imprimir.
 * @return int Código de estado: 0 si es exitoso, 1 si ocurre un error.
 */

int tail(int N) {
    if (N <= 0) return 0;

    // Crear un búfer dinámico para almacenar punteros a las líneas
    char** lines_buffer = (char**)malloc(N * sizeof(char*));
    if (!lines_buffer) {
        fputs("Error al asignar memoria para el búfer de líneas\n", stdout);
        return 1;
    }

    // Inicializar el búfer con espacio para cada línea
    for (int i = 0; i < N; i++) {
        lines_buffer[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
        if (!lines_buffer[i]) {
            fputs("Error al asignar memoria para una línea\n", stdout);
            // Liberar memoria parcialmente asignada
            for (int j = 0; j < i; j++) {
                free(lines_buffer[j]);
            }
            free(lines_buffer);
            return 2;
        }
    }

    int line_count = 0;
    char* current_line;
    // Leer el stdin línea por línea, almacenando en un ciclo de N posiciones
    while (!feof(stdin)) {
        current_line = fgets(lines_buffer[line_count % N], MAX_LINE_LENGTH, stdin);
        if (current_line != NULL) line_count++;
    }

    // Imprimir las últimas N líneas en orden
    int start = line_count > N ? line_count % N : 0;
    int total_lines = line_count < N ? line_count : N;
    fputs("\n", stdout); //Se separa la respuesta de tail con un \n por legibilidad
    for (int i = 0; i < total_lines; i++) {
        fputs(lines_buffer[(start + i) % N], stdout); //Se usa % N para evitar acceder a direcciones de memoria no permitidas
    }

    // Liberar memoria asignada
    for (int i = 0; i < N; i++) {
        free(lines_buffer[i]);
    }
    free(lines_buffer);

    return 0;
}

/**
 * Crea una nueva línea a partir del contenido proporcionado.
 *
 * @param lineContent Cadena de caracteres que representa el contenido de la línea.
 * @return Line Estructura `Line` con el contenido de la línea y su tamaño.
 */

Line createLine(const char* lineContent) {
    Line line;
    line.size = strlen(lineContent);
    line.content = (char*)malloc((line.size + 1) * sizeof(char));
    if (line.content) {
        strcpy(line.content, lineContent); //Se podria sustituir con *line.content = lineContent
    }
    return line;
}


/**
 * Inserta una línea en una lista ordenada de líneas de mayor a menor longitud.
 *
 * @param newLine Línea a insertar.
 * @param list Array de líneas que contiene las líneas más largas encontradas.
 * @param size Puntero al tamaño actual de la lista de líneas.
 * @param N Número máximo de líneas a almacenar en la lista.
 */

void insertLineList(Line newLine, Line* list, int* size, int N) {
    int pos = *size;
    // Encontrar la posición correcta para insertar en orden descendente de longitud
    while (pos > 0 && list[pos - 1].size < newLine.size) {
        if (pos < N) {
            list[pos] = list[pos - 1];
        } else {
            free(list[pos - 1].content);
        }
        pos--;
    }

    // Insertar la nueva línea en la posición correcta
    if (pos < N) {
        list[pos] = newLine;
        if (*size < N) {
            (*size)++;
        }
    } else {
        free(newLine.content);  // Liberar si no cabe en la lista
    }
}

/**
 * Encuentra las N líneas más largas de la entrada estándar.
 *
 * @param N Número de líneas más largas a encontrar.
 * @return int Código de estado: 0 si es exitoso, 1 si ocurre un error.
 */

int longlines(int N) {
    if (N <= 0) return 0;

    Line* list = (Line*)malloc(N * sizeof(Line));
    if (!list) {
        fputs("Error al asignar memoria para la lista de líneas\n", stdout);
        return 1;
    }
    int lsize = 0;
    char linebuffer[MAX_LINE_LENGTH];

    while (fgets(linebuffer, MAX_LINE_LENGTH, stdin) != NULL) {
        Line line = createLine(linebuffer);
        insertLineList(line,list, &lsize, N);
    }

    // Imprimir las N líneas más largas
    fputs("\nLíneas más largas:\n", stdout);
    for (int i = 0; i < lsize; i++) {
        fputs(list[i].content, stdout);
        free(list[i].content);  // Liberar la memoria de cada línea después de imprimirla
    }

    // Liberar la memoria de la lista
    free(list);
    return 0;
}




