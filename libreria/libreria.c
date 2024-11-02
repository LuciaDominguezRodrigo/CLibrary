#include "libreria.h"
#include <stdio.h>

int head(int N) {
    char buffer[1024];
    for(int i = 0; i < N; i++) {
        fgets(buffer, 1024, stdin);
        fputs(buffer, stdout);
    }
    return 0;
}

int tail(int N) {
    return 0;
}
int longlines(int N) {
    return 0;
}