#include "matrices.h"

#define NACERA 3
#define MORIRA 2

//---------------------------CREAR, LIBERAR Y VER MATRIZ

int** creaMatriz(int tamFil, int tamCol)
{
    int i,j;
    int ** ini;
    int ** m = (int**)calloc(tamFil*sizeof(int*), sizeof(int));
   if(!(m))
    {
      return 0;
    }
    i=0;
    ini = m;
  while(i<tamFil)
  {
    *m=(int*)calloc(tamCol , sizeof(int));
    if(!(*m))
    {
      m=ini;// vuelve al inicio del "vector grande" paralelo de la matriz
      for(j=0;j<=i;j++)
      {
        free(*m); //libera todas los ''vectores'' que hizo hasta ahora
        m++;
      }
      free(ini); //libera al ''vector grande''
      i=tamFil; //corta el while
    }
    m++;
    i++;
  }
  return ini;
}

void liberarMatriz(int** m, int tamFil)
{
    int i;
    int ** ini;
    ini = m;
    for(i=0;i<tamFil; i++)
    {
        free(*m);
        m++;
    }
    free(ini);
}

void verMatriz(int** m, int cf, int cc)
{
    int f, c;
    for(f=0;f<cf;f++)
    {
        for(c=0;c<cc;c++)
        {
            if(m[f][c]!= 0)
                printf("%d",m[f][c]);
            else
                printf(" ");
        }
        puts("  ");
    }
}
//---------------------------GENERAR PATRONES
void generarPlaneador(int **tablero) {

    *(*(tablero + 0) + 1) = 1;
    *(*(tablero + 1) + 2) = 1;
    *(*(tablero + 2) + 0) = 1;
    *(*(tablero + 2) + 1) = 1;
    *(*(tablero + 2) + 2) = 1;
}

