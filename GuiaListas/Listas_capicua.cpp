#include <iostream>
#include "listas.hpp"
using namespace std;
// ignorando espacios en blanco
bool esCapicua(string palabra)
{
    Nodo<char> *pila{nullptr};
    int largo = palabra.size();
    int i;

    // ingreso de caracteres a la pila
    for (i = 0; i < largo; i++)
    {
        push(pila, palabra[i]);
    }

    // Compruebo la reversibilidad de la palabra
    for (i = 0; i < largo; i++)
    {
        if (palabra[i] != pop(pila))
        {
            break;
        }
    }

    // si no son capicua termino de vaciar la pila

    while (pila != nullptr)
        pop(pila);

    // es capicua si todos los caracteres coinciden
    return i == largo;
}

// teniendo en cuenta los espacios en blanco

bool esCapiB(string frase)
{
    Nodo<char> *pila{nullptr};
    int largo = frase.size();
    int i;
    // Ingreso de los caracteres a la pila
    for (i = 0; i < largo; ++i)
    {
        if (frase[i] != ' ')
        {
            push(pila, frase[i]);
        }
    }
    // Compruebo si la reversa que sale de la pila es igual a la de la frase
    for (i = 0; i < largo; i++)
    {
        if (frase[i] != ' ' && frase[i] != pop(pila))
        {
            break;
        }
    }

    while (pila != nullptr)
        pop(pila);

    return i == largo;
}
int main()
{

    string cadena;
    cout << "Ingrese una palabra a comprobar si es capicua: " << endl;
    cin >> cadena;

    if (esCapicua(cadena))
    {
        cout << cadena << " es capicua" << endl;
    }
    else
    {
        cout << cadena << " No es una palabra capicua " << endl;
    }
    // Variante con frases
    cout << "Ingrese la frase a comprobar: ";
    cin.get();            // elimino el salto de linea
    getline(cin, cadena); // para que no me corte en el primer espacio

    if (esCapiB(cadena))
    {
        cout << cadena << " es palindromo" << endl;
    }
    else
    {
        cout << cadena << " No es palindromo" << endl;
    }
    return 0;
}