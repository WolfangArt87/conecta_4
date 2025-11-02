/*
 * PROYECTO: Conecta_4
 * MATERIA: Programación Dinámica
 * DOCENTE: Dr. Herman Geovany Ayala Zúñiga
 * ALUMNO: Wolfang Arturo García Méndez
 */

#include <iostream>
#include <vector>

// --- Constantes Globales del Tablero ---
const int FILAS = 6;
const int COLUMNAS = 7;
const char JUGADOR_1 = 'X';
const char JUGADOR_2 = 'O';
const char VACIO = '.';

// --- Prototipos de Funciones ---
void inicializarTablero(std::vector<std::vector<char>>& tablero);
void mostrarTablero(const std::vector<std::vector<char>>& tablero);
void jugarPartida(); // Prototipo para el bucle de juego principal

/**
 * @brief Función principal.
 */
int main() {
    jugarPartida();
    std::cout << "\n¡Gracias por jugar a Conecta 4! Adios." << std::endl;
    return 0;
}

/**
 * @brief Controla el flujo de una partida completa (por ahora, solo muestra el tablero).
 */
void jugarPartida() {
    std::vector<std::vector<char>> tablero;
    inicializarTablero(tablero);

    std::cout << "¡Bienvenido a Conecta 4!" << std::endl;
    mostrarTablero(tablero);

    // La lógica del juego irá aquí en el próximo commit
}

/**
 * @brief Prepara el tablero con celdas vacías.
 */
void inicializarTablero(std::vector<std::vector<char>>& tablero) {
    // Redimensiona el vector a 6 filas, y cada fila a 7 columnas, con '.'
    tablero.assign(FILAS, std::vector<char>(COLUMNAS, VACIO));
}

/**
 * @brief Imprime el estado actual del tablero en la consola.
 */
void mostrarTablero(const std::vector<std::vector<char>>& tablero) {
    std::cout << "\n  --- CONECTA 4 --- \n";
    std::cout << "  1 2 3 4 5 6 7\n"; // Guía de columnas
    std::cout << " -----------------\n";
    for (int i = 0; i < FILAS; ++i) {
        std::cout << "| ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << " -----------------\n";
}