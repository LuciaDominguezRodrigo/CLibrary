//imports
#include "libreria.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

//constants
#define MAX_LINE_LENGTH 1024  // Max length allow on a line

//Structure (representing a tipe ) that represents a line of text with its content and size.
typedef struct {
    char line[MAX_LINE_LENGTH]; // Save the text corresponding to the line
    int length;      // Save the length of the line
} LineEntry;


/**
 * Prints the first N lines from stdin
 *
 * @param N    Number of lines that must be printed in stdout
 * @return int State Code: 0 if the operation has been executed , 1 otherwise
 */

int head(int N) {
    int count = 0;
    char buffer[MAX_LINE_LENGTH];

    //fgets is going to be NULL when eof or lecture error
    while((count < N) && fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL)
    {
        fputs(buffer, stdout);
        count++;
    }

    if(count == N) return 0;
    else return 1;
}

/**
 * Prints the last N lines from stdin
 *
 *  @param N    Number of lines that must be printed in stdout.
 *  @return int State Code: 0 if the operation has been executed , 1 otherwise
 */

int tail(int N) {
    if (N <= 0) return 0;

    // Create a dynamic buffer to store pointers to lines
    char** lines_buffer = (char**)malloc(N * sizeof(char*));
    if (!lines_buffer) {
        fputs("Error al asignar memoria para el búfer de líneas\n", stdout);
        return 1;
    }

    // Initialize the buffer with space for each line
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
    // Read the stdin line by line, storing in a loop of N positions
    while (fgets(lines_buffer[line_count % N], MAX_LINE_LENGTH, stdin) != NULL) {
        line_count++;
    }

    // Print the last N lines in order
    int start = line_count > N ? line_count % N : 0;
    int total_lines = line_count < N ? line_count : N;
    fputs("\n", stdout); //Separate the tail response with a \n for readability
    for (int i = 0; i < total_lines; i++) {
        fputs(lines_buffer[(start + i) % N], stdout); //% N is used to avoid accessing illegal memory addresses
    }

    fputs("\n", stdout);
    // Release allocated memory
    for (int i = 0; i < N; i++) {
        free(lines_buffer[i]);
    }
    free(lines_buffer);


    return 0;
}


/**
 * Inserts a new line into the ordered list of lines, maintaining order from
 * longest to shortest length.
 *
 * @param list      pointer to lineEntry structures where each entry contains a line and its length.
 * @param N         Maximum number of entries the list can hold.
 * @param newLine   Pointer to the new line to be inserted.
 * @param newLength Length of the new line in characters (not bytes).
 * @return void     This function does not return a value.
 *
 * Inserts the new line in the correct position within the list array, so that
 * the list remains ordered from longest to shortest line. If the list already
 * has N entries, the shortest line is removed to make space if the new line
 * is among the N longest lines.
 */
void insertLine(LineEntry *list, int N, const char *newLine, int newLength) {
    int i, j;

    // Find the position where the new line should be inserted
    for (i = 0; i < N; i++) {
        if (newLength > list[i].length) {
            break;
        }
    }

    // Whether the line should be inserted within the first N positions
    if (i < N) {
        // Move elements down to make space
        for (j = N - 1; j > i; j--) {
            list[j] = list[j - 1];
        }

        // Insert the new line in its correct position
        strncpy(list[i].line, newLine, MAX_LINE_LENGTH);
        list[i].length = newLength;
    }
}


/**
 * Reads lines from standard input and prints the longest N lines by character
 * count in descending order.
 *
 * @param N  Number of longest lines to print to stdout.
 * @return   int Status code: 0 if the function executes successfully, 2 in case of error in asigning memory,1 otherwise.
 *
 * The function configures the environment for UTF-8 to handle special characters
 * and reads lines from standard input. It keeps track of the N longest lines
 * (by character count, not byte length) and displays them in descending order.
 * If the input has fewer than N lines, it will print all of them.
 * An error is printed, and the function exits if N is not greater than 0.
 */
int longlines(int N) {
    if (N <= 0) {
        fprintf(stderr, "Error en el valor introducido (tiene que ser mayor que 0)\n");
        exit(1);
    } else {

        // Set the environment to UTF-8 to handle special characters
        setlocale(LC_ALL, "");
        LineEntry *list = malloc(N * sizeof(LineEntry));
        if (list == NULL) {
            fprintf(stderr, "Error al asignar memoria\n");
            exit(2);
        }
        char temporalLine[MAX_LINE_LENGTH];
        wchar_t wideLine[MAX_LINE_LENGTH];
        int i;

        // Initialize the list with length 0 to allow comparison
        for (i = 0; i < N; i++) {
            list[i].line[0] = '\0';
            list[i].length = 0;
        }

        // Read the input lines and process each one
        while (fgets(temporalLine, MAX_LINE_LENGTH, stdin)) {
            int byteLength = strlen(temporalLine); // Calculate the length in bytes
            if (temporalLine[byteLength - 1] == '\n') {
                temporalLine[byteLength - 1] = '\0'; // Remove the line break at the end
            }

            // Convert timeline from char* to wchar_t*
            mbstowcs(wideLine, temporalLine, MAX_LINE_LENGTH);
            int charLength = wcslen(wideLine);  // Calculates the length in characters

            // Insert the line into the list of the N longest lines
            insertLine(list, N, temporalLine, charLength);
        }

        // Print the N longest lines in order
        for (i = 0; i < N; i++) {
            if (list[i].length > 0) {
                printf("%i - %s (Longitud en caracteres: %d)\n", i + 1, list[i].line, list[i].length);
            }
        }
        // free memory
        free(list);
    }
    return 0;
}