#include <iostream>
#include <fstream>
#include <cstring>
#include "listas.hpp"

using namespace std;

struct Orden
{
    int id;
    char cliente[8];
    char producto[10];
    int cantidad;
};

ostream &operator<<(ostream &os, const Orden &ordComp)
{
    os << "  ID: " << ordComp.id
       << "  CLIENTE: " << ordComp.cliente
       << "  PRODUCTO : " << ordComp.producto
       << "  CANTIDAD: " << ordComp.cantidad;
    return os;
}

// por ID ascendente
int critID(Orden a, Orden b)
{
    return a.id - b.id;
}

// por cliente y prodcuto ascendente

int critClienProd(Orden a, Orden b)
{
    int cmp = strcmp(a.cliente, b.cliente);
    if (cmp == 0)
        return strcmp(a.producto, b.producto);
    return cmp;
}

int main()
{
    Nodo<Orden> *listaid{nullptr};
    Nodo<Orden> *listaord{nullptr};

    Orden ordComp;
    ifstream arch("datos02.bin", ios::binary);

    if (!arch)
    {
        cout << "no se pudo abrir el archivo correctamente" << endl;
        return EXIT_FAILURE;
    }

    // Leo el archivo
    while (arch.read(reinterpret_cast<char *>(&ordComp), sizeof(Orden)))
    {
        insertar(ordComp, listaid, critID);
        insertar(ordComp, listaord, critClienProd);
    }
    arch.close();

    // a
    cout << "Listado ordenado por ID: " << endl;
    mostrar(listaid);

    cout << "Listado ordenado por cliente-producto: " << endl;
    mostrar(listaord);
    // b
    cout << endl
         << "=================" << endl;
    cout << "Ingrese ID a buscar: " << endl;
    Nodo<Orden> *buscado;
    cin >> ordComp.id;
    while (cin && ordComp.id > 0)
    {
        buscado = buscar(ordComp, listaid, critID);
        if (buscado)
            cout << buscado->dato << endl;
        else
            cout << "No hay ninguna orden con ID " << ordComp.id << endl;
        cout << "Ingrese el ID a buscar: " << endl;
        cin >> ordComp.id;
    }

    // punto c
    cout << " ==================" << endl;
    cout << "=== ELIMINACION POR  CLIENTE Y PRODUCTO == " << endl;

    cout << "Ingrese el cliente: " << endl;
    if (cin >> ordComp.cliente)
        cout << "Ingrese el producto: " << endl;
    while (cin >> ordComp.producto)
    {
        cout << "ELiminados." << endl;
        cout << "Lista remanente ordenada por ID: " << endl;
        mostrar(listaid);

        cout << "====================" << endl;
        cout << "Lista remanente ordenada por cliente-producto: " << endl;
        mostrar(listaord);

        cout << "Ingrese el cliente: " << endl;
        if (cin >> ordComp.cliente)
            cout << "Ingrese el producto: " << endl;
    }

    while (listaid);
    pop(listaid);

    while (listaord);
    pop(listaord);
}