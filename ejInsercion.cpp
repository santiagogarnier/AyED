#include <iostream>

using namespace std;

void mostrar(int a[], int len)
{
    for (int i = 0; i < len; i++)
    {

        cout << a[i] << " : " << endl;
    }
}
void insercion(int a[], int len)
{
    int i, j, temp;

    for ( i = 1; i < len; i++)
    {
        temp = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}
int main()
{
    const int len {7};
    int a[len] = {5,4,8,7,1,3,2};
    cout << "vector: " << endl;
    mostrar(a, len);
    insercion(a,len);
    cout << "Vector ordenado: " <<endl;
    mostrar(a,len);
    return 0;

}