#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif

#include <SDL.h>
#include "MATRICES/matrices.h"
#include "ARCHIVOS/archivos.h"

/**
Pablo Soligo. Plantilla de proyecto codeblocks para juego de la vida.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuración de proyecto.
*/

#define CELL_SIZE 10  // Tamaño de cada celula en pixeles

void jugaSDL(int **m, int cf, int cc, int vueltas, SDL_Window* window, SDL_Renderer* renderer)
{
    unsigned char done = 0;
    int k = 0;
    int delay = 100;
    SDL_Event e;
    SDL_Rect fillRect;
    char titulo[200];
    int pausado = 0;
    int generacionActual = 0;

    while (!done && generacionActual < vueltas){ //Se puede parar tambien cuando no se observen cambios!
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                done = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    pausado = !pausado;
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    done = 1;
                }
            }
        }
        // Se limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Dibujar células vivas
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

        for (int f = 0; f < cf; f++) {
            for (int c = 0; c < cc; c++) {
                if (m[f][c] == 1 || m[f][c] == 2) {
                    fillRect.x = c * CELL_SIZE; //Pos X
                    fillRect.y = f * CELL_SIZE; //Pos Y
                    fillRect.h = CELL_SIZE - 1; //Alto
                    fillRect.w = CELL_SIZE - 1; //Ancho

                    //Plantilla para pintar cuadrados
                    SDL_RenderFillRect(renderer, &fillRect);

                    //Plantilla para pintar circulos si gusta mas
                    //drawFilledCircle(renderer, c*CELL_SIZE+CELL_SIZE/2, f*CELL_SIZE+CELL_SIZE/2, CELL_SIZE/2-1);
                }
            }
        }

        // Dibujar grilla
        SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
        for (int c = 0; c <= cc; c++) {
            SDL_RenderDrawLine(renderer, c * CELL_SIZE, 0, c * CELL_SIZE, cf * CELL_SIZE);
        }
        for (int f = 0; f <= cf; f++) {
            SDL_RenderDrawLine(renderer, 0, f * CELL_SIZE, cc * CELL_SIZE, f * CELL_SIZE);
        }

        // Actualizacion del "lienzo"
        SDL_RenderPresent(renderer);
        k++;
        //SDL_UpdateWindowSurface(window);

        //Titulo/caption de la ventana
        sprintf(titulo, "Juego de la vida - Generacion: %d/%d %s",
                generacionActual + 1, vueltas, pausado ? "(PAUSADO - Presione ESPACIO)" : "");
        SDL_SetWindowTitle(window, titulo);
        SDL_Delay(delay);

        //Procesamiento de matriz?
        if (!pausado && generacionActual < vueltas - 1) {
            evaluaCelulasVecinas(m, cf, cc);
            celulasNacenOMueren(m, cf, cc);
            generacionActual++;
        }
    }
}

