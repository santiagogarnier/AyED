#include<iostream>
#include <fstream>
#include "listas.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro {
  string titulo;
  string suscripcion;
  string pais;
  int rep;
  int minutos;
};

const int ltitulo {18};
const int lsus {14};
const int lpais {10};


fstream& operator >> (fstream &fs, Registro& reg)
{
	reg.titulo = readstring(fs, ltitulo);
	reg.suscripcion = readstring(fs, lsus);
	reg.pais = readstring(fs, lpais);
	fs.read(reinterpret_cast<char *>(&reg.rep), sizeof(reg.rep));
	fs.read(reinterpret_cast<char *>(&reg.minutos), sizeof(reg.minutos));
	return fs;
}


struct Subnivel {
    string pais;
    int minutos;
};

struct Nivel1 {
    string titulo;
    string suscripcion;
    int totrep {};
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
	os << n1.titulo << "\t" << n1.suscripcion << "\t" << n1.totrep << "\t" 
	   << n1.cantsem;
	return os;
}

//por titulo ascendente y suscripcion descendente

int criterion2(const Nivel1 a, const Nivel1 b){
    if(a.titulo == b.titulo)
    return a.suscripcion.compare(b.suscripcion);
    else
    return a.titulo > b.titulo ? 1 : -1;
}

//por pais descendente

int criteriosub (const Subnivel a, const Subnivel b){
    return b.pais.compare(a.pais);
}

void listado (Nodo<Nivel1> *lista, float minprom){
    Nivel1 n1;
    while(lista !=nullptr){
        float prom = static_cast<float>(lista->dato.totrep) 
		             / lista->dato.cantsem;
        

    }
}