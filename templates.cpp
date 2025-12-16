#include <iostream>
#include <conio.h>
using namespace std;


//Generalizando los datos
//Estructura del template

template<typename TIPO>

void print(TIPO dato){
  cout << dato << endl;
}


int main(){
   print<float>(10.5);
}