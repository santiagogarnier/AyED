#include <iostream>
#include "listas.hpp"

using namespace std;

struct Alumno
{
    string nombre;
    int legajo;
    double promedio;
};

// listo los alumnos de forma ascendente y descendente
int critAlumno(Alumno a, Alumno b)
{
    if (a.promedio == b.promedio)
        return a.nombre.compare(b.nombre);
    else
    {
        return a.promedio > b.promedio ? -1 : 1;
    }
}

ostream &operator<<(ostream &os, const Alumno &a)
{
    os << a.nombre << "\t Legajo: " << a.legajo << "\t Promedio: " << a.promedio;
    return os;
}

int main()
{
    const int dim{4};
    Alumno vecselec[dim]{"Santi Garnier", 850, 8.50,
                         "Ampi Mendiburu", 950, 9.50,
                         "Luci Fernandez", 650, 7.50,
                         "Juli Lopez", 450, 6.50};
    // Alumnos que han pedido darse de baja

    const int dimbaj{2};
    Alumno darsebaja[dimbaj]{
        "Ampi Mendiburu", 950, 9.50,
        "Juli Lopez", 450, 6.50};

    Nodo<Alumno> *lista = nullptr;

    // punto a
    for (int i = 0; i < dim; i++)
        insertar(vecselec[i], lista, critAlumno);
    cout << "Lista de los seleccionados en orden: " << endl;
    mostrar(lista);
    cout << "==========================" << endl;

    // punto b
    cout << "Lista de alumnos bajados : " << endl;
    for (int i{}; i < dimbaj; i++)
        cout << darsebaja[i] << endl;

    // punto c

    for (int i{}; i < dimbaj; i++)
        borrar(darsebaja[i], lista, critAlumno);
    cout << "Listado sin las bajas: " << endl;
    mostrar(lista);

    while (lista)
        pop(lista);

    return 0;
}
