gcc -c libreria.c -o libreria.o
ar -rv liblibreria.a libreria.o
gcc -Wall -Wextra -o test.exe test.c  -L./ -llibreria