# :video_game: El juego de la vida de Conway :video_game: 

📚Este proyecto es una implementación del Juego de la Vida de Conway, un autómata celular de cero jugadores.  El objetivo fue desarrollar la lógica del juego con sus reglas en ![Lenguaje](https://img.shields.io/badge/Lenguaje-000000?style=for-the-badge)![C](https://img.shields.io/badge/C-blue?style=for-the-badge)  y utilizando ![Biblioteca](https://img.shields.io/badge/Biblioteca-000000?style=for-the-badge)![SDL2](https://img.shields.io/badge/SDL2-00FF00?style=for-the-badge) para su visualización grafica.

Todas las células se actualizan simultáneamente en cada turno o generación, siguiendo estas reglas:

* **Nace:** Si una célula muerta tiene exactamente 3 células vecinas vivas, "nace" (es decir, al turno siguiente estará viva).
* **Muere:** una célula viva puede morir por uno de 2 casos:
    * **Sobrepoblación:** si tiene más de tres vecinos alrededor.
    * **Aislamiento:** si tiene solo un vecino alrededor o ninguno.
* **Vive:** una célula se mantiene viva si tiene 2 o 3 vecinos a su alrededor.


>[!NOTE]
>Este fue un proyecto grupal para el primer cuatrimestre 2025 de la universidad en la materia Tópicos de programación.

