/*Dada una pila programe una función swap que inverta los dos
elementos tope. Si la pila tiene 1, 2, 3 luego de llamar a esta función tendrá 2, 1 , 3.
 Si la pila tiene menos de dos elementos la función la deja inalterada.*/

#include <iostream>
#include "listas.hpp"

using namespace std;

template <typename T>
void swapv(Nodo<T> *&pila)
{
    T primero, segundo;
    if (pila != nullptr)
    {
        primero = pop(pila);
        if (pila == nullptr) // En este caso no hay segundo elemento
        {
            push(pila, primero); // cambio el primero y vuelvo
            return;
        }
        segundo = pop(pila);
        push(pila, primero);
        push(pila, segundo);
    }
}

template <typename T>
void swapl(Nodo<T> *&pila) // uso la cola auxiliar
{
    Nodo<T> *cola{nullptr};
    if (pila != nullptr && pila->sig != nullptr)
    {
        agregar(cola, pop(pila));
        agregar(cola, pop(pila));
        push(pila, pop(cola));
        push(pila, pop(cola));
    }
}


int main()
{
    Nodo<int> *pilaint = nullptr;
    cout << "Muestro la pila vacia: "<<endl;
    mostrar(pilaint);
    cout << "Fin de la pila" <<endl;
    push(pilaint,3);
    swapv(pilaint);
    cout << "Muestra de pila despues del swap: "<<endl;
    mostrar(pilaint);
    cout<< "Fin de la pila" <<endl;

    push(pilaint, 2);
    cout<<"Muestra de pila con un dato: "<<endl;
    mostrar(pilaint);
    cout<<"Fin pila"<<endl;

    swapv(pilaint);
    cout<<"Pila despues del swap" <<endl;
    mostrar(pilaint);
    cout<<"Fin de la pila" <<endl;

    push(pilaint, 1);
    cout<<"Muestra de pila con dos datos: "<<endl;
    mostrar(pilaint);
    cout<<"Fin pila" <<endl;

    swapv(pilaint);
    cout<<"Pila despues del swap con dos datos" <<endl;
    mostrar(pilaint);
    cout<<"Fin de la pila" <<endl;


    /*===================CON CARACTERES==============*/
    Nodo<char> *pilachar{nullptr};
    cout << "*===================CON CARACTERES==============*"<<endl;
    push(pilachar, 'c');
    push(pilachar, 'b');
    push(pilachar, 'a');
    cout << "Muestra de pila con las tres letras: "<<endl;
    mostrar(pilachar);

    swapl(pilachar);
    cout<<"Muestro letras despues del swap: "<<endl;
    mostrar(pilachar);

    cout<< "Fin pila"<<endl;

    return 0;



}