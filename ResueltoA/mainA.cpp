#include <iostream>
#include <fstream>
#include "rwstring.hpp"
#include "listas.hpp"

using namespace std;

struct Registro {
	string titulo;
	string suscripcion;
	string pais;
	int reproducciones;
	int minutos;
};
const int ltit {18};
const int lsus {14};
const int lpais {10};

fstream& operator >> (fstream &fs, Registro& reg)
{
	reg.titulo = readstring(fs, ltit);
	reg.suscripcion = readstring(fs, lsus);
	reg.pais = readstring(fs, lpais);
	fs.read(reinterpret_cast<char *>(&reg.reproducciones), sizeof(reg.reproducciones));
	fs.read(reinterpret_cast<char *>(&reg.minutos), sizeof(reg.minutos));
	return fs;
}

struct Subnivel { //Nivel 2
	string pais;
	int minutos;
};

struct Nivel1 { //Nivel 1: Título y tipo suscripción
	string titulo;
	string suscripcion;
	int sumreprod {};
	int cantsem {};
	Nodo<Subnivel> *sublista {};
};

ostream& operator << (ostream &os, Subnivel& sub)
{
	os << sub.pais << "\t" << sub.minutos;
	return os;
}

ostream& operator << (ostream &os, Nivel1& n1)
{
	os << n1.titulo << "\t" << n1.suscripcion << "\t" << n1.sumreprod << "\t" 
	   << n1.cantsem;
	return os;
}

//x Título ascendente y suscripción descente
int criterio_n1(const Nivel1 a, const Nivel1 b)
{
	if (a.titulo == b.titulo)
		return b.suscripcion.compare(a.suscripcion);
	else
		return a.titulo > b.titulo ? 1 : -1;

}

//x País ascendente
int criterio_sub(const Subnivel a, const Subnivel b)
{
	return a.pais.compare(b.pais);

}

void listado(Nodo<Nivel1> *lista, float minprom)
{
	Nivel1 n1;
	while (lista != nullptr) {
		float prom = static_cast<float>(lista->dato.sumreprod) 
		             / lista->dato.cantsem;
		if (prom > minprom) {
			cout << lista->dato << endl;
			Nodo<Subnivel> *psub = lista->dato.sublista;
			while (psub != nullptr) {
				if (psub->sig != nullptr
				    && psub->dato.minutos > psub->sig->dato.minutos)
					cout << psub->dato << endl;
				psub = psub->sig;
			}
			cout << endl;
		}
		lista = lista->sig;
	}
}

Nodo<Subnivel>* mayor(Nodo<Subnivel>* p)
{
	Nodo<Subnivel>* max = p;
	while (p != nullptr) {
		if (p->dato.minutos > max->dato.minutos)
			max = p;
		p = p->sig;
	}
	return max;
}

int main()
{
	fstream fs;
	fs.open("Datos2025P2.bin", ios::binary | ios::in);
	if (!fs.is_open())
	{
		cout << "No se pudo abrir el primer archivo de lectura" << endl;
		return EXIT_FAILURE;
	}
	Registro reg;
	Nivel1 n1;
	Subnivel sub;
	Nodo<Nivel1> *lista {nullptr};
	Nodo<Nivel1> *pn1;

	// Punto 2
	while (fs >> reg) {
		n1.titulo = reg.titulo;
		n1.suscripcion = reg.suscripcion;
		pn1 = insertar_unico(n1, lista, criterio_n1);
		pn1->dato.sumreprod += reg.reproducciones;
		pn1->dato.cantsem++;
		//
		sub.pais = reg.pais;
		sub.minutos = reg.minutos;
		insertar(sub, pn1->dato.sublista, criterio_sub);
	}
	fs.close();

	// Punto 3
	cout << "Listado" << endl << endl;
	const float min_promedio {4.9};
	listado(lista, min_promedio);

	// Punto 4
	cout << "Ingrese el título y seguidamente el tipo de suscripción : ";
	while (cin >> n1.titulo >> n1.suscripcion) {
		pn1 = buscar(n1, lista, criterio_n1);
		if (pn1) {
			//Si existe el nivel 1 tiene que tener al menos 1
			//elemento en la sublista
			Nodo<Subnivel>*psub = mayor(pn1->dato.sublista);
			cout << "La mayor cantidad de minutos fue " 
			     << psub->dato.minutos << " y se dio con el país "
			     << psub->dato.pais << endl;
		} else {
			cout << "No hay datos para combinación " << n1.titulo
			     << " y " << n1.suscripcion << endl;
		}
		cout << "Ingrese el título y seguidamente el tipo de suscripción : ";
	}

	return EXIT_SUCCESS;
}
