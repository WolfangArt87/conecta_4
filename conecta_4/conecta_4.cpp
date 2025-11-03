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
#include <cctype>   // Para tolower()

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
bool verificarGanador(const std::vector<std::vector<char>>& tablero, int r, int c, char ficha);
void jugarPartida();

/**
 * @brief Función principal que maneja el bucle de "jugar de nuevo".
 */
int main() {
    char jugarDeNuevo = 's';
    do {
        jugarPartida();

        std::string input;
        while (true) {
            std::cout << "\n¿Quieren jugar otra partida? (s/n): ";
            std::getline(std::cin, input); // Leer la línea completa

            if (!input.empty()) {
                jugarDeNuevo = std::tolower(input[0]);
                if (jugarDeNuevo == 's' || jugarDeNuevo == 'n') {
                    break;
                }
            }
            std::cout << "Entrada invalida. Por favor, ingresa 's' o 'n'." << std::endl;
        }

    } while (jugarDeNuevo == 's');

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
    bool juegoTerminado = false; // Ahora sí lo usamos
    int turnosJugados = 0;

    mostrarTablero(tablero);

    while (!juegoTerminado) {
        // 1. Obtener jugada
        int col = obtenerJugada(tablero, jugadorActual);

        // 2. Colocar la ficha y obtener la fila donde cayó
        int fila = colocarFicha(tablero, col, jugadorActual);

        turnosJugados++;
        mostrarTablero(tablero);

        // 3. Verificar si hay ganador
        if (verificarGanador(tablero, fila, col, jugadorActual)) {
            std::cout << "\n****************************************\n";
            std::cout << "   ¡El Jugador " << (jugadorActual == JUGADOR_1 ? '1' : '2')
                << " (" << jugadorActual << ") HA GANADO!\n";
            std::cout << "****************************************\n";
            juegoTerminado = true;
        }
        // 4. Verificar si hay empate
        else if (turnosJugados == FILAS * COLUMNAS) {
            std::cout << "\n****************************************\n";
            std::cout << "             ¡EMPATE!\n";
            std::cout << "     El tablero esta lleno.\n";
            std::cout << "****************************************\n";
            juegoTerminado = true;
        }
        // 5. Cambiar de turno
        else {
            jugadorActual = (jugadorActual == JUGADOR_1) ? JUGADOR_2 : JUGADOR_1;
        }
    }
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
    return tablero[0][col] == VACIO;
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
    return -1; // No debería pasar
}

/**
 * @brief Verifica las 4 direcciones (H, V, D1, D2) desde la última jugada.
 */
bool verificarGanador(const std::vector<std::vector<char>>& tablero, int r, int c, char ficha) {

    // --- 1. Verificación Horizontal (← →) ---
    int contador = 0;
    for (int j = 0; j < COLUMNAS; ++j) {
        if (tablero[r][j] == ficha) {
            contador++;
            if (contador >= 4) return true;
        }
        else {
            contador = 0; // Rompe la racha
        }
    }

    // --- 2. Verificación Vertical (↑ ↓) ---
    contador = 0;
    for (int i = 0; i < FILAS; ++i) {
        if (tablero[i][c] == ficha) {
            contador++;
            if (contador >= 4) return true;
        }
        else {
            contador = 0;
        }
    }

    // --- 3. Verificación Diagonal Descendente (↘) ---
    contador = 0;
    int diag_r = r, diag_c = c;
    while (diag_r > 0 && diag_c > 0) { // Ir al inicio de la diagonal (arriba-izq)
        diag_r--;
        diag_c--;
    }
    while (diag_r < FILAS && diag_c < COLUMNAS) { // Recorrerla
        if (tablero[diag_r][diag_c] == ficha) {
            contador++;
            if (contador >= 4) return true;
        }
        else {
            contador = 0;
        }
        diag_r++;
        diag_c++;
    }

    // --- 4. Verificación Diagonal Ascendente (↗) ---
    contador = 0;
    diag_r = r; diag_c = c;
    while (diag_r < FILAS - 1 && diag_c > 0) { // Ir al inicio de la diagonal (abajo-izq)
        diag_r++;
        diag_c--;
    }
    while (diag_r >= 0 && diag_c < COLUMNAS) { // Recorrerla
        if (tablero[diag_r][diag_c] == ficha) {
            contador++;
            if (contador >= 4) return true;
        }
        else {
            contador = 0;
        }
        diag_r--;
        diag_c++;
    }

    return false; // No se encontró ganador
}