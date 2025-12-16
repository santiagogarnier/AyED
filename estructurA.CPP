#include <iostream>
using namespace std;

struct Alunno
{
    int legajo;
    string nombre,
        apellido;
    double promedio;
};

template <typename T>
void mostrarAlumno(T a[], int len, string titulos)
{
    cout << titulos << endl;
    for (int i = 0; i < len; i++)
    {
        cout << a[i] << endl;
    }
}