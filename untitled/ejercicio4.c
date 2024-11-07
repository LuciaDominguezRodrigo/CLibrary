#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t hijos[4] = {-1, -1, -1, -1};
int i;

void manejadorHijo (int hermano); //hermano es el siguiente hijo

int main() {
    pid_t pid;
    signal (SIGUSR2,manejadorHijo);

    for (i=0;i<4;i++) {
        pid = fork();
        if (pid ==0) {
            pause();
        }
        else {
            hijos[i] = pid;
        }
    }


    kill(hijos[3],SIGUSR2); // LE DIGO AL HIJO 4 QUE CORRA

    // se tiene que esperar a que lleguen los 4
    for (i=0;i<4;i++) {
        wait(NULL);
    }
    printf("¡Carrera terminada!");
    return 0;
}

void manejadorHijo (int hermano) {
    printf("Corriendo: hijo %d con pid %d \n", i, getpid());
    sleep(2);
    if(i != 0)
    {
        printf("Este corredor ha terminado. Pasa el testigo al hijo %d con pid %d\n",i-1, hijos[i-1]);
        kill(hijos[i-1], SIGUSR2); //Mando señal al hermano
    }
    else
        printf("¡Se ha terminado!\n");
    exit(0);
}