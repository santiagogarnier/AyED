#include <iostream>

using namespace std;

void mostrarShell(int a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << i << " : " << a[i];
    }
}

void shellSort(int a[], int len)
{
    int i, j, gap, temp;
    gap = len / 2;
    while (gap > 0)
    {
        for (i = gap; i < len; i++)
        {
            temp = a[i];
            j = i - gap;
            while ((j >= 0) && (a[j] > temp))
            {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = temp;
        }
        gap /= 2;
    }
}

int main()
{
    const int len = 15;
    int a[len] = {248, 725, 349, 669, 17, 463, 796, 64, 102, 229,
                  152, 833, 506, 964, 983};
    cout << "Array antes de Shell: "<<endl;
    mostrarShell(a, len);

    shellSort(a, len);
    cout << "Vector ordenado: " << endl;

    mostrarShell(a, len);
    return 0;
}