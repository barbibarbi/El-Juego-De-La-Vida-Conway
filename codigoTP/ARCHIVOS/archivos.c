#include "archivos.h"

void nombreArchivo(char *nomArch)
{
    char nom[TAMNOMARCH];
    puts("Ingresar nombre del archivo = ");
    scanf("%s", nom);
    strcat(nom, ".txt");
    strcpy(nomArch, nom);
}
int bajaCoordenadas(const char *nomArch, int **m, int cF, int cC)
{
    char buff[TAMCAD];
    FILE* arc = fopen(nomArch,"rt");
    if(!arc)
        return 0; //si no lo abre

    while(fgets(buff, sizeof(buff), arc))
    {

            ponerEnMatriz(m,buff);

    }

    fclose(arc);
    return 1;
}
void ponerEnMatriz (int **m, char *cadBuffer)
{
    tCoordenadas cords;

    if(strlen(cadBuffer)!=1) //Por si hay algun caracter que interprete como \n en el txt
    {
        sscanf (cadBuffer, "%d %d", &cords.f, &cords.c);

        m[cords.f-1][cords.c-1] = 1;
    }

}
