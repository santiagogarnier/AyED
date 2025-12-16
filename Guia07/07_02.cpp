#include <iostream>
#include <fstream>
#include "rwstring.hpp"
#include "listas.hpp"

using namespace std;

struct Registro
{
    string modelo;
    int cantidad;
    string ciudad;
};
const int lmodelo = 10;
const int lciu = 12;

struct Ventas
{
    string modelo;
    int cantidad;
};

struct Ciudad
{
    string ciudad;
    int vtastot = 0;
    int totcant = 0;
    Nodo<Ventas> *listvta = nullptr;
};

ostream &operator<<(ostream &os, const Ciudad &ciu)
{
    os << "Ciudad: " << ciu.ciudad
       << "Total ventas: " << ciu.vtastot;
    return os;
};

ostream &operator<<(ostream &os, const Ventas &vta)
{
    os << "Modelo: " << vta.modelo
       << "Cantidad vendida: " << vta.cantidad;

    return os;
};
fstream &operator>>(fstream &fs, Registro &reg)
{
    reg.ciudad = readstring(fs, lciu);
    reg.modelo = readstring(fs, lmodelo);
    fs.read(reinterpret_cast<char *>(&reg.cantidad), sizeof(reg.cantidad));
    return fs;
};
// listado ascendente de cada ciudad

int critCiudad(Ciudad a, Ciudad b)
{
    return a.ciudad.compare(b.ciudad);
}

int critModelo(Ventas a, Ventas b)
{
    return a.modelo.compare(b.modelo);
}

int main()
{

    Nodo<Ciudad> *listaciu = nullptr;
    fstream arch;

    arch.open("datos02.bin", ios ::in | ios::binary);
    if (!arch)
    {
        cout << "No se pudo abrir el archivo de lectura.";
        return EXIT_FAILURE;
    }
    Registro reg;
    Ciudad ciu;
    Ventas vta;

    Nodo<Ciudad> *pnodociu;
    while (arch >> reg)
    {
        ciu.ciudad = reg.ciudad;
        ciu.vtastot = 0;
        ciu.totcant = 0;
        ciu.listvta = nullptr;

        pnodociu = insertar_unico(ciu, listaciu, critCiudad);
        
        pnodociu->dato.vtastot++;
        pnodociu->dato.totcant += reg.cantidad;
        
        vta.modelo = reg.modelo;
        vta.cantidad = reg.cantidad;
        insertar(vta,pnodociu -> dato.listvta,critModelo);
    }

    arch.close();
    cout << "Listado de ciudades con totales de ventas y cantidades vendidas: " << endl;
    while (cin >> ciu.ciudad)
    {
        pnodociu = buscar(ciu, listaciu, critCiudad);
        if (pnodociu)
        {
            cout << "Ventas en la ciudad " << ciu.ciudad << endl;
            cout << "Modelo \t cantidad" << endl;
            mostrar(pnodociu->dato.listvta);
        }
        else
        {
            cout << "No hay datos de la ciudad " << ciu.ciudad << endl;
        }
        cout << "ingrese la ciudad a listar: " << endl;
    }
    cin.clear();
    clearerr(stdin);
    cout << "================PUNTO 3==================" << endl;
    // debo pedir ciudad y cantidad minima
    int cantmin;
    cout << "Ingrese ciudad: " << endl;
    if (cin >> ciu.ciudad)
        cout << "Ingrese cantidad minima: ";
    while (cin >> cantmin)
    {
        pnodociu = buscar(ciu, listaciu, critCiudad);
        if (pnodociu)
        {
            Nodo<Ventas> *p = pnodociu->dato.listvta;
            int cantsup = 0;
            while (p)
            {
                if (p->dato.cantidad > cantmin)
                    cantsup++;
                p = p->sig;
            }
            cout << "Ventas en " << ciu.ciudad << " con cantidad"
                 << "mayor a " << cantmin << " : " << cantsup << endl;
        }
        else
        {
            cout << "No hay datos de la ciudad " << ciu.ciudad << endl;
        }
        cout << "ingrese ciudad: ";
        if (cin >> ciu.ciudad)
            cout << "Ingrese cantidad minima: ";
    }
    while (listaciu->dato.listvta)
        pop(listaciu->dato.listvta);

    pop(listaciu);
    return 0;
}