void generarSapo(int **tablero) {
    *(*(tablero + 1) + 1) = 1; // (1,1)
    *(*(tablero + 1) + 2) = 1; // (1,2)
    *(*(tablero + 1) + 3) = 1; // (1,3)
    *(*(tablero + 2) + 0) = 1; // (2,0)
    *(*(tablero + 2) + 1) = 1; // (2,1)
    *(*(tablero + 2) + 2) = 1; // (2,2)
}
void generarPulsar(int **tablero, int cf, int cc) {
    int centerX = (cf / 2) - (TAMMINP / 2);  // centramos el patron
    int centerY = (cc / 2) - (TAMMINP / 2);

    //por si son negativas
    if (centerX < 0) centerX = 0;
    if (centerY < 0) centerY = 0;

    *(*(tablero + (centerX + 2)) + (centerY + 4)) = 1;
    *(*(tablero + (centerX + 2)) + (centerY + 5)) = 1;
    *(*(tablero + (centerX + 2)) + (centerY + 6)) = 1;
    *(*(tablero + (centerX + 2)) + (centerY + 10)) = 1;
    *(*(tablero + (centerX + 2)) + (centerY + 11)) = 1;
    *(*(tablero + (centerX + 2)) + (centerY + 12)) = 1;

    *(*(tablero + (centerX + 7)) + (centerY + 4)) = 1;
    *(*(tablero + (centerX + 7)) + (centerY + 5)) = 1;
    *(*(tablero + (centerX + 7)) + (centerY + 6)) = 1;
    *(*(tablero + (centerX + 7)) + (centerY + 10)) = 1;
    *(*(tablero + (centerX + 7)) + (centerY + 11)) = 1;
    *(*(tablero + (centerX + 7)) + (centerY + 12)) = 1;

    *(*(tablero + (centerX + 9)) + (centerY + 4)) = 1;
    *(*(tablero + (centerX + 9)) + (centerY + 5)) = 1;
    *(*(tablero + (centerX + 9)) + (centerY + 6)) = 1;
    *(*(tablero + (centerX + 9)) + (centerY + 10)) = 1;
    *(*(tablero + (centerX + 9)) + (centerY + 11)) = 1;
    *(*(tablero + (centerX + 9)) + (centerY + 12)) = 1;

    *(*(tablero + (centerX + 14)) + (centerY + 4)) = 1;
    *(*(tablero + (centerX + 14)) + (centerY + 5)) = 1;
    *(*(tablero + (centerX + 14)) + (centerY + 6)) = 1;
    *(*(tablero + (centerX + 14)) + (centerY + 10)) = 1;
    *(*(tablero + (centerX + 14)) + (centerY + 11)) = 1;
    *(*(tablero + (centerX + 14)) + (centerY + 12)) = 1;

    *(*(tablero + (centerX + 4)) + (centerY + 2)) = 1;
    *(*(tablero + (centerX + 5)) + (centerY + 2)) = 1;
    *(*(tablero + (centerX + 6)) + (centerY + 2)) = 1;
    *(*(tablero + (centerX + 10)) + (centerY + 2)) = 1;
    *(*(tablero + (centerX + 11)) + (centerY + 2)) = 1;
    *(*(tablero + (centerX + 12)) + (centerY + 2)) = 1;

    *(*(tablero + (centerX + 4)) + (centerY + 7)) = 1;
    *(*(tablero + (centerX + 5)) + (centerY + 7)) = 1;
    *(*(tablero + (centerX + 6)) + (centerY + 7)) = 1;
    *(*(tablero + (centerX + 10)) + (centerY + 7)) = 1;
    *(*(tablero + (centerX + 11)) + (centerY + 7)) = 1;
    *(*(tablero + (centerX + 12)) + (centerY + 7)) = 1;

    *(*(tablero + (centerX + 4)) + (centerY + 9)) = 1;
    *(*(tablero + (centerX + 5)) + (centerY + 9)) = 1;
    *(*(tablero + (centerX + 6)) + (centerY + 9)) = 1;
    *(*(tablero + (centerX + 10)) + (centerY + 9)) = 1;
    *(*(tablero + (centerX + 11)) + (centerY + 9)) = 1;
   *(*(tablero + (centerX + 12)) + (centerY + 9)) = 1;

    *(*(tablero + (centerX + 4)) + (centerY + 14)) = 1;
    *(*(tablero + (centerX + 5)) + (centerY + 14)) = 1;
    *(*(tablero + (centerX + 6)) + (centerY + 14)) = 1;
    *(*(tablero + (centerX + 10)) + (centerY + 14)) = 1;
    *(*(tablero + (centerX + 11)) + (centerY + 14)) = 1;
    *(*(tablero + (centerX + 12)) + (centerY + 14)) = 1;
}
void generarCanonPlaneadores(int **tablero, int cf, int cc) {
    int y = cf / 2 - (FCANIONP / 2); // Centrar en filas
    int x = cc / 2 - (CCANIONP / 2); // Centrar en columnas

    //por si son negativas
    if (y < 5) y = 5;
    if (x < 0) x = 0;

    // bloque izquierdo
    *(*(tablero + y) + x) = 1;
    *(*(tablero + y) + (x + 1)) = 1;
    *(*(tablero + (y + 1)) + x) = 1;
    *(*(tablero + (y + 1)) + (x + 1)) = 1;

    // primer patrón (izquierda)
    *(*(tablero + y) + (x + 10)) = 1;
    *(*(tablero + (y - 1)) + (x + 10)) = 1;
    *(*(tablero + (y + 1)) + (x + 10)) = 1;
    *(*(tablero + (y + 2)) + (x + 11)) = 1;
    *(*(tablero + (y - 2)) + (x + 11)) = 1;
    *(*(tablero + (y + 3)) + (x + 12)) = 1;
    *(*(tablero + (y - 3)) + (x + 12)) = 1;
    *(*(tablero + (y + 3)) + (x + 13)) = 1;
    *(*(tablero + (y - 3)) + (x + 13)) = 1;
   *(*(tablero + y) + (x + 14)) = 1;
    *(*(tablero + (y + 2)) + (x + 15)) = 1;
    *(*(tablero + (y - 2)) + (x + 15)) = 1;
    *(*(tablero + y) + (x + 16)) = 1;
    *(*(tablero + (y - 1)) + (x + 16)) = 1;
    *(*(tablero + (y + 1)) + (x + 16)) = 1;
    *(*(tablero + y) + (x + 17)) = 1;

    // segundo patrón (derecha)
    *(*(tablero + (y - 1)) + (x + 20)) = 1;
    *(*(tablero + (y - 2)) + (x + 20)) = 1;
    *(*(tablero + (y - 3)) + (x + 20)) = 1;
    *(*(tablero + (y - 1)) + (x + 21)) = 1;
    *(*(tablero + (y - 2)) + (x + 21)) = 1;
    *(*(tablero + (y - 3)) + (x + 21)) = 1;
    *(*(tablero + y) + (x + 22)) = 1;
    *(*(tablero + (y - 4)) + (x + 22)) = 1;
    *(*(tablero + (y - 4)) + (x + 24)) = 1;
    *(*(tablero + (y - 5)) + (x + 24)) = 1;
    *(*(tablero + y) + (x + 24)) = 1;
    *(*(tablero + (y + 1)) + (x + 24)) = 1;

    // bloque derecho
    *(*(tablero + (y - 2)) + (x + 34)) = 1;
    *(*(tablero + (y - 3)) + (x + 34)) = 1;
    *(*(tablero + (y - 2)) + (x + 35)) = 1;
    *(*(tablero + (y - 3)) + (x + 35)) = 1;
}

