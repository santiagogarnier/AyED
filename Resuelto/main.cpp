#include <iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro {
	string producto;
	string canal;
	int unidades;
	float monto;
};
const int lprod = 8;
const int lcan = 8;

struct Venta {
	string canal;
	int unidades;
};

struct Producto {
	string producto;
	int cantvtas = 0;
	float sumamontos = 0;
	Nodo<Venta> *lisvtas = nullptr;
};

struct Canal {
	string canal;
	float monto;
};

ostream& operator << (ostream &os, const Venta& vta)
{
	os << vta.canal << "\t" << vta.unidades;
	return os;
}

ostream& operator << (ostream &os, const Canal& can)
{
	os << can.canal << "\t" << can.monto;
	return os;
}

ostream& operator << (ostream &os, const Producto prod)
{
	os << prod.producto << "\t" << prod.cantvtas  << "\t" << prod.sumamontos;
	return os;
}

fstream& operator >> (fstream &fs, Registro& reg)
{
	reg.producto = readstring(fs, lprod);
	reg.canal = readstring(fs, lcan);
	fs.read(reinterpret_cast<char *>(&reg.unidades), sizeof(reg.unidades));
	fs.read(reinterpret_cast<char *>(&reg.monto), sizeof(reg.monto));
	return fs;
}

//por producto ascendente
int critprod(Producto a, Producto b)
{
	return a.producto.compare(b.producto);
}

//por canal ascendente
int critcanal(Canal a, Canal b)
{
	return a.canal.compare(b.canal);
}

const int maxvtas {12};
const float minprom {280.0};
void listarProd(Nodo<Producto> * lis)
{
	while (lis) {
		if (lis->dato.cantvtas < maxvtas) {
			cout << lis->dato << endl;
			if (lis->dato.sumamontos / lis->dato.cantvtas > minprom) {
				cout << "\nCanal\tUnidades" << endl;
				mostrar(lis->dato.lisvtas);
			}
			cout << endl;
		}
		lis = lis->sig;
	}
}

void listarCan(Nodo<Canal> *lis)
{
	int cant {};
	while (lis) {
		cout << lis->dato << endl;
		if (lis->sig && lis->dato.canal != lis->sig->dato.canal && lis->dato.monto > lis->sig->dato.monto)
			cant++;
		lis = lis->sig;
	}
	cout << endl << "Cantidad de mayores al cambiar: " << cant  << endl;
}

int main()
{
	Nodo<Producto> *listaprod = nullptr;
	Nodo<Canal> *listacan = nullptr;
	fstream archi;

	archi.open("Datos.bin", ios::in | ios::binary);
	if (!archi) {
		cout << "No se pudo abrir el primer archivo de lectura "
		     "Datos.bin" << endl;
		return EXIT_FAILURE;
	}
	Registro reg;
	Producto prod;
	Venta vta;
	Nodo<Producto> *pnodprod;
	Canal can;
	while (archi >> reg) {
		prod.producto = reg.producto;
		pnodprod = insertar_unico(prod, listaprod, critprod);
		pnodprod->dato.cantvtas++;
		pnodprod->dato.sumamontos += reg.monto;
		vta.canal = reg.canal;
		vta.unidades = reg.unidades;
		agregar(pnodprod->dato.lisvtas, vta);
		can.canal = reg.canal;
		can.monto = reg.monto;
		insertar(can, listacan, critcanal);
	}
	archi.close();

	cout << "Listado de Productos\n" << endl;
	listarProd(listaprod);

	cout << endl << "============================" << endl;

	cout << "Listado de Canales\n" << endl;
	listarCan(listacan);

	return 0;
}
