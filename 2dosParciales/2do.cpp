#include <iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro
{
    string producto;
    string canal;
    int unidades;
    float monto;
};

const int lprod{8};
const int lcanal{8};

struct Ventas
{
    string canal;
    int unidades;
};

struct Producto
{
    string producto;
    int cantvtas = 0;
    float summontos = 0;
    Nodo<Ventas> *lisvta = nullptr;
};

struct Canal
{
    string canal;
    float monto;
};

ostream &operator<<(ostream &os, const Ventas vtas)
{
    os << vtas.canal << "\t" << vtas.unidades;
    return os;
};

ostream &operator<<(ostream &os, const Canal &can)
{
    os << can.canal << "\t$" << can.monto;
    return os;
}

ostream &operator<<(ostream &os, const Producto prod)
{
    os << prod.producto << "\t" << prod.cantvtas << "\t" << prod.summontos;
    return os;
}

fstream &operator>>(fstream &fs, Registro &reg)
{
    reg.producto = readstring(fs, lprod);
    reg.canal = readstring(fs, lcanal);
    fs.read(reinterpret_cast<char *>(&reg.unidades), sizeof(reg.unidades));
    fs.read(reinterpret_cast<char *>(&reg.monto), sizeof(reg.monto));
    return fs;
}

// por producto ascendente

int critprod(Producto a, Producto b)
{
    return a.producto.compare(b.producto);
}

// por canal ascendente

int critcanal(Canal a, Canal b)
{
    return a.canal.compare(b.canal);
}

const int maxvtas{12};
const float minprom{280.0};

void listarProd(Nodo<Producto> *lis)
{
    while (lis != nullptr)
    {
        if (lis->dato.summontos < minprom)
        {
            cout << lis->dato << endl;
            if (lis->dato.summontos / lis->dato.cantvtas > minprom)
            {
                cout << "\n Canal \n Unidades " << endl;
                mostrar(lis->dato.lisvta);
            }
        }
        lis = lis->sig;
    }
}

void listarCan(Nodo<Canal> *lis)
{
    int cant{};
    while (lis)
    {
        cout << lis->dato << endl;
        if (lis->sig && lis->dato.canal != lis->sig->dato.canal &&
            lis->dato.monto > lis->sig->dato.monto)
            cant++;
        lis = lis->sig;
    }
    cout << "\n Casos donde al cambiar de canal, el monto bajo: " << cant << endl;
}

int main()
{
    // Cargo los datos

    Nodo<Producto> *listaprod = nullptr;
    Nodo<Canal> *listacan = nullptr;

    fstream arch;
    arch.open("Datos.bin", ios ::in | ios::binary);
    if (!arch)
    {
        cout << "No se pudo abrir el archivo" << endl;
        return EXIT_FAILURE;
    }

    // Carga de datos
    Registro reg;
    Producto prod;
    Ventas vta;
    
    Nodo<Producto> *pnodoprod;
    Canal can;
    while(arch >> reg){
        prod.producto = reg.producto;
        pnodoprod = insertar_unico(prod,listaprod, critprod);
        pnodoprod->dato.cantvtas ++;
        pnodoprod->dato.summontos += reg.monto;
        vta.canal = reg.canal;
        vta.unidades= reg.unidades;
        agregar(pnodoprod->dato.lisvta, vta);
        can.canal = reg.canal;
        can.monto = reg.monto;
        insertar(can,listacan, critcanal);
    }
    arch.close();

    cout << "Listado de productos \n"<<endl;
    listarProd(listaprod);

    cout << "Listado de canales\n"<<endl;
    listarCan(listacan);

    return 0;
}