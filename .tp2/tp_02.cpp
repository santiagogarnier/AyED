#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

#include "rwstring.hpp"
#include "listas.hpp"

// ============ CONSTANTES ============

const int LACCION = 12;
const int LBOLSA = 14;

// ============ ESTRUCTURAS ============

// Estructura del registro del archivo
struct Registro {
    string accion;
    int plazo;
    string bolsa;
    float precioUnitario;
    int cantidad;
};

// Estructura para cada operación en el nivel 3 del listado
struct OperacionInfo {
    string tipo;        // "COMPRA" o "VENTA"
    string accion;
    int cantidad;
};

// Estructura para cada bolsa (nivel 2)
struct BolsaInfo {
    string nombre;
    float totalNegociado;  // Valor absoluto
    float resultado;       // Con signo
    Nodo<OperacionInfo>* operaciones;  // Lista de operaciones
};

// Estructura para cada plazo (nivel 1)
struct PlazoInfo {
    string nombre;
    int cantVentas;
    int cantCompras;
    Nodo<BolsaInfo>* bolsas;  // Lista ordenada de bolsas
};

// ============ FUNCIONES DE COMPARACIÓN ============

int compararBolsas(BolsaInfo b1, BolsaInfo b2) {
    if (b1.nombre < b2.nombre) return -1;
    if (b1.nombre > b2.nombre) return 1;
    return 0;
}

// ============ FUNCIÓN PARA LEER EL ARCHIVO ============

void leerYProcesarArchivo(const string& nombreArchivo, PlazoInfo plazos[4]) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::in | ios::binary);
    
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return;
    }
    
    // Inicializar los nombres de plazos
    plazos[0].nombre = "CI (contado inmediato)";
    plazos[1].nombre = "24hs";
    plazos[2].nombre = "48hs";
    plazos[3].nombre = "72hs";
    
    for (int i = 0; i < 4; i++) {
        plazos[i].cantVentas = 0;
        plazos[i].cantCompras = 0;
        plazos[i].bolsas = nullptr;
    }
    
    cout << "========== LECTURA DEL ARCHIVO ==========" << endl << endl;
    
    int numOp = 1;
    Registro reg;
    
    // Leer archivo hasta el final
    while (!archivo.eof()) {
        // Leer cada campo
        reg.accion = readstring(archivo, LACCION);
        archivo.read(reinterpret_cast<char*>(&reg.plazo), sizeof(int));
        if (archivo.eof()) break;  // Verificar EOF después de leer
        
        reg.bolsa = readstring(archivo, LBOLSA);
        archivo.read(reinterpret_cast<char*>(&reg.precioUnitario), sizeof(float));
        archivo.read(reinterpret_cast<char*>(&reg.cantidad), sizeof(int));
        
        // Mostrar operación leída
        cout << "Operación #" << numOp++ << ":" << endl;
        cout << "  Acción: " << reg.accion << endl;
        cout << "  Plazo: " << reg.plazo << " (" << plazos[reg.plazo].nombre << ")" << endl;
        cout << "  Bolsa: " << reg.bolsa << endl;
        cout << "  Precio: $" << fixed << setprecision(2) << reg.precioUnitario << endl;
        cout << "  Cantidad: " << reg.cantidad;
        
        string tipo = (reg.cantidad < 0) ? "COMPRA" : "VENTA";
        cout << " (" << tipo << ")" << endl << endl;
        
        // ========== PROCESAR OPERACIÓN ==========
        
        // Actualizar contadores del plazo
        if (reg.cantidad < 0) {
            plazos[reg.plazo].cantCompras++;
        } else {
            plazos[reg.plazo].cantVentas++;
        }
        
        // Buscar o crear la bolsa en este plazo
        BolsaInfo bolsaBuscar;
        bolsaBuscar.nombre = reg.bolsa;
        bolsaBuscar.totalNegociado = 0;
        bolsaBuscar.resultado = 0;
        bolsaBuscar.operaciones = nullptr;
        
        Nodo<BolsaInfo>* nodoBolsa = insertar_unico(bolsaBuscar, plazos[reg.plazo].bolsas, compararBolsas);
        
        // Actualizar totales de la bolsa
        float monto = reg.precioUnitario * reg.cantidad;
        nodoBolsa->dato.totalNegociado += fabs(monto);
        nodoBolsa->dato.resultado += monto;
        
        // Agregar la operación a la lista de operaciones de la bolsa
        OperacionInfo opInfo;
        opInfo.tipo = tipo;
        opInfo.accion = reg.accion;
        opInfo.cantidad = abs(reg.cantidad);
        
        agregar(nodoBolsa->dato.operaciones, opInfo);
    }
    
    archivo.close();
    cout << "========== FIN DE LECTURA ==========" << endl << endl;
}

// ============ FUNCIÓN PARA EMITIR EL LISTADO ============

void emitirListado(PlazoInfo plazos[4]) {
    cout << endl << "============================================" << endl;
    cout << "        LISTADO DE OPERACIONES" << endl;
    cout << "============================================" << endl << endl;
    
    for (int p = 0; p < 4; p++) {
        cout << "============================================" << endl;
        cout << "Plazo: " << plazos[p].nombre << endl;
        cout << "Ventas: " << plazos[p].cantVentas << " | Compras: " << plazos[p].cantCompras << endl;
        cout << "============================================" << endl << endl;
        
        Nodo<BolsaInfo>* bolsa = plazos[p].bolsas;
        
        while (bolsa != nullptr) {
            cout << "  Bolsa: " << bolsa->dato.nombre << endl;
            cout << "  Total negociado: $" << fixed << setprecision(2) 
                 << bolsa->dato.totalNegociado << endl;
            cout << "  Resultado: $" << bolsa->dato.resultado << endl;
            cout << "  Operaciones:" << endl << endl;
            
            Nodo<OperacionInfo>* op = bolsa->dato.operaciones;
            
            while (op != nullptr) {
                cout << "    " << op->dato.tipo 
                     << " | Accion: " << op->dato.accion 
                     << " | Cantidad: " << op->dato.cantidad << endl;
                op = op->sig;
            }
            
            cout << endl;
            bolsa = bolsa->sig;
        }
    }
    
    cout << "------------------------------------------" << endl;
}

// ============ MAIN ============

int main() {
    PlazoInfo plazos[4];
    
   cout << "---------------BROKER FINANCIERO --------------------"<<endl;
    
    leerYProcesarArchivo("operaciones.dat", plazos);
    
    emitirListado(plazos);
    
    return 0;
}