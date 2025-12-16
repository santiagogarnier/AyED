#include <iostream>
#include <fstream>
#include <cstring>
#include "listas.hpp"

using namespace std;

struct Deuda
{
    char cliente[8];
    int mes;
    int cant;
};

ostream &operator<<(ostream &os, const Deuda &deuda)
{
    os << deuda.cliente << "--mes "
       << deuda.mes << "--cant "
       << deuda.cant;
    return os;
}

// POR CLIENTE Y MES ASCENDENTE
int critdeu(Deuda a, Deuda b)
{
    int cmp = strcmp(a.cliente, b.cliente); 
    if (cmp == 0)
        return a.mes - b.mes;
    return cmp;
}

// borarr siguiente

template <typename T>
void borrarSiguiente(Nodo<T> *actual)
{
    assert(actual != nullptr);
    assert(actual->sig != nullptr);

    Nodo<T> *auxaBorrar = actual->sig;
    actual->sig = auxaBorrar->sig;
    delete auxaBorrar;
}

void consolidar(Nodo<Deuda> *lista)
{
    while (lista)
    {
        while (lista->sig &&
               critdeu(lista->dato, lista->sig->dato) == 0)
        {
            lista->dato.cant += lista->sig->dato.cant;
            borrarSiguiente(lista);
        }
        lista = lista->sig;
    }
}
int main()
{
    Nodo<Deuda> *lista{nullptr};
    Deuda deuda;

    ifstream arch("datos03.bin", ios::binary);

    if (!arch)
    {
        cout << "No se pudo abrir el archivo de manera correcta." << endl;
        return EXIT_FAILURE;
    };

    // Leo el archivo
while (arch.read(reinterpret_cast<char *>(&deuda), sizeof(Deuda))) 
    {
        insertar(deuda, lista, critdeu);
    }
    arch.close();

    cout << "Listado de deudas inicial:" << endl;
    mostrar(lista);

    cout << "==================" << endl;
    cout << "Listado de deudas consolidadas: " << endl;
    consolidar(lista);
    mostrar(lista);

    while (lista)
        pop(lista);

    return EXIT_SUCCESS;
}