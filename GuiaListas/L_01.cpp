/*Dada una pila programe una función dup (por duplicar) que reciba la pila y duplique el elemento que está en el tope
(a menos que la pila esté vacía).
Por ejemplo si la pila un 1 al tope seguido más abajo de un 2 (Notación: 1, 2) luego de invocar esta función debe tener 1, 1, 2*/
#include <iostream>
#include "listas.hpp"

using namespace std;

template <typename T>
void duplicar(Nodo<T> *&pila)
{
    T primero;
    if (pila != nullptr)
    {
        primero = pop(pila);
        push(pila, primero); // una vez
        push(pila, primero); // lo duplica
    }
}

int main()
{
    Nodo<int> *pilaint = nullptr;
    cout << "Muestro la pila vacia: " << endl;
    mostrar(pilaint);


    duplicar(pilaint);
    cout << endl << "Muestro la pila despues de duplicar: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    push(pilaint, 2);
    push(pilaint, 1);
    cout << "Muestro la pila con los datos: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    duplicar(pilaint);
    cout << "Muestro la pila duplicada: " << endl;
    mostrar(pilaint);
    cout << "Fin de la pila" << endl;

    //=========AHORA CON CADENA DE CARACTERES==========
    Nodo<char> *pilachar{nullptr};
    push(pilachar, 'a');
    push(pilachar, 'b');
    cout << endl
         << "Muestro la pila con las letras: " << endl;
    mostrar(pilachar);
    cout << "Fin de la pila" << endl;

    duplicar(pilachar);
    cout << "Muestro la pila duplicada: " << endl;
    mostrar(pilachar);
    cout << "Fin de la pila" << endl;
    return 0;
}