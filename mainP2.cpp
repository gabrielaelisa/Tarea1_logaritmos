#include <iostream>
#include <math.h>
#include <random>
#include <fstream>

#include "Nodo.h"
#include "Database.h"
using namespace std;

int main(int argc, char *argv[]) 
{ 
    EstructuraBtree t("id"); // arbol B que inserta nodos segun el campo id
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Value myvals2[] = {Value((int) 2), Value("19136938-6"), Value((int) 1000)};
    Nodo nodo(keys, myvals, 3);
    Nodo nodo2(keys, myvals2, 3);
    t.add_nodo(&nodo);
    t.add_nodo(&nodo2);
    Nodo * result=t.buscar(&nodo2);
    string s=result->como_linea();
    cout << "\n el resultado de la linea es " << s << endl;
}