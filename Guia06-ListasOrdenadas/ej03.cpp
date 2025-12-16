#include <iostream>
#include <fstream>
#include <cassert>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Deuda {
	string cliente;
	int mes;
	int cant;
};
const int lclie {8};

ostream& operator << (ostream &os, const Deuda& deuda)
{
	os << deuda.cliente << " - mes: " << deuda.mes
	   << " - cant: " << deuda.cant;
	return os;
}

fstream& operator << (fstream &fs, const Deuda& deuda)
{
	writestring(fs, deuda.cliente, lclie);
	fs.write(reinterpret_cast<const char *>(&deuda.mes), sizeof(deuda.mes));
	fs.write(reinterpret_cast<const char *>(&deuda.cant), sizeof(deuda.cant));
	return fs;
}

fstream& operator >> (fstream &fs, Deuda& deuda)
{
	deuda.cliente = readstring(fs, lclie);
	fs.read(reinterpret_cast<char *>(&deuda.mes), sizeof(deuda.mes));
	fs.read(reinterpret_cast<char *>(&deuda.cant), sizeof(deuda.cant));
	return fs;
}

//por cliente y ante igualdad por mes, ambos ascendente
int critdeu(Deuda a, Deuda b)
{
	if (a.cliente == b.cliente)
		return a.mes - b.mes;
	else
		return a.cliente > b.cliente ? 1 : -1;
}

template <typename T> void borrarSiguiente(Nodo<T>* actual)
{
	assert(actual != nullptr); //Precondiciones a cumplir
	assert(actual->sig != nullptr);
	//Si quisiera controlar en producción
	//if (actual && actual->sig) { lo-de-abajo }
	Nodo<T>* aborrar = actual->sig;
	actual->sig = actual->sig->sig;
	delete aborrar;
}

void consolidar(Nodo<Deuda>* lista)
{
	while (lista) {
		while (lista->sig && // Mientras sea mismo cliente y mes
		       critdeu(lista->dato, lista->sig->dato) == 0) {

			lista->dato.cant += lista->sig->dato.cant;
			borrarSiguiente(lista);
		}
		lista = lista->sig;
	}
}

int main()
{
	Nodo<Deuda> *lista = nullptr;
	Deuda deuda;
	fstream archi;

	archi.open("datos03.bin", ios::in | ios::binary);
	if (!archi) {
		cout << "No se pudo abrir el primer archivo de lectura "
		     "datos03.bin" << endl;
		return EXIT_FAILURE;
	}
	while (archi >> deuda) {
		insertar(deuda, lista, critdeu);
	}
	archi.close();

	cout << "Listado de deudas inicial:" << endl;
	mostrar(lista);

	cout << endl << "============================" << endl;
	cout << "Listado de deudas consolidado:" << endl;
	consolidar(lista);
	mostrar(lista);

	//Estrictamente no necesario, pero para no olvidarnos de
	//ser ordenados y prolijos con los recursos
	while (lista)
		pop(lista);
	return EXIT_SUCCESS;
}
