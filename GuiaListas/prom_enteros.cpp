#include <iostream>
#include "listas.hpp"

using namespace std;
/*Dada una lista que contiene enteros programe una función que recorriendo la 
lista devuelva el promedio (con decimales) de los valores guardados en la lista.*/

float prom(Nodo<int> *lista){
 int cant {}; 
 int sum{};
 while (lista != nullptr){
    ++cant;
    sum += lista ->dato;
    lista = lista -> sig;
 }

 return cant != 0 ? float(sum) / cant : 0.0;

}

int main (){
    Nodo<int> *lista {nullptr};

    //agrego datos

    agregar(lista,2);
    agregar(lista,4);
    agregar(lista,7);
    agregar(lista,8);
    agregar(lista,3);

    cout << "muestra de lista: " <<endl;
    mostrar(lista);
    cout << "==FIN"<<endl;

    cout << "Promedio: " << prom(lista) <<endl;

    //libero memoria

    while (lista != nullptr){
        pop(lista);
    }

    cout << "Promedio sin datos: "<<prom(lista) <<endl;

    return 0;
}