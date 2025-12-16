#include <iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Ordencomp {
	int id;
	string cliente;
	string producto;
	int cant;
};
const int lclie {8};
const int lprod {10};

ostream& operator << (ostream &os, const Ordencomp& ord)
{
	os << "id: " << ord.id << " - " << ord.cliente << " - " << ord.producto
	   << " - cant " << ord.cant;
	return os;
}

fstream& operator << (fstream &fs, const Ordencomp& ord)
{
	fs.write(reinterpret_cast<const char *>(&ord.id), sizeof(ord.id));
	writestring(fs, ord.cliente, lclie);
	writestring(fs, ord.producto, lprod);
	fs.write(reinterpret_cast<const char *>(&ord.cant), sizeof(ord.cant));
	return fs;
}

fstream& operator >> (fstream &fs, Ordencomp& ord)
{
	fs.read(reinterpret_cast<char *>(&ord.id), sizeof(ord.id));
	ord.cliente = readstring(fs, lclie);
	ord.producto = readstring(fs, lprod);
	fs.read(reinterpret_cast<char *>(&ord.cant), sizeof(ord.cant));
	return fs;
}

//por id ascendente
int critid (Ordencomp a, Ordencomp b)
{
	return a.id - b.id;
}

//por cliente y ante igualdad por producto, ambos ascendente
int critclieprod (Ordencomp a, Ordencomp b)
{
	if (a.cliente == b.cliente)
		return a.producto.compare(b.producto);
	else
		return a.cliente > b.cliente ? 1 : -1;
}

int main()
{
	Nodo<Ordencomp> *listaid = nullptr;
	Nodo<Ordencomp> *listaord = nullptr;
	Ordencomp orden;
	fstream archi;

	archi.open("datos02.bin", ios::in | ios::binary);
	if (!archi) {
		cout << "No se pudo abrir el primer archivo de lectura "
		     "datos02.bin" << endl;
		return EXIT_FAILURE;
	}
	while (archi >> orden) {
		insertar(orden, listaid, critid);
		insertar(orden, listaord, critclieprod);
	}
	archi.close();

	//Punto a
	cout << "Listado ordenado por id:" << endl;
	mostrar(listaid);

	cout << endl << "============================" << endl;
	cout << "Listado ordenado por cliente-producto:" << endl;
	mostrar(listaord);

	//Punto b
	cout << endl << "============================" << endl;
	cout << "Ingrese el id a buscar:" << endl;
	Nodo<Ordencomp> *pord;
	cin >> orden.id;
	while (cin && orden.id > 0) { //cin por si ingresaron EOF o error (letras)
		pord = buscar(orden, listaid, critid);
		if (pord)
			cout << pord->dato << endl;
		else
			cout << "No hay ninguna orden con id " << orden.id << endl;
		cout << "Ingrese el id a buscar:" << endl;
		cin >> orden.id;
	}
	cout << endl << "============================" << endl;
	if (!cin) {
		cin.clear();
		clearerr(stdin);
	}

	//Punto c
	cout << "Ingrese el Cliente:" << endl;
	if (cin >> orden.cliente)
		cout << "Ingrese el producto: ";
	while (cin >> orden.producto) {
		cout << "Eliminados:" << endl;
		//Paréntesis extra para evitar adventencias del compilador
		while ((pord = extraer(orden, listaord, critclieprod))) {
			cout << pord->dato << endl;
			orden.id = pord->dato.id;
			delete pord;
			if (!borrar(orden, listaid, critid))
				cout << "Problema inesperado: no se pudo borrar"
				     " la orden con id: " << orden.id << endl;
		}
		cout << endl << "============================" << endl;
		cout << "Lista remanente ordenada por id:" << endl;
		mostrar(listaid);
		cout << endl << "============================" << endl;
		cout << "Lista remanente ordenada por cliente-producto:" << endl;
		mostrar(listaord);
		cout << endl << "Ingrese el Cliente:" << endl;
		if (cin >> orden.cliente)
			cout << "Ingrese el producto: ";
	}
	//Estrictamente no necesario, pero para no olvidarnos de
	//ser ordenados y prolijos con los recursos
	while (listaid)
		pop(listaid);
	while (listaord)
		pop(listaord);
	return 0;
}
