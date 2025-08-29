#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define TAMMINSP 5 //Sapo y Planeador de 5 x 5
#define TAMMINP 17 //Pulsar de 17 x 17
#define FCANIONP 9 //Canion de planeadores de 9 x 36
#define CCANIONP 36



//------------------------MATRICES
int** creaMatriz(int tamFil, int tamCol);
void liberarMatriz(int** m, int tamFil);
void verMatriz(int** m, int cf, int cc);
void evaluaCelulasVecinas(int** m, int cf, int cc);
void celulasNacenOMueren(int** m, int cf, int cc);
int vecinas(int **matriz, int PF, int PC, int filas, int columnas);
//------------------------PATRONES
void generarPlaneador(int **tablero);
void generarSapo(int **tablero);
void generarPulsar(int **tablero, int cf, int cc);
void generarCanonPlaneadores(int **tablero, int cf, int cc);

///----------------------- MENU
void cargoNumIteraciones(int *nVueltas);
void ingresoValida (int *ingreso, int condicion);

///-----------------------JUEGO
void juga (int **m, int cf, int cc, int generaciones);
void generarTablero(int **m, int *f, int *c, int cf, int cc);


#endif // MATRICES_H_INCLUDED