//---------------------------EVALUACIONES DE LAS CELULAS VIVAS Y MUERTAS
void evaluaCelulasVecinas(int** m, int cf, int cc)
{
    int f, c;
    int cantCelulas;
    for(f=0;f<cf;f++)
    {
        for(c=0;c<cc;c++)
        {
            cantCelulas = 0;
            cantCelulas = vecinas(m, f, c, cf, cc); //posicion actual en la matriz + cantidad de filas y columnas
            /// determina estados intermedios para luego actualizarlos
            if((cantCelulas==3)&&(m[f][c]==0))
            {
                m[f][c]=NACERA;
            }
            else
            {
                if(((cantCelulas<=1)||(cantCelulas>3))&&(m[f][c]==1))
                    m[f][c]=MORIRA;
            }
        }
    }
}
int vecinas(int **matriz, int pF, int pC, int filas, int columnas) // PF=Posicion Fila y PC=Posicion Columna
{
    int cantVivas = 0;
    int i, j;
    for (i = -1; i <= 1; i++)
	{
        for (j = -1; j <= 1; j++)
	    {
            if ((i!=0)||(j!=0)) // ignorar a la celula que se evalua
            {
                if ((pF + i) >= 0 && (pF + i) < filas && (pC + j) >= 0 && (pC + j) < columnas) // controla celula dentro de submatriz de 3x3
                {
                    if((matriz[pF + i][pC + j]==1)||(matriz[pF + i][pC + j]==2))
                    {
                        cantVivas++;
                    }
                }
            }
	    }
    }
    return cantVivas;
}

void celulasNacenOMueren(int** m, int cf, int cc)
{
    int f, c;
    for(f=0;f<cf;f++)
    {
        for(c=0;c<cc;c++)
        {
            if(m[f][c]==NACERA)
            {
                m[f][c]=1;
            }
            if(m[f][c]==MORIRA)
            {
                m[f][c]=0;
            }
        }
    }
}


//--------------- FUNCIONES CORRESPONDIENTES AL MENU

void cargoNumIteraciones(int *nVueltas)
{
    int v;
    do
    {
        printf("\n ingrese iteraciones a realizar : ");
        scanf("%d",&v);

    } while (v<0);

    *nVueltas = v;

}
void ingresoValida (int *ingreso, int condicion)
{
    int ing;
    do
    {
        scanf("%d", &ing);
        if(ing <condicion)
        {
            printf("\nEl tablero es muy chico, vuelve a intentarlo: ");
        }
    }while(ing < condicion);

    *ingreso = ing;
}
///-----------------------JUEGO
void juga (int **m, int cf, int cc, int vueltas)
{
    int i;
    system("cls"); //limpia la pantalla
    for (i=0; i<vueltas-1;i++) //(vueltas -1 porque ya muestro la generacion 1 antes)
    {

        verMatriz(m,cf,cc);
         //getchar();
        system("pause"); //espera una tecla, muestra la matriz en el momento
        system("cls"); //limpia la pantalla
        evaluaCelulasVecinas(m,cf,cc);
        celulasNacenOMueren(m,cf,cc);

    }
}
