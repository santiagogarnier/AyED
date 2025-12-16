#include <fstream>
#include <string>
#include <iostream>
#include "rwstring.hpp"

using namespace std;

// Programa para CREAR el archivo de datos de prueba
// Compilar y ejecutar SOLO UNA VEZ para generar "operaciones.dat"

int main() {
    fstream archivo;
    archivo.open("operaciones.dat", ios::out | ios::binary);
    
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo" << endl;
        return 1;
    }

    // Datos de prueba: accion(12), plazo, bolsa(14), precio, cantidad
    // Cantidad negativa = COMPRA, positiva = VENTA
    
    // Plazo CI (0) - BCBA
    writestring(archivo, "YPFD", 12);
    int plazo = 0; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    float precio = 150.50; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    int cant = 100; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "GGAL", 12);
    plazo = 0; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 180.25; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -50; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "ALUA", 12);
    plazo = 0; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 95.75; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 200; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo CI (0) - NYSE
    writestring(archivo, "AAPL", 12);
    plazo = 0; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NYSE", 14);
    precio = 175.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -25; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "TSLA", 12);
    plazo = 0; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NYSE", 14);
    precio = 250.50; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 30; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 24hs (1) - BCBA
    writestring(archivo, "BBAR", 12);
    plazo = 1; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 420.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -80; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "PAMP", 12);
    plazo = 1; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 310.50; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 120; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 24hs (1) - NYSE
    writestring(archivo, "MSFT", 12);
    plazo = 1; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NYSE", 14);
    precio = 380.75; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 40; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 48hs (2) - BCBA
    writestring(archivo, "TXAR", 12);
    plazo = 2; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 88.20; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -150; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "CEPU", 12);
    plazo = 2; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 125.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 90; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 48hs (2) - NASDAQ
    writestring(archivo, "GOOGL", 12);
    plazo = 2; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NASDAQ", 14);
    precio = 142.30; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 60; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "NFLX", 12);
    plazo = 2; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NASDAQ", 14);
    precio = 455.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -35; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 72hs (3) - BCBA
    writestring(archivo, "CRES", 12);
    plazo = 3; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 75.50; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 200; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "LOMA", 12);
    plazo = 3; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 92.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -100; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Plazo 72hs (3) - NYSE
    writestring(archivo, "META", 12);
    plazo = 3; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NYSE", 14);
    precio = 315.80; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 45; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    // Operaciones adicionales
    writestring(archivo, "YPFD", 12);
    plazo = 1; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 152.00; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = -60; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "AAPL", 12);
    plazo = 2; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "NYSE", 14);
    precio = 176.25; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 80; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    writestring(archivo, "GGAL", 12);
    plazo = 3; archivo.write(reinterpret_cast<char*>(&plazo), sizeof(int));
    writestring(archivo, "BCBA", 14);
    precio = 182.50; archivo.write(reinterpret_cast<char*>(&precio), sizeof(float));
    cant = 110; archivo.write(reinterpret_cast<char*>(&cant), sizeof(int));
    
    archivo.close();
    cout << "✓ Archivo 'operaciones.dat' creado exitosamente!" << endl;
    cout << "✓ Ahora podes compilar y ejecutar tp_02.cpp" << endl;
    
    return 0;
}