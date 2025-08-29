#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <string.h>
#include <stdio.h>

#define TAMNOMARCH 100 //nombre maximo de un archivo
#define TAMCAD 6 //f c \n \0

#define FARCH 17
#define CARCH 37

typedef struct
{
    int f;
    int c;

}tCoordenadas;

void nombreArchivo(char *nomArch);
int bajaCoordenadas(const char *nomArch, int **m, int cF, int cC);
void ponerEnMatriz(int **m, char *cadBuffer);



#endif // ARCHIVOS_H_INCLUDED