int main(int argc, char *argv[])
{
    int **tablero=NULL;
    int opcion, generaciones, filas, columnas;
    char nomArch[TAMNOMARCH];
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    do {
        printf("Juego de la Vida de Conway - Menu\n");

        printf("1. Generar Planeador\n");
        printf("2. Generar Sapo\n");
        printf("3. Generar Pulsar\n");
        printf("4. Generar Canion de planeadores\n");
        printf("5. Generar por archivo\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
            case 2:
                    //*************************************************
                    if(tablero!=NULL)
                        liberarMatriz(tablero, filas);
                    //*************************************************

                    system("cls");
                    printf("Juego de la Vida de Conway - Crear tablero");

                    printf("\nIngrese cantidad de filas del tablero (Tamanio minimo para esta figura es %d): ", TAMMINSP);
                    ingresoValida(&filas,TAMMINSP);
                    printf("\nIngrese cantidad de columnas del tablero  Tamanio minimo para esta figura es %d): ", TAMMINSP);
                    ingresoValida(&columnas,TAMMINSP);
                    tablero = creaMatriz(filas,columnas);
                    system("cls");
                    if(opcion == 1)
                    {
                        generarPlaneador(tablero);
                        printf("Patron de Planeador generado:");
                    }
                    else
                    {
                        generarSapo(tablero);
                        printf("Patron de Sapo generado:");
                    }

                    cargoNumIteraciones(&generaciones);

                    // INICIALIZAR SDL
                    if (SDL_Init(SDL_INIT_VIDEO) != 0)
                    {
                        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
                        juga(tablero, filas, columnas, generaciones);
                    }
                    else
                    {
                        // Calcular tamaño ventana
                        int windowWidth = columnas * CELL_SIZE;
                        int windowHeight = filas * CELL_SIZE;
                        if (windowWidth > 1200) windowWidth = 1200;
                        if (windowHeight > 800) windowHeight = 800;

                        //Create window
                        window = SDL_CreateWindow("Juego de la vida",
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    windowWidth,
                                                    windowHeight,
                                                    SDL_WINDOW_SHOWN);
                        if (!window) {
                            SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
                            SDL_Quit();
                            juga(tablero, filas, columnas, generaciones);
                        }
                        else
                        {
                            // Creamos el lienzo
                            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                            if (!renderer) {
                                SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                                juga(tablero, filas, columnas, generaciones);
                            }
                            else
                            {
                                jugaSDL(tablero, filas, columnas, generaciones, window, renderer);

                                //destruyo todos los elementos creados
                                SDL_DestroyRenderer(renderer);
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                            }
                        }
                    }

                    verMatriz(tablero, filas, columnas);
                    break;

            case 3:
                //*************************************************
                    if(tablero!=NULL)
                        liberarMatriz(tablero, filas);
                //*************************************************
                system("cls");

                printf("Juego de la Vida de Conway - Crear tablero");

                printf("\nIngrese cantidad de filas del tablero (Tamanio minimo para esta figura es %d): ", TAMMINP);
                ingresoValida(&filas,TAMMINP);
                printf("\nIngrese cantidad de columnas del tablero  Tamanio minimo para esta figura es %d): ", TAMMINP);
                ingresoValida(&columnas,TAMMINP);
                tablero = creaMatriz(filas,columnas);

                system("cls");

                generarPulsar(tablero, filas, columnas);
                printf("Patron Pulsar generado\n");
                cargoNumIteraciones(&generaciones);

                // INICIALIZAR SDL (misma lógica que casos 1 y 2)
                if (SDL_Init(SDL_INIT_VIDEO) != 0)
                {
                    printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
                    juga(tablero, filas, columnas, generaciones);
                }
                else
                {
                    int windowWidth = columnas * CELL_SIZE;
                    int windowHeight = filas * CELL_SIZE;
                    if (windowWidth > 1200) windowWidth = 1200;
                    if (windowHeight > 800) windowHeight = 800;

                    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                windowWidth,
                                                windowHeight,
                                                SDL_WINDOW_SHOWN);
                    if (!window) {
                        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
                        SDL_Quit();
                        juga(tablero, filas, columnas, generaciones);
                    }
                    else
                    {
                        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                        if (!renderer) {
                            SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            juga(tablero, filas, columnas, generaciones);
                        }
                        else
                        {
                            jugaSDL(tablero, filas, columnas, generaciones, window, renderer);
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                        }
                    }
                }

                verMatriz(tablero, filas, columnas);
                break;

            case 4:
                //*************************************************
                    if(tablero!=NULL)
                        liberarMatriz(tablero, filas);
                //*************************************************

                system("cls");

                printf("Juego de la Vida de Conway - Crear tablero");

                printf("\nIngrese cantidad de filas del tablero (Tamanio minimo para esta figura es %d): ", FCANIONP);
                ingresoValida(&filas,FCANIONP);
                printf("\nIngrese cantidad de columnas del tablero  Tamanio minimo para esta figura es %d): ", CCANIONP);
                ingresoValida(&columnas,CCANIONP);
                tablero = creaMatriz(filas,columnas);

                system("cls");

                generarCanonPlaneadores(tablero, filas, columnas);
                printf("Patron Canon de Planeadores generado\n");
                cargoNumIteraciones(&generaciones);

                // INICIALIZAR SDL
                if (SDL_Init(SDL_INIT_VIDEO) != 0)
                {
                    printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
                    juga(tablero, filas, columnas, generaciones);
                }
                else
                {
                    int windowWidth = columnas * CELL_SIZE;
                    int windowHeight = filas * CELL_SIZE;
                    if (windowWidth > 1200) windowWidth = 1200;
                    if (windowHeight > 800) windowHeight = 800;

                    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                windowWidth,
                                                windowHeight,
                                                SDL_WINDOW_SHOWN);
                    if (!window) {
                        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
                        SDL_Quit();
                        juga(tablero, filas, columnas, generaciones);
                    }
                    else
                    {
                        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                        if (!renderer) {
                            SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            juga(tablero, filas, columnas, generaciones);
                        }
                        else
                        {
                            jugaSDL(tablero, filas, columnas, generaciones, window, renderer);
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                        }
                    }
                }

                verMatriz(tablero, filas, columnas);
                break;

            case 5:
                //*************************************************
                    if(tablero!=NULL)
                        liberarMatriz(tablero, filas);
                //*************************************************
                system("cls");

                printf("Juego de la Vida de Conway - Crear tablero");

                printf("\nIngrese cantidad de filas del tablero (Tamanio minimo para archivos es %d): ", FARCH);
                ingresoValida(&filas,FARCH);
                printf("\nIngrese cantidad de columnas del tablero  Tamanio minimo para archivos es %d): ", CARCH);
                ingresoValida(&columnas,CARCH);
                tablero = creaMatriz(filas,columnas);

                system("cls");

                nombreArchivo(nomArch);
                if(bajaCoordenadas(nomArch,tablero,filas,columnas))
                {
                    printf("Patron del archivo %s generado\n", nomArch);
                    cargoNumIteraciones(&generaciones);

                    // INICIALIZAR SDL
                    if (SDL_Init(SDL_INIT_VIDEO) != 0)
                    {
                        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
                        juga(tablero, filas, columnas, generaciones);
                    }
                    else
                    {
                        int windowWidth = columnas * CELL_SIZE;
                        int windowHeight = filas * CELL_SIZE;
                        if (windowWidth > 1200) windowWidth = 1200;
                        if (windowHeight > 800) windowHeight = 800;

                        window = SDL_CreateWindow("Juego de la vida",
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    windowWidth,
                                                    windowHeight,
                                                    SDL_WINDOW_SHOWN);
                        if (!window) {
                            SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
                            SDL_Quit();
                            juga(tablero, filas, columnas, generaciones);
                        }
                        else
                        {
                            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                            if (!renderer) {
                                SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                                juga(tablero, filas, columnas, generaciones);
                            }
                            else
                            {
                                jugaSDL(tablero, filas, columnas, generaciones, window, renderer);
                                SDL_DestroyRenderer(renderer);
                                SDL_DestroyWindow(window);
                                SDL_Quit();
                            }
                        }
                    }

                    verMatriz(tablero, filas, columnas);
                }
                else
                {
                    puts("No se puede abrir el archivo o nombre incorrecto");
                }

                break;
            case 0:
                    printf("Saliendo del programa...\n");
                    if(tablero!=NULL)
                        liberarMatriz(tablero, filas); //tiene que ir aca porque sino no puede liberar algo que no existe
                    break;

            default:
                    printf("Opcion no valida. Intentelo de nuevo.\n");
        }

    } while (opcion != 0);

    return 0;
}
