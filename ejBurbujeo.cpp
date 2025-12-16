#include <iostream>

using namespace std;
// El algortim recorre el array comparando a[i] con a[i+1]
void ordenar(int a[], int len)
{
    int ordenado = 0;
    while (!ordenado)
    {
        for (int i = 0; i < len - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                ordenado = 0;
            }
        }
    }
}

void mostrar(int a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << i << " : " << a[i] << endl;
    }
}

int main()
{
    const int len = 7;
    int a[len] = {5, 7, 2, 6, 1, 3, 4};
    cout << "Vector desordenado: " << endl;
    mostrar(a,len);
    ordenar(a, len);
    cout << "Vector ordenado : " << endl;
    mostrar(a,len);

    return 0;
}