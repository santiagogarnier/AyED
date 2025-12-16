#include <iostream>

using namespace std;

// Defino el nodo
struct Nodo
{
    int info;
    Nodo *sgte;
};

void push(Nodo *&pila, int valor); // Agrega los elementos a la pila
int pop(Nodo *&pila);

// Ingreso el elemento con un void y lo saco al elemento con un int POp

int main()
{
    // Defino la pila
    Nodo *pila = NULL;
    int carga;
    // Cargo la pila
    cout << "Ingrese los valores : " <<endl;
    cin >> carga;
    while (carga != 0){
        push(pila,carga);
        cout << "Ingresar valor o termine con 0 : " <<endl;
        cin >> carga;
    }

    int result;

    //saco de la pila sin saber la cantidad de elementos

    while (pila != NULL)
    {
        result = pop(pila);
        cout << result <<endl;
    }
   
    return 0;
}

void push(Nodo *&pila, int valor)
{
    // 1.Creo el nodo -> es decir pedir memoria
    Nodo *nuevo_nodo = new Nodo();
    // 2.Cargo el nodo,
    nuevo_nodo->info = valor;
    nuevo_nodo->sgte = pila; // se actualiza la pila

    // 3.Conectar con el resto de los nodos
    pila = nuevo_nodo;
};
int pop(Nodo *&pila)
{
    // Guardo el valor de retorno
    int retorno;
    retorno = pila->info;
    Nodo *aux = pila;  // Auxiliar para no perder la referencia
    pila = pila->sgte; // Otra alternativa : pila=pila->sgte;
    delete aux;        // Para liberar memoria
    return retorno;
}; // saca los elementos de la pila -> Tinfo (devuelve el Tinfo)
