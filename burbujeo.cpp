#include <iostream>

using namespace std;

//Shell sort en su versión original
void shell_sort(int v[], int dim)
{
	int i, j, temp, gap;

	gap = dim / 2;
	while (gap > 0) {
		for (i = gap; i < dim; i++) {
			temp = v[i];
			j = i - gap;
			while ((j >= 0) && (v[j] > temp)) {
				v[j+gap] = v[j];
				j -= gap;
			}
			v[j + gap] = temp;
		}
		gap /= 2;
	}
}

//Shell sort con la secuencia de gaps de Ciura, que es hasta ahora, empíricamente
//la más eficiente. La secuencia es "oficial" hasta 1750, el resto de los valores
//son una extrapolación: v(i) = truncar ( v(i-1) * 2.25 )
void shellCiura_sort(int v[], int dim)
{
	int i, j, temp;
	const int vgapdim {14};
	int gaps[vgapdim] = {1, 4, 10, 23, 57, 132, 301, 701, 1750, 3937, 8858,
				19930, 44842, 100894};
	//busco el elemento de gaps inmediatamente menor que dim
	int igap = buscar_bin_insert(dim, gaps, vgapdim) - 1;

	while (igap >= 0) {
		for (i = gaps[igap]; i < dim; i++) {
			temp = v[i];
			j = i - gaps[igap];
			while ((j >= 0) && (v[j] > temp)) {
				v[j+gaps[igap]] = v[j];
				j -= gaps[igap];
			}
			v[j+gaps[igap]] = temp;
		}
		--igap;
	}
}

int main()
{
	const int dimvec {15};
	int vec_ent[dimvec] = {248, 725, 349, 669, 17, 463, 796, 64, 102, 229
				 , 152, 833, 506, 964, 983
			      };

	cout << "Vector:" << endl;
	mostrar(vec_ent, dimvec);

	shell_sort(vec_ent, dimvec);
	cout << endl << "Vector Ordenado:" << endl;
	mostrar(vec_ent, dimvec);

	return 0;
}


