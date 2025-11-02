/*
 * PROYECTO: Conecta_4
 * MATERIA: Programación Dinámica
 * DOCENTE: Dr. Herman Geovany Ayala Zúñiga
 * ALUMNO: Wolfang Arturo García Méndez
 */
#include <iostream>
#include <vector>
#include <string>   // Para leer la entrada de forma segura
#include <sstream>  // Para validar la entrada numérica
#include <cctype>   // Para tolower() (lo usaremos en el commit 3)

 // --- Constantes Globales del Tablero ---
const int FILAS = 6;
const int COLUMNAS = 7;
const char JUGADOR_1 = 'X';
const char JUGADOR_2 = 'O';
const char VACIO = '.';

// --- Prototipos de Funciones ---
void inicializarTablero(std::vector<std::vector<char>>& tablero);
void mostrarTablero(const std::vector<std::vector<char>>& tablero);
int obtenerJugada(const std::vector<std::vector<char>>& tablero, char jugador);
bool esColumnaValida(const std::vector<std::vector<char>>& tablero, int col);
int colocarFicha(std::vector<std::vector<char>>& tablero, int col, char ficha);
// bool verificarGanador(...); // Lo añadiremos en el próximo commit
void jugarPartida();

/**
 * @brief Función principal.
 */
int main() {
    jugarPartida();
    // La lógica de "jugar de nuevo" irá en el próximo commit
    std::cout << "\n¡Gracias por jugar a Conecta 4! Adios." << std::endl;
    return 0;
}

/**
 * @brief Controla el flujo de una partida completa.
 */
void jugarPartida() {
    std::vector<std::vector<char>> tablero;
    inicializarTablero(tablero);

    char jugadorActual = JUGADOR_1;
    // bool juegoTerminado = false; // Se usará en el commit 3
    int turnosJugados = 0;

    mostrarTablero(tablero);

    // Bucle de juego principal
    // Por ahora, termina solo cuando el tablero está lleno
    while (turnosJugados < FILAS * COLUMNAS) {
        // 1. Obtener jugada
        int col = obtenerJugada(tablero, jugadorActual);

        // 2. Colocar la ficha
        colocarFicha(tablero, col, jugadorActual);

        turnosJugados++;
        mostrarTablero(tablero);

        // 3. Verificar si hay ganador (PENDIENTE)

        // 4. Verificar si hay empate (PENDIENTE)

        // 5. Cambiar de turno
        jugadorActual = (jugadorActual == JUGADOR_1) ? JUGADOR_2 : JUGADOR_1;
    }

    std::cout << "\nJuego terminado (lógica de ganador pendiente).\n";
}

/**
 * @brief Prepara el tablero con celdas vacías.
 */
void inicializarTablero(std::vector<std::vector<char>>& tablero) {
    tablero.assign(FILAS, std::vector<char>(COLUMNAS, VACIO));
}

/**
 * @brief Imprime el estado actual del tablero en la consola.
 */
void mostrarTablero(const std::vector<std::vector<char>>& tablero) {
    std::cout << "\n  --- CONECTA 4 --- \n";
    std::cout << "  1 2 3 4 5 6 7\n";
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

/**
 * @brief Solicita al usuario una columna (1-7) y la valida.
 * @return El índice de la columna (0-6).
 */
int obtenerJugada(const std::vector<std::vector<char>>& tablero, char jugador) {
    std::string input;
    int col = -1;

    while (true) {
        std::cout << "Turno del Jugador " << (jugador == JUGADOR_1 ? '1' : '2')
            << " (" << jugador << ").\n";
        std::cout << "Elige una columna (1-7): ";

        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> col && ss.eof()) {
            if (col >= 1 && col <= 7) {
                if (esColumnaValida(tablero, col - 1)) {
                    return col - 1; // Devuelve el índice base 0
                }
                else {
                    std::cout << "Error: Esa columna esta llena. Intenta de nuevo.\n";
                }
            }
            else {
                std::cout << "Error: Numero fuera de rango. Debe ser entre 1 y 7.\n";
            }
        }
        else {
            std::cout << "Error: Entrada invalida. Ingresa solo un numero.\n";
        }
    }
}

/**
 * @brief Verifica si una ficha puede ser colocada en una columna (si no está llena).
 */
bool esColumnaValida(const std::vector<std::vector<char>>& tablero, int col) {
    return tablero[0][col] == VACIO; // Solo chequear la celda superior
}

/**
 * @brief Coloca la ficha en la posición más baja disponible de la columna.
 * @return La fila (0-5) donde la ficha aterrizó.
 */
int colocarFicha(std::vector<std::vector<char>>& tablero, int col, char ficha) {
    for (int r = FILAS - 1; r >= 0; --r) {
        if (tablero[r][col] == VACIO) {
            tablero[r][col] = ficha;
            return r; // Devuelve la fila donde se colocó
        }
    }
    return -1; // No debería pasar si esColumnaValida se usó
}