#include <iostream>
#include "listas.hpp"
using namespace std;

template <typename T>
void rot(Nodo<T> *&pila)
{
    // Verifico que haya al menos 3 elementos
    Nodo<T> *paux = pila;
    int contador = 0;
    
    while (paux != nullptr && contador < 3)
    {
        paux = paux->sig;
        contador++;
    }
    
    // Si no hay 3 elementos, no hago nada
    if (contador < 3)
        return;
    
    // Ahora sí roto los 3 primeros elementos
    T primero = pop(pila);   // Saco 1
    T segundo = pop(pila);   // Saco 2
    T tercero = pop(pila);   // Saco 3
    
    push(pila, segundo);     // Pongo 2
    push(pila, primero);     // Pongo 1
    push(pila, tercero);     // Pongo 3
}

template <typename T>
void rotarlista(Nodo<T> *&pila)
{
    // Verifico que haya al menos 3 elementos
    Nodo<T> *paux = pila;
    int contador = 0;
    
    while (paux != nullptr && contador < 3)
    {
        paux = paux->sig;
        contador++;
    }
    
    if (contador < 3)  // Si no hay 3, salgo
        return;
    
    // Uso lista auxiliar para rotar
    Nodo<T> *lista{nullptr};
    push(lista, pop(pila));    // 1
    push(lista, pop(pila));    // 2 -> 1
    agregar(lista, pop(pila)); // 2 -> 1 -> 3
    
    push(pila, pop(lista));    // Saco 2
    push(pila, pop(lista));    // Saco 1
    push(pila, pop(lista));    // Saco 3
}

int main()
{
    Nodo<int> *pilaint{nullptr};
    cout << "Muestro la pila vacia: " << endl;
    mostrar(pilaint);

    rot(pilaint);
    cout << "Pila despues de rotar: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;
    push(pilaint, 3);
    cout << "Muestra de pila con un dato: " << endl;
    mostrar(pilaint);
    cout << "fin pila" << endl;

    push(pilaint, 2);
    cout << "Muestro la pila con dos datos: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    rot(pilaint);
    cout << "Muestro pila despues de rotar los dos datos: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    push(pilaint, 1);
    cout << "Muestro la pila con tres datos: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    rot(pilaint);
    cout << " Muestro pila con tres datos: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    Nodo<char> *pilachar{nullptr};
    cout << "==================CON CARACTERES==================" << endl;
    push(pilachar, 'c');
    push(pilachar, 'd');
    push(pilachar, 'a');
    push(pilachar, 'b');
    cout << endl
         << "Muestra de la pila con las letras: " << endl;
    mostrar(pilachar);
    cout << "Fin de la pila" << endl;

    rotarlista(pilachar);
    cout << "Muestra de la pila despues de rotar: " << endl;
    mostrar(pilachar);
    cout << "Fin de la pila" << endl;

    // LIbero memoria
    while (pilaint != nullptr)
        pop(pilaint);
    while (pilachar != nullptr)
        pop(pilachar);
    return 0;
}