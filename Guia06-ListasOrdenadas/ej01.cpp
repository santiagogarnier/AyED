#include <iostream>
#include "listas.hpp"

using namespace std;

struct Alumno {
	string	nombre;
	int	legajo;
	double	promedio;
};

//por promedio descendente y nombre ascendente
int critalum (Alumno a, Alumno b)
{
	if (a.promedio == b.promedio)
		return a.nombre.compare(b.nombre);
	else
		return a.promedio > b.promedio ? -1 : 1;
}

ostream& operator << (ostream &os, const Alumno& a)
{
	os << a.nombre << "\t(legajo: " << a.legajo << ") : " << a.promedio;
	return os;
}

int main()
{
	const int dimselec {9};
	Alumno vselec[dimselec]
		{"Maria", 721, 8.4, "Pedro", 847, 7.2, "Ana", 614, 9.1,
		 "Jose", 578, 8.9,  "Juan", 927, 8.4,  "Unai", 325, 8.1,
		 "Ramon", 418, 8.4, "Elaia", 892, 9.6, "Carlos", 733, 8.5
		};

	const int dimbaj {3};
	Alumno vbajas[dimbaj]
		{"Pedro", 847, 7.2, "Ramon", 418, 8.4, "Unai", 325, 8.1};

	Nodo<Alumno> *lista = nullptr;
	
	//Punto a
	for (int i = 0; i < dimselec; ++i)
		insertar(vselec[i], lista, critalum);

	cout << "Listado de los seleccionados en orden:" << endl;
	mostrar(lista);

	cout << endl << "============================" << endl;
	//Punto b
	cout << "Listado de bajas (sin ordenar):" << endl;
	for (int i {}; i < dimbaj; ++i)
		cout << vbajas[i] << endl;

	//Punto c
	for (int i {}; i < dimbaj; ++i)
		borrar(vbajas[i], lista, critalum);
	cout << endl << "============================" << endl;
	cout << "Listado definitivo sin las bajas:" << endl;
	mostrar(lista);
	//Estrictamente no necesario, pero para no olvidarnos de
	//ser ordenados y prolijos con los recursos
	while (lista)
		pop(lista);
	return 0;
}
