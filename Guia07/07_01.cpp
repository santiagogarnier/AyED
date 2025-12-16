#include <iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;
/*Se dispone del archivo binario datos01.bin que contiene una lista no ordenada de ventas.
Cada venta tiene una campo modelo que es un string guardado en el archivo con 10 caracteres y el campo cantidad vendida que es un entero.*/

struct Venta{
    string modelo;
    int cantidad;
};

const int lmodelo {10};

//por modelo ascendente

int critmod(Venta a, Venta b){
    return a.modelo.compare(b.modelo);
}

ostream& operator << (ostream &os, const Venta& venta){
    os << "Modelo: "<<venta.modelo
    <<"\t" "Cantidad: "<<venta.cantidad;
    return os;
}

fstream &operator >> (fstream &fs, Venta& vta){
    vta.modelo = readstring(fs,lmodelo);
    fs.read(reinterpret_cast<char*>(&vta.cantidad),sizeof(vta.cantidad));
    return fs;
}

int main(){
    Nodo<Venta> *lista = nullptr;
    Nodo<Venta> *pnodo;
    Venta venta;
    Venta reg;
    fstream arch;

    arch.open("datos01.bin", ios :: in | ios :: binary );

    if(!arch){
        cout << "No se pudo abrir el archivo de lectura."<< endl;
        return EXIT_FAILURE;
    }
    venta.cantidad = 0;
    while(arch >> reg){
         venta.modelo = reg.modelo;
         pnodo = insertar_unico(venta,lista,critmod);
         pnodo->dato.cantidad += reg.cantidad;
    }
    arch.close();

    cout << "Listado de modelos con cantidad vendida: "<<endl;
    mostrar(lista);

    while(lista)
    pop(lista);

    return EXIT_SUCCESS;
}