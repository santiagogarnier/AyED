#include <iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro
{
    string pais;
    string empresa;
    string tipo;
    float energia;
    float costo;
};

const int lpais{9};
const int lempre{8};
const int ltipo{11};
const float minprom{20.1};
const float costomax{1000.0};

fstream &operator>>(fstream &fs, Registro &reg)
{
    reg.pais = readstring(fs, lpais);
    reg.empresa = readstring(fs, lempre);
    reg.tipo = readstring(fs, ltipo);
    fs.read(reinterpret_cast<char *>(&reg.energia), sizeof(reg.energia));
    fs.read(reinterpret_cast<char *>(&reg.costo), sizeof(reg.costo));
    return fs;
}

struct Nivel2
{
    string tipo;
    float costo;
};

ostream &operator<<(ostream &os, Nivel2 n2)
{
    os << "Tipo de planta: " << n2.tipo << '\t' << "Costo: " << n2.costo;
    return os;
};

struct Nivel1
{ // pais-empresa
    string pais;
    string empresa;
    float totenergia{};
    int cantdias{};
    Nodo<Nivel2> *lista{};
};

ostream &operator<<(ostream &os, Nivel1 n1)
{
    os << "Energia producida: " << n1.totenergia
       << "se produjo en " << n1.cantdias << " dias"
       << '\t' << "Promedio: " << n1.totenergia / n1.cantdias;
    if (n1.totenergia / n1.cantdias > minprom)
    {
        os << endl;
        mostrar(n1.lista);
    }
    return os;
};

// Ordenadoen forma ascendente por pais y empresa

int criterio(Nivel1 a, Nivel1 b)
{
    if (a.pais == b.pais)
        return a.empresa.compare(b.empresa);
    else
        return a.pais > b.pais ? 1 : -1;
}

// de forma descendente

int criterioN2(Nivel2 a, Nivel2 b)
{
    b.tipo.compare(a.tipo); // comparo b con a, ya que pide descendente;
}

bool mayor_que_siguiente(Nodo<Nivel1> *actual)
{
    assert(actual->sig != nullptr);
    float promactual = actual->dato.totenergia / actual->dato.cantdias;
    actual = actual->sig;
    float promsiguiente = actual->dato.totenergia / actual->dato.cantdias;
    return promactual > promsiguiente;
};

void listar(Nodo<Nivel2> *lista)
{
    while (lista != nullptr)
    {
        if (lista->dato.costo > costomax)
            cout << lista->dato << endl;
        lista = lista->sig;
    }
}

int main()
{
    fstream arch;
    arch.open("Datos.bin", ios ::in | ios::binary);
    if (!arch)
    {
        cout << "No se pudo abrir el archivo. " << endl;
        return EXIT_FAILURE;
    }

    Nodo<Nivel1> *lista = nullptr;
    Nodo<Nivel1> *pnodo;
    Nivel1 n1;
    Nivel2 n2;
    Registro reg;
    while (arch >> reg)
    {
        n1.pais = reg.pais;
        n1.empresa = reg.empresa;
        n2.tipo = reg.tipo;
        pnodo = insertar_unico(n1, lista, criterio);
        pnodo->dato.totenergia += reg.energia;
        pnodo->dato.cantdias++;

        n2.costo = reg.costo;
        n2.tipo = reg.tipo;
        insertar(n2, pnodo->dato.lista, criterioN2);
    }
    arch.close();

    mostrar(lista);

    cout << "Ingrese el pais y luego la empresa: ";
    while (cin >> n1.pais >> n1.empresa)
    {
        pnodo = buscar(n1, lista, criterio);
        if (pnodo)
        {
            if (pnodo->sig = nullptr)
            {
                cout << "No hay siguiente para la combinacion " << n1.pais << " con " << n1.empresa << endl;
            }
            else
            {
                cout << " El promedio fue " << (mayor_que_siguiente(pnodo) ? "mayor" : "menor") << "que el siguiente" << endl;
            }
            listar(pnodo->dato.lista);
        }
        else
        {
            cout << "No hay datos para la combinacion " << n1.pais
                 << " con " << n1.empresa << endl;
        }
        cout << "Ingrese el pais seguido de la empresa: ";
    }
    return 0;
}
