#include <iostream>
#include <fstream>
#include <cassert>
#include "rwstring.hpp"
#include "listas.hpp"

using namespace std;

struct Registro {
	string pais;
	string empresa;
	string tipo;
	float energia;
	float costo;
};
const int lpais {9};
const int lemp {8};
const int ltipo {11};
const float minprom {20.1};
const float maxcosto {1000.0};

fstream& operator >> (fstream &fs, Registro& reg)
{
	reg.pais = readstring(fs, lpais);
	reg.empresa = readstring(fs, lemp);
	reg.tipo = readstring(fs, ltipo);
	fs.read(reinterpret_cast<char *>(&reg.energia), sizeof(reg.energia));
	fs.read(reinterpret_cast<char *>(&reg.costo), sizeof(reg.costo));
	return fs;
}

struct Nivel2 {
	string tipo;
	float costo;
};

ostream& operator << (ostream& os, Nivel2 n2) 
{
	os << n2.tipo << "\t" << n2.costo;
	return os;
}

struct Nivel1 { //País-Empresa
	string pais;
	string empresa;
	float totenerg {};
	int cantdias {};
	float promedio;
	Nodo<Nivel2> *lista {};
};

ostream& operator << (ostream& os, Nivel1 n1) 
{
	os << n1.pais << "\t" << n1.empresa << "\t" << n1.totenerg << "\t" 
	   << n1.cantdias << "\t" << n1.promedio;
	if (n1.promedio > minprom) {
		os << endl;
		mostrar(n1.lista);
	}
	return os;
}

int critNivel2 (Nivel2 a, Nivel2 b) {
	return b.tipo.compare(a.tipo); //descendente
}

int critNivel1 (Nivel1 a, Nivel1 b) {
	if (a.pais == b.pais)
		return a.empresa.compare(b.empresa);
	else
		return a.pais > b.pais ? 1 : -1; 
}

bool mayor_que_siguiente (Nodo<Nivel1> *actual)
{
	assert(actual->sig != nullptr);
	return actual->dato.promedio > actual->sig->dato.promedio;
}

void listar(Nodo<Nivel2>* lista)
{ 
	while (lista != nullptr) {
		if (lista->dato.costo < maxcosto)
			cout << lista->dato << endl;
		lista = lista->sig;
	}
}

int main()
{
	fstream arch;
	arch.open("Datos.bin", ios::in | ios::binary);
	if (!arch) {
		cout << "No se pudo abrir el archivo de datos" << endl;
		return EXIT_FAILURE;
	}

	Nodo<Nivel1> *lista {};
	Nodo<Nivel1> *pnodo;
	Nivel1 n1;
	Nivel2 n2;
	Registro reg;
	while (arch >> reg) {
		n1.pais = reg.pais;
		n1.empresa = reg.empresa;
		pnodo = insertar_unico(n1, lista, critNivel1);
		pnodo->dato.totenerg += reg.energia;
		pnodo->dato.cantdias++;

		n2.tipo = reg.tipo;
		n2.costo = reg.costo;
		insertar(n2, pnodo->dato.lista, critNivel2);
	}
	arch.close();
	pnodo = lista;
	while (pnodo) {
		pnodo->dato.promedio = pnodo->dato.totenerg / pnodo->dato.cantdias;
		pnodo = pnodo->sig;
	}

	mostrar(lista);

	cout << "Ingrese el país y seguidamente la empresa : ";
	while (cin >> n1.pais >> n1.empresa) {
		pnodo = buscar(n1, lista, critNivel1);
		if (pnodo) {
			if (pnodo->sig == nullptr) {
				cout << "No hay siguiente para la combinación "
				     << n1.pais << " con " << n1.empresa << endl;
			} else {
				cout << "El promedio fue " 
				     << (mayor_que_siguiente(pnodo) ? "mayor" : "menor")
				     << " que el siguiente" << endl;
			}
			listar(pnodo->dato.lista);
		} else {
			cout << "No hay datos para combinación " << n1.pais
			     << " con " << n1.empresa << endl;
		}
		cout << "Ingrese el país y seguidamente la empresa : ";
	}
	return 0;
}
