#include <iostream>
#include <fstream>
#include <cassert>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Requerimiento {
	int urgencia;
	string cliente;
	double monto;
};
const int lclie {9};

ostream& operator << (ostream &os, const Requerimiento& req)
{
	os << req.urgencia << " - " << req.cliente
	   << " : " << req.monto;
	return os;
}

fstream& operator >> (fstream &fs, Requerimiento& req)
{
	fs.read(reinterpret_cast<char *>(&req.urgencia), sizeof(req.urgencia));
	req.cliente = readstring(fs, lclie);
	fs.read(reinterpret_cast<char *>(&req.monto), sizeof(req.monto));
	return fs;
}

//por urgencia y ante igualdad cliente, ambos ascendente
int criterio(Requerimiento a, Requerimiento b)
{
	if (a.urgencia == b.urgencia)
		return a.cliente.compare(b.cliente);
	else
		return a.urgencia - b.urgencia;
}

void informar(Nodo<Requerimiento>* lista)
{
	assert(lista != nullptr);
	Requerimiento clave = lista->dato;
	double total = 0;
	do {
		total += lista->dato.monto;
		cout << lista->dato << endl;
		lista = lista->sig;
	} while (lista && criterio(clave, lista->dato) == 0);
	cout << "Monto total: " << total << endl << endl;
}

int main()
{
	Nodo<Requerimiento> *lista = nullptr;
	Requerimiento req;
	fstream archi;

	archi.open("datos04.bin", ios::in | ios::binary);
	if (!archi) {
		cout << "No se pudo abrir el primer archivo de lectura "
		     "datos04.bin" << endl;
		return EXIT_FAILURE;
	}
	while (archi >> req) {
		insertar(req, lista, criterio);
	}
	archi.close();

	cout << "Listado total:" << endl;
	mostrar(lista);

	cout << endl << "============================" << endl;
	Nodo<Requerimiento> *p;
	cout << "Ingrese el nivel de urgencia: ";
	if (cin >> req.urgencia) {
		cout << "Ingrese el cliente: ";
		cin.get();
	}
	while (getline(cin, req.cliente)) {
		p = buscar(req, lista, criterio);
		if (p)
			informar(p);
		else
			cout << "No hay requerimientos con urgencia " << req.urgencia
			     << " y cliente " << req.cliente << endl;
		// Siguiente
		cout << "Ingrese el nivel de urgencia: ";
		if (cin >> req.urgencia) {
			cout << "Ingrese el cliente: ";
			cin.get();
		}
	}

	//Estrictamente no necesario, pero para no olvidarnos de
	//ser ordenados y prolijos con los recursos
	while (lista)
		pop(lista);
	return EXIT_SUCCESS;
}
