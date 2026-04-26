/*
 * Autor: [Tu nombre]
 * Proyecto: Generador de secuencia de Fibonacci
 * Descripcion: Genera los primeros N terminos de la secuencia de Fibonacci
 *              y escribe los resultados en fibonacci.txt para su graficacion.
 * Compilar: make
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>

// Calcula el n-esimo termino de Fibonacci usando la definicion recursiva eficiente
std::vector<long long> fibonacci(int n) {
    std::vector<long long> seq(n);
    if (n >= 1) seq[0] = 0;
    if (n >= 2) seq[1] = 1;
    for (int i = 2; i < n; ++i) {
        seq[i] = seq[i-1] + seq[i-2];
    }
    return seq;
}

int main(int argc, char** argv) {
    // Numero de terminos (por defecto 40, o el primer argumento)
    int n = 40;
    if (argc > 1) {
        n = std::atoi(argv[1]);
        if (n <= 0 || n > 90) {
            std::cerr << "Error: N debe estar entre 1 y 90.\n";
            return 1;
        }
    }

    std::vector<long long> seq = fibonacci(n);

    // Salida en consola
    std::cout << "Secuencia de Fibonacci (primeros " << n << " terminos):\n";
    std::cout << std::setw(5) << "n" << std::setw(20) << "F(n)" << "\n";
    std::cout << std::string(25, '-') << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(5) << i << std::setw(20) << seq[i] << "\n";
    }

    // Guardar datos en archivo para GNUplot
    std::string filename = "fibonacci.txt";
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filename << "\n";
        return 1;
    }
    out << "# n  F(n)\n";
    for (int i = 0; i < n; ++i) {
        out << i << "  " << seq[i] << "\n";
    }
    out.close();

    std::cout << "\nDatos guardados en " << filename << "\n";
    return 0;
}
